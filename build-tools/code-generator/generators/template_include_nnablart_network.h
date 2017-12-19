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

#ifndef H_NETWORK_H__
#define H_NETWORK_H__

#ifdef __cplusplus
extern "C" {{
#endif /* __cplusplus */

#include <stdint.h> // for fixed bit length integer type
#include <stdlib.h> // for size_t

#define NN_BINARY_FORMAT_VERSION {BINARY_VERSION}

/// @defgroup NetworkDefinitions Internal network representation
///
/// ネットワークの構造をメモリ上に格納するための構造体と、データにアク
/// セスするためのマクロ群から構成されています。ネットワークデータを保
/// 存する際にシリアライズを不要にするため、データへのアクセスは全てポ
/// インタではなく、データバッファ内のインデックスを用いて行います。
///
///
/// @{{

typedef int32_t pointer_index_t; ///< データの場所を示すインデックス
typedef uint32_t nn_size_t; ///< データの場所を示すインデックス

/// @brief 整数のリスト
typedef struct {{
  nn_size_t size;       ///< リストのサイズ
  pointer_index_t list; ///< リストデータへのインデックス
}} nn_list_t;

/// @brief Data types.
typedef enum {{
  NN_DATA_TYPE_FLOAT, ///< 32bit float.
  NN_DATA_TYPE_INT16, ///< 16bit integer.
  NN_DATA_TYPE_INT8,  ///<  8bit integer.
  NN_DATA_TYPE_SIGN,   ///< Binary.
  END_OF_NN_DATA_TYPE
}} nn_data_type_t;

/// @brief Definition of Variable.
typedef struct {{
  uint32_t id;             ///< Identifier
  nn_list_t shape;         ///< Shape
  nn_data_type_t type : 4; ///< Type of param values
  unsigned int fp_pos : 4; ///< floating point position.
  int32_t data_index;      ///< Location of data. If negative, it means data buffer index. Otherwize it means location of data in memory.
}} nn_variable_t;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup Functions エッジの定義
/// @brief Definitions for functions.
/// @{{

/// @brief Function types.
typedef enum {{
    {FUNCTION_ENUMS}
}} nn_function_type_t;

/// @brief Common definition of Function.
/// This type is to be used for the function does not have arguements.
/// @{{
typedef struct {{
  nn_function_type_t type; ///< Common: type of function.
  nn_list_t inputs;        ///< Common: List of input variables.
  nn_list_t outputs;       ///< Common: List of output variables.
}} nn_function_t;

/// @}}

{FUNCTION_DEFINES}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup Network ネットワーク定義
/// @brief Definitions for network.
/// @{{

typedef struct {{
  nn_size_t num_of_data;
  nn_size_t data_size;
}} nn_memory_t;

/// @brief Definition of Network.
///
typedef struct {{
  uint32_t version;     ///< nnablart version.
  nn_list_t variables;  ///< list of nn_variable_t
  nn_list_t functions;  ///< list of nn_function_t
  nn_list_t inputs;     ///< list of input variable ids
  nn_list_t outputs;    ///< list of output variable ids
  nn_memory_t memory;   ///< memory to store all data.
}} nn_network_t;

/// @}}
/// @}}
/// @}}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup ErrorCodes
///
/// @{{
#define NN_ERROR_CODE_NOERROR (0)
/// @}}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup DebugFunctions デバッグ用
///
/// @{{
#ifndef WHOAMI
#define WHOAMI(...)                                                            \
  {{                                                                           \
    printf("%s:%d :", __FILE__, __LINE__);                                     \
    printf(__VA_ARGS__);                                                       \
    fflush(stdout);                                                            \
  }}
#endif // WHOAMI
/// @}}

#ifdef __cplusplus
}}
#endif /* __cplusplus */

#endif // H_NETWORK_H__
