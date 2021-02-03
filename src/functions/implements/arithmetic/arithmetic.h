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

#ifndef H_ARITHMETIC_H_
#define H_ARITHMETIC_H_

#include <nnablart/functions.h>

void calc_arithmetic(rt_function_t *f, float (*calc_func)(float, float));
void calc_arithmetic_generic(rt_function_t *f,
                             float (*calc_func)(float, float));
void calc_arithmetic_fixed8(rt_function_t *f,
                            int8_t (*calc_func)(int8_t, int8_t));
void calc_arithmetic_fixed16(rt_function_t *f,
                             int16_t (*calc_func)(int16_t, int16_t));
void calc_arithmetic_fixed8_largebuff(rt_function_t *f,
                                      int16_t (*calc_func)(int8_t, int8_t, int),
                                      int rescaling_factor);
void calc_arithmetic_fixed16_largebuff(rt_function_t *f,
                                       int32_t (*calc_func)(int16_t, int16_t,
                                                            int),
                                       int rescaling_factor);
void calc_scalar(rt_function_t *f, float value,
                 float (*calc_func)(float, float));

void calc_scalar_fixed8(rt_function_t *f, float value,
                        int8_t (*calc_func)(int8_t, int8_t));
void calc_scalar_fixed16(rt_function_t *f, float value,
                         int16_t (*calc_func)(int16_t, int16_t));
void calc_scalar_fixed8_largebuff(rt_function_t *f, float value,
                                  int16_t (*calc_func)(int8_t, int8_t,
                                                       int rescaling_factor));
void calc_scalar_fixed16_largebuff(rt_function_t *f, float value,
                                   int32_t (*calc_func)(int16_t, int16_t,
                                                        int rescaling_factor));
void calc_scalar_generic(rt_function_t *f, float value,
                         float (*calc_func)(float, float));

void equalize_bits_fixed8(rt_variable_t *v1, rt_variable_t *v2);
void equalize_bits_fixed16(rt_variable_t *v1, rt_variable_t *v2);

float calc_sub(float v1, float v2);
float calc_rsub(float v1, float v2);
float calc_rpow(float v1, float v2);
float calc_rdiv(float v1, float v2);
float calc_pow(float v1, float v2);
float calc_mul(float v1, float v2);
float select_min(float v1, float v2);
float select_max(float v1, float v2);
float calc_div(float v1, float v2);
float calc_add(float v1, float v2);

int8_t calc_sub_fixed8(int8_t v1, int8_t v2);
int8_t calc_rsub_fixed8(int8_t v1, int8_t v2);
// int8_t calc_rpow_fixed8(int8_t v1, int8_t v2);
// int8_t calc_rdiv_fixed8(int8_t v1, int8_t v2);
// int8_t calc_pow_fixed8(int8_t v1, int8_t v2);
int16_t calc_mul_fixed8(int8_t v1, int8_t v2, int rescaling_factor);
int8_t select_min_fixed8(int8_t v1, int8_t v2);
int8_t select_max_fixed8(int8_t v1, int8_t v2);
int16_t calc_div_fixed8(int8_t v1, int8_t v2, int rescaling_factor);
int8_t calc_add_fixed8(int8_t v1, int8_t v2);

int16_t calc_sub_fixed16(int16_t v1, int16_t v2);
int16_t calc_rsub_fixed16(int16_t v1, int16_t v2);
// int16_t calc_rpow_fixed16(int16_t v1, int16_t v2);
// int16_t calc_rdiv_fixed16(int16_t v1, int16_t v2);
// int16_t calc_pow_fixed16(int16_t v1, int16_t v2);
int32_t calc_mul_fixed16(int16_t v1, int16_t v2, int rescaling_factor);
int16_t select_min_fixed16(int16_t v1, int16_t v2);
int16_t select_max_fixed16(int16_t v1, int16_t v2);
int32_t calc_div_fixed16(int16_t v1, int16_t v2, int rescaling_factor);
int16_t calc_add_fixed16(int16_t v1, int16_t v2);

#endif // H_ARITHMETIC_H_
