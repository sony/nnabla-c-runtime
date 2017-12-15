// -*- coding:utf-8 -*-
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

/// @brief Definition of Parameter.
typedef struct {{
  uint32_t variable_id; ///< Variable that uses this parameter.
  nn_list_t shape;      ///< Shape of param
  nn_data_type_t type; ///< Type of param values
  nn_size_t scale;      ///< Scale of param values
  pointer_index_t data; ///< Location of param data
}} nn_param_t;

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

/// @brief Definition of Variable.
typedef struct {{
  uint32_t id;
  nn_list_t shape;
  int32_t buffer_index;
}} nn_variable_t;

typedef struct {{
  nn_size_t num_of_data;
  nn_size_t data_size;
}} nn_memory_t;

/// @brief Definition of Network.
///
typedef struct {{
  uint32_t version;     ///< nnablart version.
  nn_list_t inputs;     ///< list of nn_variable_t
  nn_list_t outputs;    ///< list of nn_variable_t
  nn_list_t functions;  ///< list of nn_function_t
  nn_list_t parameters; ///< list of nn_param_t
  nn_list_t variables;  ///< list of nn_variable_t
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
  {{                                                                            \
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
