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

#ifndef H_RUNTIME_INTERNAL_H_171220111925_
#define H_RUNTIME_INTERNAL_H_171220111925_

#include "context.h"

/// @brief Calculate index size.
/// @note It is intended to internal use, and not assumed to use from the
/// outside.
#define NN_NETWORK_INDEX_SIZE(xNetwork)                                        \
  ((xNetwork)->memory.num_of_data * sizeof(pointer_index_t))

/// @brief Data size.
/// @note It is intended to internal use, and not assumed to use from the
/// outside.
#define NN_NETWORK_DATA_SIZE(xNetwork) ((xNetwork)->memory.data_size)

/// @brief Size of whole network.
#define NN_NETWORK_SIZE(xNetwork)                                              \
  (sizeof(nn_network_t) + NN_NETWORK_INDEX_SIZE(xNetwork) +                    \
   NN_NETWORK_DATA_SIZE(xNetwork))

/// @brief Get pointer of index area.
/// @note It is intended to internal use, and not assumed to use from the
/// outside.
#define NN_NETWORK_INDEX_POINTER(xNetwork)                                     \
  ((pointer_index_t *)(((uint8_t *)xNetwork) + sizeof(nn_network_t)))

/// @brief Get pointer of data area.
/// @note It is intended to internal use, and not assumed to use from the
/// outside.
#define NN_NETWORK_DATA_POINTER(xNetwork)                                      \
  ((uint8_t *)NN_NETWORK_INDEX_POINTER(xNetwork) +                             \
   NN_NETWORK_INDEX_SIZE(xNetwork))

/// @brief Get pointer from index.
#define NN_GET(xNetwork, xIndex)                                               \
  (NN_NETWORK_DATA_POINTER(xNetwork) +                                         \
   NN_NETWORK_INDEX_POINTER(xNetwork)[xIndex])

rt_list_t create_rt_list_from_nn_list(nn_network_t *n, nn_list_t list);

rt_function_context_t allocate_function_io(nn_network_t *n, rt_context_t *c,
                                           nn_function_t *function);

void allocate_function_context(nn_network_t *n, nn_function_t *function,
                               rt_function_context_t *function_context);

#endif // H_RUNTIME_INTERNAL_H_171220111925_
