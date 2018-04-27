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

#ifndef H_RUNTIME_H_
#define H_RUNTIME_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @defgroup Runtime Runtime APIs
/// @brief Calcurate feed forward neural network with @ref NetworkDefinitions
///
/// @ref Runtime provides following functions.
/// - @ref rt_initialize_context()
///   - @copydoc rt_initialize_context()
/// - @ref rt_free_context()
///   - @copydoc rt_free_context()
/// - @ref rt_num_of_input()
///   - @copydoc rt_num_of_input()
/// - @ref rt_input_size()
///   - @copydoc rt_input_size()
/// - @ref rt_input_dimension()
///   - @copydoc rt_input_dimension()
/// - @ref rt_input_shape()
///   - @copydoc rt_input_shape()
/// - @ref rt_num_of_output()
///   - @copydoc rt_num_of_output()
/// - @ref rt_output_size()
///   - @copydoc rt_output_size()
/// - @ref rt_output_dimension()
///   - @copydoc rt_output_dimension()
/// - @ref rt_output_shape()
///   - @copydoc rt_output_shape()
/// - @ref rt_forward()
///   - @copydoc rt_forward()
///
/// - Sequence
///   - Initialize
/// @li Initialize runtime context with @ref rt_initialize_context()
/// @li Allocate I/O buffers in size get from @ref rt_num_of_input(), @ref
/// rt_input_size(), @ref rt_num_of_output() and @ref rt_output_size()
///   - Diagram
/// @msc
///   UserApplication,Runtime;
///   UserApplication=>Runtime [label="rt_initialize_context(&context,
///   network)", URL="@ref rt_initialize_context()"];
///   UserApplication<<Runtime [label="(Context stored into context)" ];
///   UserApplication=>Runtime [label="rt_num_of_input(context)", URL="@ref
///   rt_num_of_input()"];
///   UserApplication<<Runtime [label="num_of_input" ];
///   --- [label="LOOP: index"];
///   UserApplication=>Runtime [label="rt_input_size(context, index)",
///   URL="@ref rt_input_size()"];
///   UserApplication<<Runtime [label="input_size[index]" ];
///   --- [label="LOOP_END: index"];
///   UserApplication=>UserApplication [label="(allocate input buffer)" ];
///   UserApplication=>Runtime [label="rt_num_of_output(context)",
///   URL="@ref rt_num_of_output()"];
///   UserApplication<<Runtime [label="num_of_output" ];
///   --- [label="LOOP: index"];
///   UserApplication=>Runtime [label="rt_output_size(context)", URL="@ref
///   rt_output_size()"];
///   UserApplication<<Runtime [label="output_size" ];
///   --- [label="LOOP_END: index"];
///   UserApplication=>UserApplication [label="(allocate output buffer)" ];
/// @endmsc
///   - Execute
/// @li Prepare input data and buffer to output.
/// @li @ref rt_forward()
/// @li Use output data in output buffer.
/// @msc
///   UserApplication,Runtime;
///   UserApplication=>UserApplication [label="(Copy input data into input
///   buffer)" ];
///   UserApplication=>Runtime [label="rt_forward(context, input_buffer,
///   output_buffer)", URL="@ref rt_forward()"];
///   Runtime=>Runtime [label="(Execute feedforward neural network)" ];
///   UserApplication<<Runtime [label="(Output stored into output_buffer)" ];
/// @endmsc
/// @{

/// @file
/// @brief @ref Runtime API Header

#include <nnablart/functions.h>

/// @brief Errors in @ref Runtime.
typedef enum {
  RT_ERROR_VERSION_UNMATCH = -899,   ///< 899
  RT_ERROR_ALLOCATE_CONTEXT,         ///< 898
  RT_ERROR_INITIALIZE_CONTEXT_TWICE, ///< 897
  RT_ERROR_ALLOCATE_CALLBACK_BUFFER, ///< 896
  RT_ERROR_INVALID_BUFFER_INDEX,     ///< 895
  RT_ERROR_INIT_VARIABLE,            ///< 894
  RT_ERROR_UNKNOWN_FUNCTION,         ///< 893
  RT_ERROR_NOERROR = 0               ///< 0
} rt_error_enum_t;

typedef void *rt_context_pointer;

/// @brief Create runtime context.
/// In this function only allocates runtime context.
/// @param[out] context Pointer to created context. It must be freed by @ref
/// rt_free_context()
/// @return @ref rt_error_enum_t
rt_error_enum_t rt_allocate_context(rt_context_pointer *context);

/// @brief Add callback function to runtime context.
/// @param[in] context
/// @return @ref rt_error_enum_t
rt_error_enum_t
rt_add_callback(rt_context_pointer context, nn_function_type_t type,
                rt_function_error_t (*allocate_local_context)(rt_function_t *f),
                rt_function_error_t (*free_local_context)(rt_function_t *f),
                rt_function_error_t (*exec)(rt_function_t *f));

/// @brief Initialize runtime context with parsing @ref nn_network_t.
/// Initialize all functions in context and prepare forward calculation.
/// @param[in/out] context Pointer to created context. It must be freed by @ref
/// rt_free_context()
/// @param[in] network
/// @return @ref rt_error_enum_t
rt_error_enum_t rt_initialize_context(rt_context_pointer context,
                                      nn_network_t *network);

/// @brief Free context.
/// @param[in] context
/// @return @ref rt_error_enum_t
rt_error_enum_t rt_free_context(rt_context_pointer *context);

/// @brief Get number of network inputs.
/// @param[in] context
/// @return Number of inputs
int rt_num_of_input(rt_context_pointer context);

/// @brief Size of input data at index
/// @param[in] context
/// @param[in] index
/// @return Size of data
int rt_input_size(rt_context_pointer context, size_t index);

/// @brief Get dimention of input data at index
/// @param[in] context
/// @param[in] index
/// @return Dimension size
int rt_input_dimension(rt_context_pointer context, size_t index);

/// @brief Shape size at shape_index.
/// @param[in] context
/// @param[in] index
/// @param[in] shape_index
/// @return Size
int rt_input_shape(rt_context_pointer context, size_t index,
                   size_t shape_index);

/// @brief Get input buffer at index
/// NOTE: This function may use for debug perpose.
/// @param[in] context
/// @param[in] index
/// @return pointer
float *rt_input_buffer(rt_context_pointer context, size_t index);

/// @brief Get number of network outputs.
/// @param[in] context
/// @return Number of outputs
int rt_num_of_output(rt_context_pointer context);

/// @brief Size of output data at index
/// @param[in] context
/// @param[in] index
/// @return Size of data
int rt_output_size(rt_context_pointer context, size_t index);

/// @brief Get dimention of output data at index
/// @param[in] context
/// @param[in] index
/// @return Dimension size
int rt_output_dimension(rt_context_pointer context, size_t index);

/// @brief Shape size at shape_index.
/// @param[in] context
/// @param[in] index
/// @param[in] shape_index
/// @return Size
int rt_output_shape(rt_context_pointer context, size_t index,
                    size_t shape_index);

/// @brief Get output buffer at index
/// NOTE: This function may use for debug perpose.
/// @param[in] context
/// @param[in] index
/// @return pointer
float *rt_output_buffer(rt_context_pointer context, size_t index);

/// @brief Execute feed forward calculation.
/// Get data from @ref input and store result to @output.
/// @param[in] context
/// @return @ref rt_error_enum_t
rt_error_enum_t rt_forward(rt_context_pointer context);

/// @}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // H_RUNTIME_H_
