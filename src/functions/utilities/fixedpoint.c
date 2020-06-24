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
extern int8_t saturate32_to_8(int32_t a);
extern int16_t saturate64_to_16(int64_t a);
