// -*- coding:utf-8 -*-

#include "list.h"
#include "accessor.h"
#include "vector.h"

void pos_to_shape(rt_list_t out, rt_list_t shape, int pos) {
  int i = 0, o = 1;
  for (i = shape.size - 1; i >= 0; i--) {
    out.data[i] = (pos / o) % shape.data[i];
    o *= shape.data[i];
  }
}

int shape_to_pos(rt_list_t shape, rt_list_t pos) {
  int ret = 0;
  int i, o = 1;
  for (i = shape.size - 1; i >= 0; i--) {
    ret += o * pos.data[i];
    o *= shape.data[i];
  }
  return ret;
}

int find_num_in_shape(rt_list_t shape, int num) {
  int i;
  for (i = 0; i < shape.size; i++) {
    if (shape.data[i] == num) {
      return i;
    }
  }
  return -1;
}

static void calc_broadcast_position(rt_list_t broadcast_position,
                                    rt_list_t broadcast_shape,
                                    rt_list_t position) {
  int bi, pi;
  for (bi = broadcast_position.size - 1, pi = position.size - 1;
       bi >= 0 && pi >= 0; bi--, pi--) {
    if (broadcast_shape.data[bi] == 1) {
      broadcast_position.data[bi] = 0;
    } else {
      broadcast_position.data[bi] = position.data[pi];
    }
  }
  for (; bi >= 0; bi--) {
    broadcast_position.data[bi] = 0;
  }
}

vector_calc_context_t init_vector_calc_context(int num_of_inputs,
                                               rt_variable_t *inputs,
                                               rt_variable_t output) {
  int i; // loop counter

  vector_calc_context_t c;

  c.num_of_inputs = num_of_inputs;

  // shape for calculation.
  c.shape = output.shape;

  // prepare all shapes.
  c.input_shapes = calloc(sizeof(rt_list_t), c.num_of_inputs);
  for (i = 0; i < c.num_of_inputs; i++) {
    c.input_shapes[i].size = calc_list_size(inputs[i].shape);
    c.input_shapes[i].data = inputs[i].data;
  }
  c.output_shape.size = calc_list_size(output.shape);
  c.output_shape.data = output.data;

  // prepare position variables.
  c.position = clone_list(c.shape);
  c.input_positions = calloc(sizeof(rt_list_t), c.num_of_inputs);
  for (i = 0; i < c.num_of_inputs; i++) {
    c.input_positions[i] = clone_list(c.input_shapes[i]);
  }
  c.output_position = clone_list(c.output_shape);

  // prepare input value buffer.
  c.input_values = calloc(sizeof(float), c.num_of_inputs);

  return c;
}

void free_vector_calc_context(vector_calc_context_t c) {
  // free allocated buffers.
  free(c.input_values);
  free_list(c.output_position);
  int i;
  for (i = 0; i < c.num_of_inputs; i++) {
    free_list(c.input_positions[i]);
  }
  free(c.input_positions);
  free_list(c.position);
  free(c.input_shapes);
}

void vector_calc(vector_calc_context_t c, int num_of_inputs, rt_variable_t *inputs,
                 rt_variable_t output, float (*calc_func)(int, float *))

{
  int i, j; // loop counters;

  // main loop
  int shape_length = calc_list_size(c.shape);
  for (i = 0; i < shape_length; i++) {
    pos_to_shape(c.position, c.shape, i);

    for (j = 0; j < c.num_of_inputs; j++) {
      calc_broadcast_position(c.input_positions[j], c.input_shapes[j],
                              c.position);
      c.input_values[j] = select_getter(inputs[j].type)(
          &(inputs[j]), shape_to_pos(c.input_shapes[j], c.input_positions[j]));
    }
    calc_broadcast_position(c.output_position, c.output_shape, c.position);
    select_setter(output.type)(&output, shape_to_pos(c.output_shape, c.output_position),
               calc_func(c.num_of_inputs, c.input_values));
  }
}

vector_average_context_t init_vector_average_context(rt_list_t in_shape,
                                                     rt_list_t axes_shape) {
  vector_average_context_t c;
  c.in_shape = clone_list(in_shape);
  c.in_pos = clone_list(in_shape);
  c.calc_axes = clone_list(axes_shape);
  c.calc_shape = clone_list(axes_shape);
  c.calc_pos = clone_list(axes_shape);

  int i;
  for (i = 0; i < c.calc_shape.size; i++) {
    c.calc_shape.data[i] = c.in_shape.data[c.calc_axes.data[i]];
  }
  c.rest_axes = allocate_list(in_shape.size - c.calc_axes.size);
  c.rest_shape = allocate_list(in_shape.size - c.calc_axes.size);
  c.rest_pos = allocate_list(in_shape.size - c.calc_axes.size);

  int w_pos = 0;
  for (i = 0; i < c.rest_axes.size; i++) {
    while (find_num_in_shape(c.calc_axes, w_pos) >= 0 &&
           w_pos < in_shape.size) {
      w_pos += 1;
    }
    c.rest_axes.data[i] = w_pos;
    c.rest_shape.data[i] = in_shape.data[w_pos];
    w_pos += 1;
  }

  c.calc_ipos_max = calc_list_size(c.calc_shape);
  c.rest_ipos_max = calc_list_size(c.rest_shape);

  if (c.rest_shape.size > 0) {
    c.output.data = c.rest_shape.data;
    c.output.type = NN_DATA_TYPE_FLOAT;
    c.output.data = calloc(sizeof(float), c.rest_ipos_max);
  } else {
    static int output_shape[] = {1};
    c.output.data = output_shape;
    c.output.type = NN_DATA_TYPE_FLOAT;
    c.output.data = calloc(sizeof(float), 1);
    c.calc_ipos_max = calc_list_size(c.in_shape);
  }
  return c;
}

void vector_average_calc_mean(vector_average_context_t c, rt_variable_t input) {
  int calc_ipos = 0;
  int rest_ipos = 0;

  if (c.rest_shape.size > 0) {
    int i, j;
    for (rest_ipos = 0; rest_ipos < c.rest_ipos_max; rest_ipos++) {
      float mean = 0;
      int count = 0;
      pos_to_shape(c.rest_pos, c.rest_shape, rest_ipos);
      for (calc_ipos = 0; calc_ipos < c.calc_ipos_max; calc_ipos++) {
        pos_to_shape(c.calc_pos, c.calc_shape, calc_ipos);
        for (i = 0; i < c.in_pos.size; i++) {
          for (j = 0; j < c.calc_axes.size; j++) {
            if (c.calc_axes.data[j] == i) {
              c.in_pos.data[i] = c.calc_pos.data[j];
            }
          }
          for (j = 0; j < c.rest_axes.size; j++) {
            if (c.rest_axes.data[j] == i) {
              c.in_pos.data[i] = c.rest_pos.data[j];
            }
          }
        }
        mean += select_getter(input.type)(&input, shape_to_pos(c.in_shape, c.in_pos));
        count += 1;
      }
      select_setter(c.output.type)(&(c.output), rest_ipos, mean / count);
    }
  } else {
    int i;
    float mean = 0;
    for (i = 0; i < c.calc_ipos_max; i++) {
      mean += select_getter(input.type)(&input, i);
    }
    select_setter(c.output.type)(&(c.output), 0, mean / c.calc_ipos_max);
  }
}

void free_vector_average_context(vector_average_context_t c) {
  free(c.output.data);
  free_list(c.rest_pos);
  free_list(c.rest_shape);
  free_list(c.rest_axes);
  free_list(c.calc_pos);
  free_list(c.calc_shape);
  free_list(c.calc_axes);
  free_list(c.in_pos);
  free_list(c.in_shape);
}
