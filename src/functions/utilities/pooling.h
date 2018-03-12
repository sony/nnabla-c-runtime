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

#ifndef H_POOLING_H_
#define H_POOLING_H_

#include <nnablart/functions.h>

/// Calculate start value.
int calc_start_value(int iy, int stride, int pad);

/// Calculate end value.
int calc_end_value(int start, int kernel, int x, int pad);

#endif // H_POOLING_H_
