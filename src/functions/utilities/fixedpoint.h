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

#ifndef H_FIXEDPOINT_H
#define H_FIXEDPOINT_H

#include <stdint.h>

inline int sum_acc_sat8(int8_t *acc, int8_t b) {
  int8_t result = *acc + b;
  if (*acc > 0 && b > 0 && result < 0) {
    *acc = INT8_MAX;
    return -1;
  } else if (*acc < 0 && b < 0 && result > 0) {
    *acc = INT8_MIN;
    return -1;
  } else {
    *acc = result;
    return 0;
  }
}

inline int sum_acc_sat16(int16_t *acc, int16_t b) {
  int16_t result = *acc + b;
  if (*acc > 0 && b > 0 && result < 0) {
    *acc = INT16_MAX;
    return -1;
  } else if (*acc < 0 && b < 0 && result > 0) {
    *acc = INT16_MIN;
    return -1;
  } else {
    *acc = result;
    return 0;
  }
}

inline int sum_acc_sat32(int32_t *acc, int32_t b) {
  int32_t result = *acc + b;
  if (*acc > 0 && b > 0 && result < 0) {
    *acc = INT32_MAX;
    return -1;
  } else if (*acc < 0 && b < 0 && result > 0) {
    *acc = INT32_MIN;
    return -1;
  } else {
    *acc = result;
    return 0;
  }
}

inline int8_t saturate32_to_8(int32_t a) {
  if (a >= INT8_MAX) {
    return INT8_MAX;
  } else if (a <= INT8_MIN) {
    return INT8_MIN;
  } else {
    return (int8_t)a;
  }
}

inline int16_t saturate64_to_16(int64_t a) {
  if (a >= INT16_MAX) {
    return INT16_MAX;
  } else if (a <= INT16_MIN) {
    return INT16_MIN;
  } else {
    return (int16_t)a;
  }
}

#endif // H_FIXEDPOINT_H
