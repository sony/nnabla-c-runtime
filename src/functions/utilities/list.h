// Copyright 2018,2019,2020,2021 Sony Corporation.
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

#ifndef H_LIST_H_171210064151_
#define H_LIST_H_171210064151_

#include <nnablart/functions.h>

/// Allocate shape
rt_list_t allocate_list(int length);

/// Free allocated shape.
void free_list(rt_list_t s);

/// Clone shape
///
/// list.shape will be allocated inside this function.
/// User must free cloned shape.
rt_list_t clone_list(rt_list_t src);

#endif // H_LIST_H_171210064151_
