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

#include <assert.h>

#include "list.h"

rt_list_t allocate_list(int length) {
  rt_list_t ret;
  assert(length >= 0);
  ret.size = length;
  ret.data = (int *)rt_malloc_func(sizeof(int) * length);
  return ret;
}

void free_list(rt_list_t s) {
  if (s.data) {
    rt_free_func(s.data);
  }
  s.data = 0;
}

rt_list_t clone_list(rt_list_t src) {
  int i;
  rt_list_t dst = allocate_list(src.size);
  for (i = 0; i < src.size; i++) {
    dst.data[i] = src.data[i];
  }
  return dst;
}
