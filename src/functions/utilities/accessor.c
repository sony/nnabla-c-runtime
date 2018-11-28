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
#include "accessor.h"
#include "shape.h"
#include <string.h>

float get_float(rt_variable_t *variable, nn_size_t pos) {
  return GET_FLOAT(variable, pos);
}

float get_int16(rt_variable_t *variable, nn_size_t pos) {
  return GET_INT16(variable, pos);
}

float get_int8(rt_variable_t *variable, nn_size_t pos) {
  return GET_INT8(variable, pos);
}

float get_sign(rt_variable_t *variable, nn_size_t pos) {
  if ((*((uint32_t *)(variable->data) + (pos / 32))) & (1 << (pos % 32))) {
    return 1;
  }
  return -1;
}

void set_float(rt_variable_t *variable, nn_size_t pos, float value) {
  *((float *)(variable->data) + pos) = value;
}

void set_int16(rt_variable_t *variable, nn_size_t pos, float value) {
  value /= variable->coefficient;
  if (value >= INT16_MAX) {
    *((int16_t *)(variable->data) + pos) = INT16_MAX;
  } else if (value <= INT16_MIN) {
    *((int16_t *)(variable->data) + pos) = INT16_MIN;
  } else {
    *((int16_t *)(variable->data) + pos) = (int16_t)value;
  }
}

void set_int8(rt_variable_t *variable, nn_size_t pos, float value) {
  value /= variable->coefficient;
  if (value >= INT8_MAX) {
    *((int8_t *)(variable->data) + pos) = INT8_MAX;
  } else if (value <= INT8_MIN) {
    *((int8_t *)(variable->data) + pos) = INT8_MIN;
  } else {
    *((int8_t *)(variable->data) + pos) = (int8_t)value;
  }
}

void set_sign(rt_variable_t *variable, nn_size_t pos, float value) {
  if (value >= 0) {
    *((uint32_t *)(variable->data) + (pos / 32)) |= 1 << (pos % 32);
  } else {
    *((uint32_t *)(variable->data) + (pos / 32)) &= ~(1 << (pos % 32));
  }
}

static rt_variable_getter getter_list[END_OF_NN_DATA_TYPE] = {
    get_float, get_int16, get_int8, get_sign};

rt_variable_getter select_getter(rt_variable_t *variable) {
  return getter_list[variable->type];
}

static rt_variable_setter setter_list[END_OF_NN_DATA_TYPE] = {
    set_float, set_int16, set_int8, set_sign};

rt_variable_setter select_setter(rt_variable_t *variable) {
  return setter_list[variable->type];
}

void fill_variable_with(rt_variable_t *variable, int8_t value) {
  int size = calc_shape_size(variable->shape);

  switch (variable->type) {
  case NN_DATA_TYPE_FLOAT:
    size *= sizeof(float);
    break;

  case NN_DATA_TYPE_INT16:
    size *= sizeof(uint16_t);
    break;

  case NN_DATA_TYPE_INT8:
    size *= sizeof(uint8_t);
    break;

  case NN_DATA_TYPE_SIGN:
    size >>= 3;
    break;

  default:; // Do nothing
  }

  memset(variable->data, 0, size);
}