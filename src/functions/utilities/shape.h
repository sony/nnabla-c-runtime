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

#ifndef H_SHAPE_H_171218133433_
#define H_SHAPE_H_171218133433_

#include "list.h"
#include <nnablart/functions.h>

////////////////////////////////////////////////////////////////////////////////
/// @ingroup Utilities

/// @defgroup ShapeFunction ShapeFunction
/// @{

/// Calc vector axis at specified data pos.
void pos_to_shape(rt_list_t out, rt_list_t shape, int pos);

/// Calc data position at specified vector axis.
int shape_to_pos(rt_list_t s, rt_list_t pos);

/// If s has specified num, return position. Otherwise return -1.
int find_num_in_shape(rt_list_t s, int num);

/// Calclate data size with shape
int calc_shape_size(rt_list_t shape);

/// Calculate multiplication result of variable->shape from shape_begin to
/// shape_end
int shape_product_of(const rt_variable_t *v, unsigned shape_begin,
                     unsigned shape_end);

/// Helper for getting strides of C contiguous memory arrangement.
rt_list_t calc_contiguous_strides(rt_list_t shape);

/// @}

#endif // H_SHAPE_H_171218133433_
