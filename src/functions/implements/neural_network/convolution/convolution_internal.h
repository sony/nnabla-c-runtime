// Copyright (c) 2018 Sony Corporation. All Rights Reserved.
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

#ifndef H_CONVOLUTION_INTERNAL_H_171218154530_
#define H_CONVOLUTION_INTERNAL_H_171218154530_

#include "../../../utilities.h"

typedef rt_function_error_t (*exec_conv_func_t)(rt_function_t *f);

typedef struct {
  rt_variable_t* v;
  rt_list_t shape;
  rt_list_t stride;
  rt_variable_setter set;
  rt_variable_getter get;
  nn_size_t offset;
} var_t;

void var_free(var_t*);

typedef struct {
  var_t out_var;
  var_t in_var;
  var_t w_var;
  var_t b_var;
  exec_conv_func_t exec;
} convolution_private_t;

#define B  (0)   //batch dimension of input or output
#define G  (1)   //group dimension of input or output
#define I  (2)   //index dimension of input or output
#define H  (3)   //height of input or output
#define W  (4)   //width of input or output

#define KG  (0)   //group dimension of input or output
#define KO  (1)   //index of output
#define KI  (2)   //index of input
#define KH  (3)   //height of kernel
#define KW  (4)   //width of kernel

#define SPH  (0)  //height of stride/pad
#define SPW  (1)  //width of stride/pad

rt_function_error_t exec_convolution_generic(rt_function_t *f);

#endif // H_CONVOLUTION_INTERNAL_H_171218154530_
