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

#include "../runtime/runtime_internal.h"
#include "dump_function.h"

int dump(nn_network_t *net, int argc, char *argv[]) {
  int i, j;
  WHOAMI("%s\n", __func__);

  printf("NNB: Version: [%d]\n", net->version);
  printf("NNB: Has %d buffers.\n", net->buffers.size);
  int *list = (int *)NN_GET(net, net->buffers.list);
  for (i = 0; i < net->buffers.size; i++) {
    printf("NNB: Buffer id:%d size:%d\n", i, *(list + i));
  }
  
  printf("NNB: Has %d variables.\n", net->variables.size);
  list = (int *)NN_GET(net, net->variables.list);
  for (i = 0; i < net->variables.size; i++) {
    nn_variable_t *var = (nn_variable_t *)(NN_GET(net, *(list + i)));
    printf("NNB: Variable id:         %d\n", var->id);
    printf("NNB: Variable shape:      (");
    int *shape_list = (int *)NN_GET(net, var->shape.list);
    for (j = 0; j < var->shape.size; j++) {
      printf(" %d", *(shape_list + j));
    }
    printf(" )\n");
    printf("NNB: Variable type:       %d\n", var->type);
    printf("NNB: Variable fp_pos:     %d\n", var->fp_pos);
    if(var->data_index < 0){
      printf("NNB: Variable data_index: Buffer[%d]\n", (-1 * var->data_index) - 1 );
    } else {
      printf("NNB: Variable data_index: %d\n", var->data_index);
    }
  }

  printf("NNB: Has %d functions.\n", net->functions.size);
  list = (int *)NN_GET(net, net->functions.list);
  for (i = 0; i < net->functions.size; i++) {
    dump_function(net, (nn_function_t *)(NN_GET(net, *(list + i))));
  }

  printf("NNB: Has %d inputs.\n", net->inputs.size);
  list = (int *)NN_GET(net, net->inputs.list);
  for (i = 0; i < net->inputs.size; i++) {
    printf("NNB: Input[%d]   Variable id:%d\n", i, *(list + i));
  }

  printf("NNB: Has %d outputs.\n", net->outputs.size);
  list = (int *)NN_GET(net, net->outputs.list);
  for (i = 0; i < net->outputs.size; i++) {
    printf("NNB: Output[%d]  Variable id:%d\n", i, *(list + i));
  }

  return 0;
}
