// Copyright 2019,2020,2021 Sony Corporation.
// Copyright 2021 Sony Group Corporation.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <nnablart/config.h>
#include <nnablart/functions.h>
#include <stdlib.h>

#ifdef CONFIG_PAD

typedef struct {
  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t input_strides;
  rt_list_t output_strides;
  rt_variable_t *input;
  rt_variable_getter get_input;
  rt_variable_t *output;
  rt_variable_setter set_output;
  rt_list_t pad_width[2];
  rt_list_t out_position;
  int output_size;
} pad_private_t;

rt_function_error_t exec_pad_generic(rt_function_t *f);

// Pad
rt_function_error_t allocate_pad_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  pad_private_t *p = rt_malloc_func(sizeof(pad_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  pad_local_context_t *context = (pad_local_context_t *)(f->local_context);
  ((pad_local_context_t *)(f->local_context))->data = (void *)p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);
  p->output = f->outputs[0];
  p->set_output = select_setter(p->output);

  p->input_shape = clone_list(f->inputs[0]->shape);
  p->output_shape = clone_list(f->outputs[0]->shape);
  p->input_strides = calc_contiguous_strides(f->inputs[0]->shape);
  p->output_strides = calc_contiguous_strides(f->outputs[0]->shape);
  p->pad_width[0] = allocate_list(p->output_shape.size);
  p->pad_width[1] = allocate_list(p->output_shape.size);
  p->output_size = calc_shape_size(p->output_shape);
  p->out_position = allocate_list(p->output_shape.size);

  int i, j;
  for (i = 0; i < p->output_shape.size - context->pad_width.size / 2; i++) {
    p->pad_width[0].data[i] = 0;
    p->pad_width[1].data[i] = 0;
  }
  for (j = 0; i < p->output_shape.size; i++, j = j + 2) {
    p->pad_width[0].data[i] = context->pad_width.data[j];
    p->pad_width[1].data[i] = context->pad_width.data[j + 1];
  }
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_PAD_FLOAT32
    f->exec_func = exec_pad;
#endif /* CONFIG_PAD_FLOAT32 */
  } else {
#ifdef CONFIG_PAD_GENERIC
    f->exec_func = exec_pad_generic;
#endif /* CONFIG_PAD_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_pad_local_context(rt_function_t *f) {
  pad_private_t *p =
      (pad_private_t *)(((pad_local_context_t *)(f->local_context))->data);
  free_list(p->input_shape);
  free_list(p->output_shape);
  free_list(p->input_strides);
  free_list(p->output_strides);
  free_list(p->out_position);
  free_list(p->pad_width[0]);
  free_list(p->pad_width[1]);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

static inline int reflect_index(int index, int len) {
  return len > 0 ? abs(((index / len) & 1) * len - (index % len)) : 0;
}

rt_function_error_t exec_pad(rt_function_t *f) {
  pad_local_context_t *context = (pad_local_context_t *)(f->local_context);
  pad_private_t *p = (pad_private_t *)(context->data);
  const float *x = (float *)(p->input->data);
  float *y = (float *)(p->output->data);

  if (context->mode == PAD_MODE_CONSTANT) {
    for (int o = 0; o < p->output_size; o++) {
      uint8_t is_constant = 0;
      int index = 0;
      pos_to_shape(p->out_position, p->output->shape, o);
      for (int i = 0; i < p->output_shape.size; i++) {
        if (p->out_position.data[i] < p->pad_width[0].data[i] ||
            (p->out_position.data[i] >=
             p->output_shape.data[i] - p->pad_width[1].data[i])) {
          is_constant = 1;
          break;
        }
        index += (p->out_position.data[i] - p->pad_width[0].data[i]) *
                 p->input_strides.data[i];
      }
      if (is_constant) {
        y[o] = context->constant_value;
      } else {
        y[o] = x[index];
      }
    }
  } else if (context->mode == PAD_MODE_REFLECT) {
    for (int o = 0; o < p->output_size; o++) {
      int index = 0;
      pos_to_shape(p->out_position, p->output->shape, o);
      for (int i = 0; i < p->output_shape.size; i++) {
        if (p->out_position.data[i] < p->pad_width[0].data[i]) {
          int _p = p->pad_width[0].data[i];
          int r = reflect_index(_p - p->out_position.data[i],
                                p->input_shape.data[i] - 1);
          p->out_position.data[i] = _p + r;
        }
        if (p->out_position.data[i] >=
            p->output_shape.data[i] - p->pad_width[1].data[i]) {
          int _p = p->pad_width[0].data[i] + p->input_shape.data[i];
          int r = reflect_index(p->out_position.data[i] - _p + 1,
                                p->input_shape.data[i] - 1);
          p->out_position.data[i] = _p - r - 1;
        }
        index += (p->out_position.data[i] - p->pad_width[0].data[i]) *
                 p->input_strides.data[i];
      }
      y[o] = x[index];
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t exec_pad_generic(rt_function_t *f) {
  pad_local_context_t *context = (pad_local_context_t *)(f->local_context);
  pad_private_t *p = (pad_private_t *)(context->data);

  if (context->mode == PAD_MODE_CONSTANT) {
    for (int o = 0; o < p->output_size; o++) {
      uint8_t is_constant = 0;
      int index = 0;
      pos_to_shape(p->out_position, p->output->shape, o);
      for (int i = 0; i < p->output_shape.size; i++) {
        if (p->out_position.data[i] < p->pad_width[0].data[i] ||
            (p->out_position.data[i] >=
             p->output_shape.data[i] - p->pad_width[1].data[i])) {
          is_constant = 1;
          break;
        }
        index += (p->out_position.data[i] - p->pad_width[0].data[i]) *
                 p->input_strides.data[i];
      }
      if (is_constant) {
        p->set_output(p->output, o, context->constant_value);
      } else {
        float x = p->get_input(p->input, index);
        p->set_output(p->output, o, x);
      }
    }
  } else if (context->mode == PAD_MODE_REFLECT) {
    for (int o = 0; o < p->output_size; o++) {
      int index = 0;
      pos_to_shape(p->out_position, p->output->shape, o);
      for (int i = 0; i < p->output_shape.size; i++) {
        if (p->out_position.data[i] < p->pad_width[0].data[i]) {
          int _p = p->pad_width[0].data[i];
          int r = reflect_index(_p - p->out_position.data[i],
                                p->input_shape.data[i] - 1);
          p->out_position.data[i] = _p + r;
        }
        if (p->out_position.data[i] >=
            p->output_shape.data[i] - p->pad_width[1].data[i]) {
          int _p = p->pad_width[0].data[i] + p->input_shape.data[i];
          int r = reflect_index(p->out_position.data[i] - _p + 1,
                                p->input_shape.data[i] - 1);
          p->out_position.data[i] = _p - r - 1;
        }
        index += (p->out_position.data[i] - p->pad_width[0].data[i]) *
                 p->input_strides.data[i];
      }
      float x = p->get_input(p->input, index);
      p->set_output(p->output, o, x);
    }
  }
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_PAD */