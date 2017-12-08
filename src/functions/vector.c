// -*- coding:utf-8 -*-

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

rt_list_t allocate_shape(int length) {
  rt_list_t ret;
  assert(length >= 0);
  ret.size = length;
  ret.data = (int *)calloc(sizeof(int), length);
  return ret;
}

void free_shape(rt_list_t s) {
  if (s.data) {
    free(s.data);
  }
  s.data = 0;
}

rt_list_t clone_shape(rt_list_t src) {
  int i;
  rt_list_t dst = allocate_shape(src.size);
  for (i = 0; i < src.size; i++) {
    dst.data[i] = src.data[i];
  }
  return dst;
}

void pos_to_shape(rt_list_t out, rt_list_t shape, int pos) {
  int i = 0, o = 1;
  for (i = shape.size - 1; i >= 0; i--) {
    out.data[i] = (pos / o) % shape.data[i];
    o *= shape.data[i];
  }
}

int shape_to_pos(rt_list_t s, rt_list_t pos) {
  int ret = 0;
  int i, o = 1;
  for (i = s.size - 1; i >= 0; i--) {
    ret += o * pos.data[i];
    o *= s.data[i];
  }
  return ret;
}

int find_num_in_shape(rt_list_t s, int num) {
  int i;
  for (i = 0; i < s.size; i++) {
    if (s.data[i] == num) {
      return i;
    }
  }
  return -1;
}

int calc_shape_size(rt_list_t shape) {
  int i;
  int size = 1;
  for (i = 0; i < shape.size; i++) {
    size *= shape.data[i];
  }
  return size;
}

rt_variable_t get_values_from_param(rt_param_t param) {
  rt_variable_t v;
  v.buffer = param.data;
  int param_size = calc_shape_size(param.shape);
  v.buffer = calloc(sizeof(float), param_size);
  int i;
  for (i = 0; i < param_size; i++) {
    v.buffer[i] = param.get(&param, i);
  }
  return v;
}

rt_param_t vertex_to_param(rt_variable_t v) {
  rt_param_t p;
  p.data = v.buffer;
  p.type = NN_PARAM_TYPE_FLOAT;
  p.data = v.buffer;
  p.get = getFloat;
  p.set = setFloat;
  return p;
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
                                               rt_param_t *inputs,
                                               rt_param_t output) {
  int i; // loop counter

  vector_calc_context_t c;

  c.num_of_inputs = num_of_inputs;

  // shape for calculation.
  c.shape.size = calc_shape_size(output.shape);
  c.shape.data = output.data;

  c.shape_length = calc_shape_size(c.shape);

  // prepare all shapes.
  c.input_shapes = calloc(sizeof(rt_list_t), c.num_of_inputs);
  for (i = 0; i < c.num_of_inputs; i++) {
    c.input_shapes[i].size = calc_shape_size(inputs[i].shape);
    c.input_shapes[i].data = inputs[i].data;
  }
  c.output_shape.size = calc_shape_size(output.shape);
  c.output_shape.data = output.data;

  // prepare position variables.
  c.position = clone_shape(c.shape);
  c.input_positions = calloc(sizeof(rt_list_t), c.num_of_inputs);
  for (i = 0; i < c.num_of_inputs; i++) {
    c.input_positions[i] = clone_shape(c.input_shapes[i]);
  }
  c.output_position = clone_shape(c.output_shape);

  // prepare input value buffer.
  c.input_values = calloc(sizeof(float), c.num_of_inputs);

  return c;
}

void free_vector_calc_context(vector_calc_context_t c) {
  // free allocated buffers.
  free(c.input_values);
  free_shape(c.output_position);
  int i;
  for (i = 0; i < c.num_of_inputs; i++) {
    free_shape(c.input_positions[i]);
  }
  free(c.input_positions);
  free_shape(c.position);
  free(c.input_shapes);
}

void vector_calc(vector_calc_context_t c, int num_of_inputs, rt_param_t *inputs,
                 rt_param_t output, float (*calc_func)(int, float *))

{
  int i, j; // loop counters;

  // main loop
  for (i = 0; i < c.shape_length; i++) {
    pos_to_shape(c.position, c.shape, i);

    for (j = 0; j < c.num_of_inputs; j++) {
      calc_broadcast_position(c.input_positions[j], c.input_shapes[j],
                              c.position);
      c.input_values[j] = inputs[j].get(
          &(inputs[j]), shape_to_pos(c.input_shapes[j], c.input_positions[j]));
    }
    calc_broadcast_position(c.output_position, c.output_shape, c.position);
    output.set(&output, shape_to_pos(c.output_shape, c.output_position),
               calc_func(c.num_of_inputs, c.input_values));
  }
}

vector_average_context_t init_vector_average_context(rt_list_t in_shape,
                                                     rt_list_t axes_shape) {
  vector_average_context_t c;
  c.in_shape = clone_shape(in_shape);
  c.in_pos = clone_shape(in_shape);
  c.calc_axes = clone_shape(axes_shape);
  c.calc_shape = clone_shape(axes_shape);
  c.calc_pos = clone_shape(axes_shape);

  int i;
  for (i = 0; i < c.calc_shape.size; i++) {
    c.calc_shape.data[i] = c.in_shape.data[c.calc_axes.data[i]];
  }
  c.rest_axes = allocate_shape(in_shape.size - c.calc_axes.size);
  c.rest_shape = allocate_shape(in_shape.size - c.calc_axes.size);
  c.rest_pos = allocate_shape(in_shape.size - c.calc_axes.size);

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

  c.calc_ipos_max = calc_shape_size(c.calc_shape);
  c.rest_ipos_max = calc_shape_size(c.rest_shape);

  if (c.rest_shape.size > 0) {
    c.output.data = c.rest_shape.data;
    c.output.type = NN_PARAM_TYPE_FLOAT;
    c.output.data = calloc(sizeof(float), c.rest_ipos_max);
    c.output.get = getFloat;
    c.output.set = setFloat;
  } else {
    static int output_shape[] = {1};
    c.output.data = output_shape;
    c.output.type = NN_PARAM_TYPE_FLOAT;
    c.output.data = calloc(sizeof(float), 1);
    c.output.get = getFloat;
    c.output.set = setFloat;
    c.calc_ipos_max = calc_shape_size(c.in_shape);
  }
  return c;
}

void vector_average_calc_mean(vector_average_context_t c, rt_param_t input) {
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
        mean += input.get(&input, shape_to_pos(c.in_shape, c.in_pos));
        count += 1;
      }
      c.output.set(&(c.output), rest_ipos, mean / count);
    }
  } else {
    int i;
    float mean = 0;
    for (i = 0; i < c.calc_ipos_max; i++) {
      mean += input.get(&input, i);
    }
    c.output.set(&(c.output), 0, mean / c.calc_ipos_max);
  }
}

void free_vector_average_context(vector_average_context_t c) {
  free(c.output.data);
  free_shape(c.rest_pos);
  free_shape(c.rest_shape);
  free_shape(c.rest_axes);
  free_shape(c.calc_pos);
  free_shape(c.calc_shape);
  free_shape(c.calc_axes);
  free_shape(c.in_pos);
  free_shape(c.in_shape);
}
