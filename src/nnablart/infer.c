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
#include <stdio.h>
#include <string.h>

#include <nnablart/network.h>
#include <nnablart/runtime.h>

int infer(nn_network_t *net, int argc, char *argv[]) {
  WHOAMI("%s\n", __func__);
  int i;
  for(i = 0; i < argc; i++ ){
    printf("     %d: %s\n",i, argv[i]);
  }

  rt_context_pointer context;
  rt_initialize_context(&context, net);
  rt_free_context(&context);
  return 0;
}
