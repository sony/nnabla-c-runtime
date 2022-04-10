// Copyright 2022 Sony Group Corporation.
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
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include <nnablart/functions.h>

#define OF(t) offsetof(t, data)

// convolution family
static_assert(OF(convolution_local_context_t) == OF(depthwise_convolution_local_context_t), "Invalid struct!");
//static_assert(OF(convolution_local_context_t) == OF(fused_convolution_local_context_t), "Invalid struct!");
//static_assert(OF(convolution_local_context_t) == OF(deformable_convolution_local_context_t), "Invalid struct!");
static_assert(OF(convolution_local_context_t) == OF(binary_connect_convolution_local_context_t), "Invalid struct!");
//static_assert(OF(convolution_local_context_t) == OF(inq_convolution_local_context_t), "Invalid struct!");
static_assert(OF(convolution_local_context_t) == OF(binary_weight_convolution_local_context_t), "Invalid struct!");


// affine family
static_assert(OF(affine_local_context_t) == OF(binary_connect_affine_local_context_t), "Invalid struct!");
static_assert(OF(affine_local_context_t) == OF(binary_weight_affine_local_context_t), "Invalid struct!");
//static_assert(OF(affine_local_context_t) == OF(inq_affine_local_context_t), "Invalid struct!");

// deconvolution family
//static_assert(OF(deconvolution_local_context_t) == OF(depthwise_deconvolution_local_context_t), "Invalid struct!");


int main(int argc, const char* argv[])
{
    return 0;
}
