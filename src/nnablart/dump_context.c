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

#include <nnablart/network.h>
#include <nnablart/runtime.h>

#include "../runtime/context.h"

void dump_context(void *context) {
  int i, j; // Iterator

  rt_context_t *c = context;
  printf("CONTEXT: Has %d variables\n", c->num_of_variables);
  for (i = 0; i < c->num_of_variables; i++) {
    printf("CONTEXT: Variable[%d]: Shape ( ", i);
    for (j = 0; j < c->variables[i].shape.size; j++) {
      printf(" %d", c->variables[i].shape.data[j]);
    }
    printf(" )\n");
  }
}
