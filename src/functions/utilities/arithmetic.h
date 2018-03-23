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

void calc_arithmetic(rt_function_t *f, float(*calc_func)(float, float));
void calc_scalar(rt_function_t *f, float value, float(*calc_func)(float, float));
void calc_scalar(rt_function_t *f, float value,
                 float (*calc_func)(float, float));
float calc_sub(float v1, float v2);
float calc_rsub(float v1, float v2);
float calc_rpow(float v1, float v2);
float calc_rdiv(float v1, float v2);
float calc_pow(float v1, float v2);
float calc_mul(float v1, float v2);
float select_min(float v1, float v2);
float select_max(float v1, float v2);
float calc_add(float v1, float v2);

#endif // H_ARITHMETIC_H_
