// Copyright (c) 2020 Sony Corporation. All Rights Reserved.
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

#include "../../utilities/fixedpoint.h"
#include "../../utilities/shape.h"
#include "arithmetic.h"
#include <math.h>

// Common algorithm for arithmetic calculation between two vectors has same
// dimension.
void calc_dim_arithmetic_fixed8(rt_variable_t *output, rt_variable_t *input1,
                                rt_variable_t *input2, int dim_index, int y_out,
                                int y_in1, int y_in2,
                                int8_t (*calc_func)(int8_t, int8_t)) {
  int dim_size = output->shape.size;
  int x_size_out = output->shape.data[dim_index];
  int x_size_in1 = input1->shape.data[dim_index];
  int x_size_in2 = input2->shape.data[dim_index];
  for (int x_out = 0; x_out < x_size_out; x_out++) {
    int x_in1 = (x_out % x_size_in1);
    int x_in2 = (x_out % x_size_in2);
    int z_out = y_out * x_size_out + x_out;
    int z_in1 = y_in1 * x_size_in1 + x_in1;
    int z_in2 = y_in2 * x_size_in2 + x_in2;
    if (dim_index + 1 < dim_size) {
      calc_dim_arithmetic_fixed8(output, input1, input2, dim_index + 1, z_out,
                                 z_in1, z_in2, calc_func);
    } else {
      int8_t *data_out = output->data;
      int8_t *data_in1 = input1->data;
      int8_t *data_in2 = input2->data;
      data_out[z_out] = calc_func(data_in1[z_in1], data_in2[z_in2]);
    }
  }
}

// Fixed-point mul and div require larger buffer and rescaling
void calc_dim_arithmetic_fixed8_largebuff(
    rt_variable_t *output, rt_variable_t *input1, rt_variable_t *input2,
    int dim_index, int y_out, int y_in1, int y_in2,
    int16_t (*calc_func)(int8_t, int8_t, int), int rescaling_factor) {

  int dim_size = output->shape.size;
  int x_size_out = output->shape.data[dim_index];
  int x_size_in1 = input1->shape.data[dim_index];
  int x_size_in2 = input2->shape.data[dim_index];
  for (int x_out = 0; x_out < x_size_out; x_out++) {
    int x_in1 = (x_out % x_size_in1);
    int x_in2 = (x_out % x_size_in2);
    int z_out = y_out * x_size_out + x_out;
    int z_in1 = y_in1 * x_size_in1 + x_in1;
    int z_in2 = y_in2 * x_size_in2 + x_in2;
    if (dim_index + 1 < dim_size) {
      calc_dim_arithmetic_fixed8_largebuff(output, input1, input2,
                                           dim_index + 1, z_out, z_in1, z_in2,
                                           calc_func, rescaling_factor);
    } else {
      int8_t *data_out = output->data;
      int8_t *data_in1 = input1->data;
      int8_t *data_in2 = input2->data;
      int16_t output_largebuff =
          calc_func(data_in1[z_in1], data_in2[z_in2], rescaling_factor);
      data_out[z_out] = saturate16_to_8(output_largebuff);
    }
  }
}

void calc_dim_arithmetic_fixed16(rt_variable_t *output, rt_variable_t *input1,
                                 rt_variable_t *input2, int dim_index,
                                 int y_out, int y_in1, int y_in2,
                                 int16_t (*calc_func)(int16_t, int16_t)) {
  int dim_size = output->shape.size;
  int x_size_out = output->shape.data[dim_index];
  int x_size_in1 = input1->shape.data[dim_index];
  int x_size_in2 = input2->shape.data[dim_index];
  for (int x_out = 0; x_out < x_size_out; x_out++) {
    int x_in1 = (x_out % x_size_in1);
    int x_in2 = (x_out % x_size_in2);
    int z_out = y_out * x_size_out + x_out;
    int z_in1 = y_in1 * x_size_in1 + x_in1;
    int z_in2 = y_in2 * x_size_in2 + x_in2;
    if (dim_index + 1 < dim_size) {
      calc_dim_arithmetic_fixed16(output, input1, input2, dim_index + 1, z_out,
                                  z_in1, z_in2, calc_func);
    } else {
      int16_t *data_out = output->data;
      int16_t *data_in1 = input1->data;
      int16_t *data_in2 = input2->data;
      data_out[z_out] = calc_func(data_in1[z_in1], data_in2[z_in2]);
    }
  }
}

// Fixed-point mul and div require larger buffer and rescaling
void calc_dim_arithmetic_fixed16_largebuff(
    rt_variable_t *output, rt_variable_t *input1, rt_variable_t *input2,
    int dim_index, int y_out, int y_in1, int y_in2,
    int32_t (*calc_func)(int16_t, int16_t, int), int rescaling_factor) {

  int dim_size = output->shape.size;
  int x_size_out = output->shape.data[dim_index];
  int x_size_in1 = input1->shape.data[dim_index];
  int x_size_in2 = input2->shape.data[dim_index];
  for (int x_out = 0; x_out < x_size_out; x_out++) {
    int x_in1 = (x_out % x_size_in1);
    int x_in2 = (x_out % x_size_in2);
    int z_out = y_out * x_size_out + x_out;
    int z_in1 = y_in1 * x_size_in1 + x_in1;
    int z_in2 = y_in2 * x_size_in2 + x_in2;
    if (dim_index + 1 < dim_size) {
      calc_dim_arithmetic_fixed16_largebuff(output, input1, input2,
                                            dim_index + 1, z_out, z_in1, z_in2,
                                            calc_func, rescaling_factor);
    } else {
      int16_t *data_out = output->data;
      int16_t *data_in1 = input1->data;
      int16_t *data_in2 = input2->data;
      int32_t output_largebuff =
          calc_func(data_in1[z_in1], data_in2[z_in2], rescaling_factor);
      data_out[z_out] = saturate32_to_16(output_largebuff);
    }
  }
}

void equalize_bits_fixed8(rt_variable_t *v1, rt_variable_t *v2) {
  // Rescale two arrays to have the same number of range bits.
  // Downscale the array having most precision bits.

  if (v1->fp_pos == v2->fp_pos) {
    return;
  }

  const rt_variable_t *to_keep = v1->fp_pos < v2->fp_pos ? v1 : v2;
  rt_variable_t *to_rescale = to_keep == v1 ? v2 : v1;
  const unsigned rescale_size = calc_shape_size(to_rescale->shape);

  rescale_fixed8(to_rescale->data, rescale_size, to_rescale->fp_pos,
                 to_keep->fp_pos);

  // Update fp_pos for rescaled variable
  to_rescale->fp_pos = to_keep->fp_pos;

  return;
}

void equalize_bits_fixed16(rt_variable_t *v1, rt_variable_t *v2) {
  // Rescale two arrays to have the same number of range bits.
  // Downscale the array having most precision bits.

  if (v1->fp_pos == v2->fp_pos) {
    return;
  }

  const rt_variable_t *to_keep = v1->fp_pos < v2->fp_pos ? v1 : v2;
  rt_variable_t *to_rescale = to_keep == v1 ? v2 : v1;
  const unsigned rescale_size = calc_shape_size(to_rescale->shape);

  rescale_fixed16(to_rescale->data, rescale_size, to_rescale->fp_pos,
                  to_keep->fp_pos);

  // Update fp_pos for rescaled variable
  to_rescale->fp_pos = to_keep->fp_pos;

  return;
}

// Common algorithm for arithmetic calculation between two vectors.
void calc_arithmetic_fixed8(rt_function_t *f,
                            int8_t (*calc_func)(int8_t, int8_t)) {
  calc_dim_arithmetic_fixed8(f->outputs[0], f->inputs[0], f->inputs[1], 0, 0, 0,
                             0, calc_func);
}

void calc_arithmetic_fixed16(rt_function_t *f,
                             int16_t (*calc_func)(int16_t, int16_t)) {
  calc_dim_arithmetic_fixed16(f->outputs[0], f->inputs[0], f->inputs[1], 0, 0,
                              0, 0, calc_func);
}

void calc_arithmetic_fixed16_largebuff(rt_function_t *f,
                                       int32_t (*calc_func)(int16_t, int16_t,
                                                            int),
                                       int rescaling_factor) {
  calc_dim_arithmetic_fixed16_largebuff(f->outputs[0], f->inputs[0],
                                        f->inputs[1], 0, 0, 0, 0, calc_func,
                                        rescaling_factor);
}

void calc_arithmetic_fixed8_largebuff(rt_function_t *f,
                                      int16_t (*calc_func)(int8_t, int8_t, int),
                                      int rescaling_factor) {
  calc_dim_arithmetic_fixed8_largebuff(f->outputs[0], f->inputs[0],
                                       f->inputs[1], 0, 0, 0, 0, calc_func,
                                       rescaling_factor);
}

// // Common algorithm for arithmetic calculation between vector and scalar
// // value.
void calc_scalar_fixed8(rt_function_t *f, float value,
                        int8_t (*calc_func)(int8_t, int8_t)) {
  int out_size = calc_shape_size(f->outputs[0]->shape);
  int8_t *input = f->inputs[0]->data;
  int8_t *output = f->outputs[0]->data;
  int8_t value_int = float_to_fixed8(value, f->inputs[0]->fp_pos);
  int i; // Iterator
  for (i = 0; i < out_size; i++) {
    output[i] = calc_func(input[i], value_int);
  }
}

void calc_scalar_fixed16(rt_function_t *f, float value,
                         int16_t (*calc_func)(int16_t, int16_t)) {
  int out_size = calc_shape_size(f->outputs[0]->shape);
  int16_t *input = f->inputs[0]->data;
  int16_t *output = f->outputs[0]->data;
  int16_t value_int = float_to_fixed16(value, f->inputs[0]->fp_pos);
  int i; // Iterator
  for (i = 0; i < out_size; i++) {
    output[i] = calc_func(input[i], value_int);
  }
}

void calc_scalar_fixed8_largebuff(rt_function_t *f, float value,
                                  int16_t (*calc_func)(int8_t, int8_t, int)) {
  int out_size = calc_shape_size(f->outputs[0]->shape);
  int8_t *input = f->inputs[0]->data;
  int8_t *output = f->outputs[0]->data;

  // Compute needed number of range bits to represent given float.
  // Notice that it should be log(abs(x)) instead of log(1+abs(x)), but the
  // implemented
  // formulation makes sure the output of the log is positive.
  const short n_dec_bits_scalar =
      roundf(fmaxf(0.0, 8.0 - (1.0 + log2f(1.0 + fabsf(value)))));

  // Convert scalar value to fixed-point.
  const int8_t value_int = float_to_fixed8(value, n_dec_bits_scalar);
  const int n_bits_rescale =
      f->inputs[0]->fp_pos + n_dec_bits_scalar - f->outputs[0]->fp_pos;
  const int rescaling_factor = 1 << n_bits_rescale;
  int i; // Iterator
  for (i = 0; i < out_size; i++) {
    int16_t output_largebuff = calc_func(input[i], value_int, rescaling_factor);
    output[i] = saturate16_to_8(output_largebuff);
  }
}

void calc_scalar_fixed16_largebuff(rt_function_t *f, float value,
                                   int32_t (*calc_func)(int16_t, int16_t,
                                                        int)) {
  int out_size = calc_shape_size(f->outputs[0]->shape);
  int16_t *input = f->inputs[0]->data;
  int16_t *output = f->outputs[0]->data;

  // Compute needed number of range bits to represent given float.
  // Notice that it should be log(x) instead of log(1+x), but the implemented
  // formulation makes sure the output of the log is positive.
  const short n_dec_bits_scalar =
      roundf(fmaxf(0.0, 16.0 - (1.0 + log2f(1.0 + fabsf(value)))));

  // Convert scalar value to fixed-point.
  const int16_t value_int = float_to_fixed16(value, n_dec_bits_scalar);
  const int n_bits_rescale =
      f->inputs[0]->fp_pos + n_dec_bits_scalar - f->outputs[0]->fp_pos;
  const int rescaling_factor = 1 << n_bits_rescale;
  int i; // Iterator
  for (i = 0; i < out_size; i++) {
    int32_t output_largebuff = calc_func(input[i], value_int, rescaling_factor);
    output[i] = saturate32_to_16(output_largebuff);
  }
}

// calc callbacks (8-bit)

int8_t calc_sub_fixed8(int8_t v1, int8_t v2) { return sub_sat8(v1, v2); }

int8_t calc_rsub_fixed8(int8_t v1, int8_t v2) { return sub_sat8(v2, v1); }

// int8_t calc_rpow_fixed8(int8_t v1, int8_t v2) { return powf(v2, v1); }

// int8_t calc_rdiv_fixed8(int8_t v1, int8_t v2) { return v2 / v1; }

// int8_t calc_pow_fixed8(int8_t v1, int8_t v2) { return powf(v1, v2); }

int16_t calc_mul_fixed8(int8_t v1, int8_t v2, int rescaling_factor) {
  return ((int16_t)v1 * (int16_t)v2) / rescaling_factor;
}

int8_t select_min_fixed8(int8_t v1, int8_t v2) { return (v1 < v2) ? v1 : v2; }

int8_t select_max_fixed8(int8_t v1, int8_t v2) { return (v1 > v2) ? v1 : v2; }

int16_t calc_div_fixed8(int8_t v1, int8_t v2, int rescaling_factor) {
  return ((int16_t)v1 * rescaling_factor / (int16_t)v2);
}

int8_t calc_add_fixed8(int8_t v1, int8_t v2) { return sum_sat8(v1, v2); }

// calc callbacks (16-bit)

int16_t calc_sub_fixed16(int16_t v1, int16_t v2) { return sub_sat16(v1, v2); }

int16_t calc_rsub_fixed16(int16_t v1, int16_t v2) { return sub_sat16(v2, v1); }

// int16_t calc_rpow_fixed16(int16_t v1, int16_t v2) { return powf(v2, v1); }

// int16_t calc_rdiv_fixed16(int16_t v1, int16_t v2) { return v2 / v1; }

// int16_t calc_pow_fixed16(int16_t v1, int16_t v2) { return powf(v1, v2); }

int32_t calc_mul_fixed16(int16_t v1, int16_t v2, int rescaling_factor) {
  return ((int32_t)v1 * (int32_t)v2) / rescaling_factor;
}

int16_t select_min_fixed16(int16_t v1, int16_t v2) {
  return (v1 < v2) ? v1 : v2;
}

int16_t select_max_fixed16(int16_t v1, int16_t v2) {
  return (v1 > v2) ? v1 : v2;
}

int32_t calc_div_fixed16(int16_t v1, int16_t v2, int rescaling_factor) {
  return ((int32_t)v1 * rescaling_factor / (int32_t)v2);
}

int16_t calc_add_fixed16(int16_t v1, int16_t v2) { return sum_sat16(v1, v2); }
