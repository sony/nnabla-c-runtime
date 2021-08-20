// Copyright 2018,2019,2020,2021 Sony Corporation.
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

#include <nnablart/config.h>
#include <nnablart/functions.h>

#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <string.h>

#ifdef CONFIG_DECONVOLUTION

typedef struct {
  rt_variable_t *input;
  rt_variable_getter get_input;

  rt_variable_t *weight;
  rt_variable_getter get_weight;

  rt_variable_t *bias;
  rt_variable_getter get_bias;

  rt_variable_t *output;
  rt_variable_setter set_output;
  rt_variable_getter get_output;

  rt_list_t input_shape;
  rt_list_t output_shape;
  rt_list_t kernel_shape;
  rt_list_t in_position;
  rt_list_t out_position;

  int spatial_dims;
  int base_loop_size;
} deconvolution_private_t;

rt_function_error_t exec_deconvolution_generic(rt_function_t *f);

// Deconvolution
rt_function_error_t allocate_deconvolution_local_context(rt_function_t *f) {
  deconvolution_local_context_t *c =
      (deconvolution_local_context_t *)(f->local_context);

  if (f->num_of_inputs != 2 && f->num_of_inputs != 3) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }

  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }

  deconvolution_private_t *p = rt_malloc_func(sizeof(deconvolution_private_t));
  if (p == 0) {
    return RT_FUNCTION_ERROR_MALLOC;
  }
  c->data = (void *)p;
  p->input = f->inputs[0];
  p->get_input = select_getter(p->input);

  p->weight = f->inputs[1];
  p->get_weight = select_getter(p->weight);

  p->output = f->outputs[0];
  p->get_output = select_getter(p->output);
  p->set_output = select_setter(p->output);

  if (f->num_of_inputs > 2) {
    p->bias = f->inputs[2];
    p->get_bias = select_getter(p->bias);
  } else {
    p->bias = 0;
  }

  p->base_loop_size = 1;
  for (int i = 0; i < c->base_axis; i++) {
    p->base_loop_size *= p->input->shape.data[i];
  }
  p->spatial_dims = p->input->shape.size - c->base_axis - 1;

  p->input_shape = allocate_list(p->spatial_dims);
  p->kernel_shape = allocate_list(p->spatial_dims);
  p->output_shape = allocate_list(p->spatial_dims);
  p->in_position = allocate_list(p->spatial_dims);
  p->out_position = allocate_list(p->spatial_dims);

  for (int i = 0; i < p->spatial_dims; i++) {
    p->kernel_shape.data[i] = p->weight->shape.data[i + 2];
    p->input_shape.data[i] = p->input->shape.data[i + c->base_axis + 1];
    p->output_shape.data[i] = p->output->shape.data[i + c->base_axis + 1];
  }

  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT &&
      p->weight->type == NN_DATA_TYPE_FLOAT &&
      ((p->bias && p->bias->type == NN_DATA_TYPE_FLOAT) || !p->bias)) {
#ifdef CONFIG_DECONVOLUTION_FLOAT32
    f->exec_func = exec_deconvolution;
#endif /* CONFIG_DECONVOLUTION_FLOAT32 */
  } else {
#ifdef CONFIG_DECONVOLUTION_GENERIC
    f->exec_func = exec_deconvolution_generic;
#endif /* CONFIG_DECONVOLUTION_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_deconvolution_local_context(rt_function_t *f) {
  deconvolution_local_context_t *c =
      (deconvolution_local_context_t *)(f->local_context);
  deconvolution_private_t *p = (deconvolution_private_t *)(c->data);
  free_list(p->input_shape);
  free_list(p->output_shape);
  free_list(p->kernel_shape);
  free_list(p->in_position);
  free_list(p->out_position);
  rt_free_func(p);
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_DECONVOLUTION_FLOAT32
rt_function_error_t exec_deconvolution(rt_function_t *f) {
  deconvolution_local_context_t *c =
      (deconvolution_local_context_t *)(f->local_context);
  deconvolution_private_t *p = (deconvolution_private_t *)(c->data);

  int output_size = calc_shape_size(p->output_shape);
  int kernel_size = calc_shape_size(p->kernel_shape);
  int input_size = calc_shape_size(p->input_shape);

  memset(p->output->data, 0, sizeof(float) * calc_shape_size(p->output->shape));

  for (int b = 0; b < p->base_loop_size; b++) {
    for (int g = 0; g < c->group; g++) {
      for (int om = 0; om < p->weight->shape.data[1]; om++) {
        int output_offset = (b * c->group * p->weight->shape.data[1] +
                             g * p->weight->shape.data[1] + om) *
                            output_size;
        for (int im = 0; im < p->weight->shape.data[0] / c->group; im++) {
          int input_offset = (b * p->weight->shape.data[0] +
                              g * p->weight->shape.data[0] / c->group + im) *
                             input_size;
          int kernel_offset = (g * p->weight->shape.data[1] *
                                   p->weight->shape.data[0] / c->group +
                               im * p->weight->shape.data[1] + om) *
                              kernel_size;
          for (int o = 0; o < output_size; o++) {
            float sum = 0.0f;
            pos_to_shape(p->out_position, p->output_shape, o);
            for (int k = 0; k < kernel_size; k++) {
              pos_to_shape(p->in_position, p->kernel_shape, k);
              uint8_t condition = 1;
              for (int j = 0; j < p->spatial_dims; j++) {
                int k1 =
                    c->dilation.data[j] * (p->kernel_shape.data[j] - 1) + 1;
                p->in_position.data[j] *= c->dilation.data[j];
                p->in_position.data[j] -= k1 - c->pad.data[j] - 1;
                p->in_position.data[j] += p->out_position.data[j];
                if (p->in_position.data[j] % c->stride.data[j] != 0) {
                  condition = 0;
                  break;
                }
                p->in_position.data[j] =
                    p->in_position.data[j] / c->stride.data[j];
                if (p->in_position.data[j] < 0 ||
                    p->in_position.data[j] >= p->input_shape.data[j]) {
                  condition = 0;
                  break;
                }
              }
              if (condition) {
                float x = *((float *)(p->input->data) + input_offset +
                            shape_to_pos(p->input_shape, p->in_position));
                float w = *((float *)(p->weight->data) + kernel_offset +
                            (kernel_size - k - 1));
                sum += x * w;
              }
            }
            *((float *)(p->output->data) + output_offset + o) += sum;
          }
        }
        if (p->bias) {
          for (int o = 0; o < output_size; o++) {
            *((float *)(p->output->data) + output_offset + o) +=
                *((float *)(p->bias->data) + g * p->weight->shape.data[1] + om);
          }
        }
      }
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_DECONVOLUTION_FLOAT32 */

#ifdef CONFIG_DECONVOLUTION_GENERIC
rt_function_error_t exec_deconvolution_generic(rt_function_t *f) {
  deconvolution_local_context_t *c =
      (deconvolution_local_context_t *)(f->local_context);
  deconvolution_private_t *p = (deconvolution_private_t *)(c->data);

  int output_size = calc_shape_size(p->output_shape);
  int kernel_size = calc_shape_size(p->kernel_shape);
  int input_size = calc_shape_size(p->input_shape);

  fill_variable_with(f->outputs[0], 0);

  for (int b = 0; b < p->base_loop_size; b++) {
    for (int g = 0; g < c->group; g++) {
      for (int om = 0; om < p->weight->shape.data[1]; om++) {
        int output_offset = (b * c->group * p->weight->shape.data[1] +
                             g * p->weight->shape.data[1] + om) *
                            output_size;
        for (int im = 0; im < p->weight->shape.data[0] / c->group; im++) {
          int input_offset = (b * p->weight->shape.data[0] +
                              g * p->weight->shape.data[0] / c->group + im) *
                             input_size;
          int kernel_offset = (g * p->weight->shape.data[1] *
                                   p->weight->shape.data[0] / c->group +
                               im * p->weight->shape.data[1] + om) *
                              kernel_size;
          for (int o = 0; o < output_size; o++) {
            float sum = 0.0f;
            pos_to_shape(p->out_position, p->output_shape, o);
            for (int k = 0; k < kernel_size; k++) {
              pos_to_shape(p->in_position, p->kernel_shape, k);
              uint8_t condition = 1;
              for (int j = 0; j < p->spatial_dims; j++) {
                int k1 =
                    c->dilation.data[j] * (p->kernel_shape.data[j] - 1) + 1;
                p->in_position.data[j] *= c->dilation.data[j];
                p->in_position.data[j] -= k1 - c->pad.data[j] - 1;
                p->in_position.data[j] += p->out_position.data[j];
                if (p->in_position.data[j] % c->stride.data[j] != 0) {
                  condition = 0;
                  break;
                }
                p->in_position.data[j] =
                    p->in_position.data[j] / c->stride.data[j];
                if (p->in_position.data[j] < 0 ||
                    p->in_position.data[j] >= p->input_shape.data[j]) {
                  condition = 0;
                  break;
                }
              }
              if (condition) {
                float x = p->get_input(
                    p->input, input_offset +
                                  shape_to_pos(p->input_shape, p->in_position));
                float w = p->get_weight(p->weight,
                                        kernel_offset + (kernel_size - k - 1));
                sum += x * w;
              }
            }
            float y = p->get_output(p->output, output_offset + o);
            y += sum;
            p->set_output(p->output, output_offset + o, y);
          }
        }
        if (p->bias) {
          for (int o = 0; o < output_size; o++) {
            float y = p->get_output(p->output, output_offset + o);
            float bias =
                p->get_bias(p->bias, g * p->weight->shape.data[1] + om);
            y += bias;
            p->set_output(p->output, output_offset + o, y);
          }
        }
      }
    }
  }

  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_DECONVOLUTION_GENERIC */

#endif /* CONFIG_DECONVOLUTION */
