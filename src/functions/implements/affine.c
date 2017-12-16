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

#include <nnablart/functions.h>

// Affine
void init_affine_config(affine_config_t *config, int32_t base_axis)
{
  WHOAMI(" %s\n", __func__);
}

void init_affine_local_context(rt_function_t *f)
{
  WHOAMI(" %s\n", __func__);
}

void free_affinelocal_context(rt_function_t *f)
{
  WHOAMI(" %s\n", __func__);
}

void exec_affine(rt_function_t *f)
{
  WHOAMI(" %s\n", __func__);
  int i; // iterator

  WHOAMI(" i:%d\n", f->num_of_inputs);
  for(i = 0; i < f->num_of_inputs; i++ ){
    WHOAMI("  i[%d]: %p %f\n", i, f->inputs[i], *((float*)(f->inputs[i])));
  }

  WHOAMI(" o:%d\n", f->num_of_outputs);
  for(i = 0; i < f->num_of_outputs; i++ ){
    WHOAMI("  o[%d]: %p %f\n", i, f->outputs[i], *((float*)(f->outputs[i])));
  }
  
  
  affine_config_t *config = (affine_config_t*)f->config;
  WHOAMI(" base_axis %d\n", config->base_axis);
  
}

