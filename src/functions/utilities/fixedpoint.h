// Copyright 2020,2021 Sony Corporation.
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

#ifndef H_FIXEDPOINT_H
#define H_FIXEDPOINT_H

#include <math.h>
#include <stdint.h>

inline int sum_acc_sat8(int8_t *acc, int8_t b) {
  // Accumulate b into *acc, after cheking for overflow (8-bit accumulator)
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
  // Accumulate b into *acc, after cheking for overflow (16-bit accumulator)
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
  // Accumulate b into *acc, after cheking for overflow (32-bit accumulator)
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

inline int8_t saturate16_to_8(int16_t a) {
  // Integer 16-bit to integer 8-bit with overflow check.
  if (a >= INT8_MAX) {
    return INT8_MAX;
  } else if (a <= INT8_MIN) {
    return INT8_MIN;
  } else {
    return (int8_t)a;
  }
}

inline int8_t saturate32_to_8(int32_t a) {
  // Integer 32-bit to integer 8-bit with overflow check.
  if (a >= INT8_MAX) {
    return INT8_MAX;
  } else if (a <= INT8_MIN) {
    return INT8_MIN;
  } else {
    return (int8_t)a;
  }
}

inline int16_t saturate32_to_16(int32_t a) {
  // Integer 32-bit to integer 16-bit with overflow check.
  if (a >= INT16_MAX) {
    return INT16_MAX;
  } else if (a <= INT16_MIN) {
    return INT16_MIN;
  } else {
    return (int16_t)a;
  }
}

inline int16_t saturate64_to_16(int64_t a) {
  // Integer 64-bit to integer 16-bit with overflow check.
  if (a >= INT16_MAX) {
    return INT16_MAX;
  } else if (a <= INT16_MIN) {
    return INT16_MIN;
  } else {
    return (int16_t)a;
  }
}

inline int32_t saturate64_to_32(int64_t a) {
  // Integer 64-bit to integer 16-bit with overflow check.
  if (a >= INT32_MAX) {
    return INT32_MAX;
  } else if (a <= INT32_MIN) {
    return INT32_MIN;
  } else {
    return (int32_t)a;
  }
}

inline void rescale_fixed8(int8_t *arr, unsigned arr_size,
                           unsigned old_decimal_bits,
                           unsigned new_decimal_bits) {
  // Rescale an array of 8-bit fixed-point values,
  // from old_decimal_bits precision, to new_decimal_bits precision.

  const short n_bits_shift = old_decimal_bits - new_decimal_bits;
  if (n_bits_shift > 0) {
    const int8_t rescaling = 1 << n_bits_shift;
    for (int i = 0; i < arr_size; i++) {
      *(arr + i) /= rescaling;
    }
  } else if (n_bits_shift < 0) {
    const int16_t rescaling = 1 << -n_bits_shift;
    for (int i = 0; i < arr_size; i++) {
      *(arr + i) = saturate16_to_8(*(arr + i) * rescaling); // ovf could occur
    }
  }
}

inline void rescale_fixed16(int16_t *arr, unsigned arr_size,
                            unsigned old_decimal_bits,
                            unsigned new_decimal_bits) {
  // Rescale an array of 16-bit fixed-point values,
  // from old_decimal_bits precision, to new_decimal_bits precision.

  const short n_bits_shift = old_decimal_bits - new_decimal_bits;

  if (n_bits_shift > 0) {
    const int16_t rescaling = 1 << n_bits_shift;
    for (int i = 0; i < arr_size; i++) {
      *(arr + i) /= rescaling;
    }
  } else if (n_bits_shift < 0) {
    const int32_t rescaling = 1 << -n_bits_shift;
    for (int i = 0; i < arr_size; i++) {
      *(arr + i) = saturate32_to_16(*(arr + i) * rescaling);
    }
  }

  return;
}

inline int8_t rescale_scalar_fixed8(int8_t value, unsigned old_decimal_bits,
                                    unsigned new_decimal_bits) {
  // Rescale a single 8-bit fixed-point value,
  // from old_decimal_bits precision, to new_decimal_bits precision.
  const short n_bits_shift = old_decimal_bits - new_decimal_bits;
  if (n_bits_shift == 0) {
    return value;
  } else if (n_bits_shift > 0) {
    const int8_t rescaling = 1 << n_bits_shift;
    return value / rescaling;
  } else {
    const int16_t rescaling = 1 << -n_bits_shift;
    return saturate16_to_8(value * rescaling); // ovf could occur
  }
}

inline int16_t rescale_scalar_fixed16(int16_t value, unsigned old_decimal_bits,
                                      unsigned new_decimal_bits) {
  // Rescale a single 16-bit fixed-point value,
  // from old_decimal_bits precision, to new_decimal_bits precision.
  const short n_bits_shift = old_decimal_bits - new_decimal_bits;
  if (n_bits_shift == 0) {
    return value;
  } else if (n_bits_shift > 0) {
    const int16_t rescaling = 1 << n_bits_shift;
    return value / rescaling;
  } else {
    const int32_t rescaling = 1 << -n_bits_shift;
    return saturate32_to_16(value * rescaling); // ovf could occur
  }
}

inline int32_t rescale_scalar_fixed32(int32_t value, unsigned old_decimal_bits,
                                      unsigned new_decimal_bits) {
  // Rescale a single 32-bit fixed-point value,
  // from old_decimal_bits precision, to new_decimal_bits precision.
  const short n_bits_shift = old_decimal_bits - new_decimal_bits;
  if (n_bits_shift == 0) {
    return value;
  } else if (n_bits_shift > 0) {
    const int32_t rescaling = 1 << n_bits_shift;
    return value / rescaling;
  } else {
    const int64_t rescaling = 1 << -n_bits_shift;
    return saturate64_to_32(value * rescaling); // ovf could occur
  }
}

inline int8_t sum_sat8(int8_t v1, int8_t v2) {
  // Sum v1 and v2, after cheking for overflow.
  const int8_t result = v1 + v2;
  if (result < 0 && v1 > 0 && v2 > 0) {
    return INT8_MAX;
  } else if (result > 0 && v1 < 0 && v2 < 0) {
    return INT8_MIN;
  } else {
    return result;
  }
}

inline int16_t sum_sat16(int16_t v1, int16_t v2) {
  // Sum v1 and v2, after cheking for overflow.
  const int16_t result = v1 + v2;
  if (result < 0 && v1 > 0 && v2 > 0) {
    return INT16_MAX;
  } else if (result > 0 && v1 < 0 && v2 < 0) {
    return INT16_MIN;
  } else {
    return result;
  }
}

inline int8_t sub_sat8(int8_t v1, int8_t v2) {
  // Subtract v1 and v2, after cheking for overflow.
  const int8_t result = v1 - v2;
  if (result < 0 && v1 > 0 && v2 < 0) {
    return INT8_MAX;
  } else if (result > 0 && v1 < 0 && v2 > 0) {
    return INT8_MIN;
  } else {
    return result;
  }
}

inline int16_t sub_sat16(int16_t v1, int16_t v2) {
  // Subtract v1 and v2, after cheking for overflow.
  const int16_t result = v1 - v2;
  if (result < 0 && v1 > 0 && v2 < 0) {
    return INT16_MAX;
  } else if (result > 0 && v1 < 0 && v2 > 0) {
    return INT16_MIN;
  } else {
    return result;
  }
}

inline float fixed8_to_float(int8_t value, int n_precision_bits) {
  return ((float)value / (1 << n_precision_bits));
}

inline float fixed16_to_float(int16_t value, int n_precision_bits) {
  return ((float)value / (1 << n_precision_bits));
}

inline int8_t float_to_fixed8(float value, int n_precision_bits) {
  const float FIXED8_MAX =
      (1 << (8 - n_precision_bits - 1)) - (1 / (1 << n_precision_bits));
  const float FIXED8_MIN = -(1 << (8 - n_precision_bits - 1));

  if (value >= FIXED8_MAX) {
    return (int8_t)FIXED8_MAX;
  } else if (value <= FIXED8_MIN) {
    return (int8_t)FIXED8_MIN;
  } else {
    return (int8_t)roundf(value * (1 << n_precision_bits));
  }
}

inline int16_t float_to_fixed16(float value, int n_precision_bits) {
  const float FIXED16_MAX =
      (1 << (16 - n_precision_bits - 1)) - (1 / (1 << n_precision_bits));
  const float FIXED16_MIN = -(1 << (16 - n_precision_bits - 1));

  if (value >= FIXED16_MAX) {
    return (int16_t)FIXED16_MAX;
  } else if (value <= FIXED16_MIN) {
    return (int16_t)FIXED16_MIN;
  } else {
    return (int16_t)roundf(value * (1 << n_precision_bits));
  }
}

inline int16_t max16(int16_t v1, int16_t v2) { return v1 > v2 ? v1 : v2; }

inline int8_t max8(int8_t v1, int8_t v2) { return v1 > v2 ? v1 : v2; }

inline int16_t min16(int16_t v1, int16_t v2) { return v1 > v2 ? v2 : v1; }

inline int8_t min8(int8_t v1, int8_t v2) { return v1 > v2 ? v2 : v1; }

#endif // H_FIXEDPOINT_H
