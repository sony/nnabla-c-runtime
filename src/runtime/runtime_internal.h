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

/// @brief インデックス部分のサイズを計算します。
/// @note
/// マクロ内から利用するためのものであり、外部から利用することは想定していません。
#define NN_NETWORK_INDEX_SIZE(xNetwork)                                        \
  ((xNetwork)->memory.num_of_data * sizeof(pointer_index_t))

/// @brief データ部分のサイズを計算します。
/// @note
/// マクロ内から利用するためのものであり、外部から利用することは想定していません。
#define NN_NETWORK_DATA_SIZE(xNetwork) ((xNetwork)->memory.data_size)

/// @brief ネットワーク全体のデータサイズを計算します。
#define NN_NETWORK_SIZE(xNetwork)                                              \
  (sizeof(nn_network_t) + NN_NETWORK_INDEX_SIZE(xNetwork) +                    \
   NN_NETWORK_DATA_SIZE(xNetwork))

/// @brief インデックスエリアの先頭ポインタを返します。
/// @note
/// マクロ内から利用するためのものであり、外部から利用することは想定していません。
#define NN_NETWORK_INDEX_POINTER(xNetwork)                                     \
  ((pointer_index_t *)(((uint8_t *)xNetwork) + sizeof(nn_network_t)))

/// @brief データエリアの先頭ポインタを返します。
/// @note
/// マクロ内から利用するためのものであり、外部から利用することは想定していません。
#define NN_NETWORK_DATA_POINTER(xNetwork)                                      \
  ((uint8_t *)NN_NETWORK_INDEX_POINTER(xNetwork) +                             \
   NN_NETWORK_INDEX_SIZE(xNetwork))

/// @brief インデックスからポインタを返します。
#define NN_GET(xNetwork, xIndex)                                               \
  (NN_NETWORK_DATA_POINTER(xNetwork) +                                         \
   NN_NETWORK_INDEX_POINTER(xNetwork)[xIndex])

rt_list_t create_rt_list_from_nn_list(nn_network_t *n, nn_list_t list);
rt_function_context_t create_function_context(nn_network_t *n, rt_context_t *c,
                                              nn_function_t *function);

#endif // H_RUNTIME_INTERNAL_H_171220111925_
