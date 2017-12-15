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

#include <nnablart/functions.h>
#include "accessor.h"

float getFloat(rt_variable_t *variable, nn_size_t pos) {
  return GET_FLOAT(variable, pos);
}

float getInt16(rt_variable_t *variable, nn_size_t pos) {
  return GET_INT16(variable, pos);
}

float getInt8(rt_variable_t *variable, nn_size_t pos) { return GET_INT8(variable, pos); }

float getSign(rt_variable_t *variable, nn_size_t pos) {
  if ((*((uint32_t *)(variable->data) + (pos / 32))) & (1 << (pos % 32))) {
    return 1;
  }
  return -1;
}

void setFloat(rt_variable_t *variable, nn_size_t pos, float value) {
  *((float *)(variable->data) + pos) = value;
}

void setInt16(rt_variable_t *variable, nn_size_t pos, float value) {
  *((int16_t *)(variable->data) + pos) = (int16_t)(value / variable->coefficient);
}

void setInt8(rt_variable_t *variable, nn_size_t pos, float value) {
  *((int8_t *)(variable->data) + pos) = (int8_t)(value / variable->coefficient);
}

void setSign(rt_variable_t *variable, nn_size_t pos, float value) {
  if (value >= 0) {
    *((uint32_t *)(variable->data) + (pos / 32)) |= 1 << (pos % 32);
  } else {
    *((uint32_t *)(variable->data) + (pos / 32)) &= ~(1 << (pos % 32));
  }
}

static rt_variable_getter getter_list[END_OF_NN_DATA_TYPE] = {
  getFloat, getInt16, getInt8, getSign
};

rt_variable_getter select_getter(nn_data_type_t data_type)
{
  return getter_list[data_type];
}

static rt_variable_setter setter_list[END_OF_NN_DATA_TYPE] = {
  setFloat, setInt16, setInt8, setSign
};

rt_variable_setter select_setter(nn_data_type_t data_type)
{
  return setter_list[data_type];
}


