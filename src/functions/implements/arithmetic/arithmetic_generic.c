// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
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

#include "arithmetic.h"
#include "../../utilities/accessor.h"
#include "../../utilities/shape.h"
#include <math.h>

void calc_dim_arithmetic_generic(rt_variable_t *output, rt_variable_t *input1,
                                 rt_variable_t *input2, int dim_index,
                                 int y_out, int y_in1, int y_in2,
                                 float (*calc_func)(float, float)) {
  int dim_size = output->shape.size;
  int x_size_out = output->shape.data[dim_index];
  int x_size_in1 = input1->shape.data[dim_index];
  int x_size_in2 = input2->shape.data[dim_index];
  rt_variable_getter get_input1 = select_getter(input1);
  rt_variable_getter get_input2 = select_getter(input2);
  rt_variable_setter set_output = select_setter(output);
  for (int x_out = 0; x_out < x_size_out; x_out++) {
    int x_in1 = (x_out % x_size_in1);
    int x_in2 = (x_out % x_size_in2);
    int z_out = y_out * x_size_out + x_out;
    int z_in1 = y_in1 * x_size_in1 + x_in1;
    int z_in2 = y_in2 * x_size_in2 + x_in2;
    if (dim_index + 1 < dim_size) {
      calc_dim_arithmetic_generic(output, input1, input2, dim_index + 1, z_out,
                                  z_in1, z_in2, calc_func);
    } else {
      float data_in1 = get_input1(input1, z_in1);
      float data_in2 = get_input2(input2, z_in2);
      set_output(output, z_out, calc_func(data_in1, data_in2));
    }
  }
}

// Common algorithm for arithmetic calculation between two vectors.
void calc_arithmetic_generic(rt_function_t *f,
                             float (*calc_func)(float, float)) {
  calc_dim_arithmetic_generic(f->outputs[0], f->inputs[0], f->inputs[1], 0, 0,
                              0, 0, calc_func);
}

// Common algorithm for arithmetic calculation between vector and scalar value.
void calc_scalar_generic(rt_function_t *f, float value,
                         float (*calc_func)(float, float)) {
  int out_size = calc_shape_size(f->outputs[0]->shape);
  rt_variable_t *input = f->inputs[0];
  rt_variable_getter get_input = select_getter(input);
  rt_variable_t *output = f->outputs[0];
  rt_variable_setter set_output = select_setter(output);

  int i; // Iterator
  for (i = 0; i < out_size; i++) {
    float x = get_input(input, i);
    set_output(output, i, calc_func(x, value));
  }
}
