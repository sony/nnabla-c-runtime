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

#ifndef H_ACCESOR_H_171210064532_
#define H_ACCESOR_H_171210064532_

#include <nnablart/functions.h>

#define GET_FLOAT(xVariable, xPos) (*((float *)((xVariable)->data) + (xPos)))
#define GET_INT16(xVariable, xPos)                                             \
  ((xVariable)->coefficient *                                                  \
   (float)(*((int16_t *)((xVariable)->data) + (xPos))))
#define GET_INT8(xVariable, xPos)                                              \
  ((xVariable)->coefficient *                                                  \
   (float)(*((int8_t *)((xVariable)->data) + (xPos))))
#define GET_SIGN(xVariable, xPos) getSign(xVariable, xPos)

float get_float(rt_variable_t *variable, nn_size_t pos);
float get_int16(rt_variable_t *variable, nn_size_t pos);
float get_int8(rt_variable_t *variable, nn_size_t pos);
float get_sign(rt_variable_t *variable, nn_size_t pos);

void set_float(rt_variable_t *variable, nn_size_t pos, float value);
void set_int16(rt_variable_t *variable, nn_size_t pos, float value);
void set_int8(rt_variable_t *variable, nn_size_t pos, float value);
void set_sign(rt_variable_t *variable, nn_size_t pos, float value);

typedef float (*rt_variable_getter)(rt_variable_t *, nn_size_t);
rt_variable_getter select_getter(rt_variable_t *variable);

typedef void (*rt_variable_setter)(rt_variable_t *, nn_size_t, float);
rt_variable_setter select_setter(rt_variable_t *variable);

void fill_variable_with(rt_variable_t *variable, int8_t value);

#endif // H_ACCESSOR_H_171210064532_
