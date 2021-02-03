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

#include "fixedpoint.h"

extern int sum_acc_sat8(int8_t *acc, int8_t b);
extern int sum_acc_sat16(int16_t *acc, int16_t b);
extern int sum_acc_sat32(int32_t *acc, int32_t b);

extern int8_t saturate16_to_8(int16_t a);
extern int8_t saturate32_to_8(int32_t a);
extern int16_t saturate32_to_16(int32_t a);
extern int16_t saturate64_to_16(int64_t a);
extern int32_t saturate64_to_32(int64_t a);

extern float fixed8_to_float(int8_t value, int n_precision_bits);
extern float fixed16_to_float(int16_t value, int n_precision_bits);

extern int8_t float_to_fixed8(float value, int n_precision_bits);
extern int16_t float_to_fixed16(float value, int n_precision_bits);

extern void rescale_fixed8(int8_t *arr, unsigned arr_size,
                           unsigned old_decimal_bits,
                           unsigned new_decimal_bits);
extern void rescale_fixed16(int16_t *arr, unsigned arr_size,
                            unsigned old_decimal_bits,
                            unsigned new_decimal_bits);
extern int8_t rescale_scalar_fixed8(int8_t value, unsigned old_decimal_bits,
                                    unsigned new_decimal_bits);
extern int16_t rescale_scalar_fixed16(int16_t value, unsigned old_decimal_bits,
                                      unsigned new_decimal_bits);
extern int32_t rescale_scalar_fixed32(int32_t value, unsigned old_decimal_bits,
                                      unsigned new_decimal_bits);
extern int8_t sum_sat8(int8_t v1, int8_t v2);
extern int16_t sum_sat16(int16_t v1, int16_t v2);

extern int8_t sub_sat8(int8_t v1, int8_t v2);
extern int16_t sub_sat16(int16_t v1, int16_t v2);

extern int8_t max8(int8_t v1, int8_t v2);
extern int16_t max16(int16_t v1, int16_t v2);

extern int8_t min8(int8_t v1, int8_t v2);
extern int16_t min16(int16_t v1, int16_t v2);
