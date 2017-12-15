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
/// @defgroup Runtime ランタイム
/// @brief @ref NetworkDefinitions
/// を用いて順伝播型ニューラルネットワーク計算を実施します。
///
/// 以下のAPIを提供しています。
/// - @ref rt_initialize_context()
///   - @copydoc rt_initialize_context()
/// - @ref rt_free_context()
///   - @copydoc rt_free_context()
/// - @ref rt_num_of_input_data()
///   - @copydoc rt_num_of_input_data()
/// - @ref rt_input_data_size()
///   - @copydoc rt_input_data_size()
/// - @ref rt_input_data_dimension()
///   - @copydoc rt_input_data_dimension()
/// - @ref rt_input_data_shape()
///   - @copydoc rt_input_data_shape()
/// - @ref rt_num_of_output_data()
///   - @copydoc rt_num_of_output_data()
/// - @ref rt_output_data_size()
///   - @copydoc rt_output_data_size()
/// - @ref rt_output_data_dimension()
///   - @copydoc rt_output_data_dimension()
/// - @ref rt_output_data_shape()
///   - @copydoc rt_output_data_shape()
/// - @ref rt_forward()
///   - @copydoc rt_forward()
///
/// - 処理の流れ
///   処理の流れのシーケンスを示します。具体的な実装例は@ref simple_runtime.c
///   や@ref reference_runtime.c にあります。
///   - 初期化
/// @li @ref rt_initialize_context() で実行時コンテキストを初期化
/// @li @ref rt_num_of_input_data(), @ref rt_input_data_size(), @ref
/// rt_num_of_output_data(), @ref rt_output_data_size()
/// により、入出力バッファのサイズを取得してバッファを確保する
/// @msc
///   UserApplication,Runtime;
///   UserApplication=>Runtime [label="rt_initialize_context(&context,
///   network)", URL="@ref rt_initialize_context()"];
///   UserApplication<<Runtime [label="(Context stored into context)" ];
///   UserApplication=>Runtime [label="rt_num_of_input_data(context)", URL="@ref
///   rt_num_of_input_data()"];
///   UserApplication<<Runtime [label="num_of_input_data" ];
///   --- [label="LOOP: index"];
///   UserApplication=>Runtime [label="rt_input_data_size(context, index)",
///   URL="@ref rt_input_data_size()"];
///   UserApplication<<Runtime [label="input_data_size[index]" ];
///   --- [label="LOOP_END: index"];
///   UserApplication=>UserApplication [label="(allocate input buffer)" ];
///   UserApplication=>Runtime [label="rt_num_of_output_data(context)",
///   URL="@ref rt_num_of_output_data()"];
///   UserApplication<<Runtime [label="num_of_output_data" ];
///   --- [label="LOOP: index"];
///   UserApplication=>Runtime [label="rt_output_data_size(context)", URL="@ref
///   rt_output_data_size()"];
///   UserApplication<<Runtime [label="output_data_size" ];
///   --- [label="LOOP_END: index"];
///   UserApplication=>UserApplication [label="(allocate output buffer)" ];
/// @endmsc
///   - 実行
/// @li 初期化時に確保した入力バッファに入力データを格納
/// @li @ref rt_forward() を実行して順伝播ネットワーク計算を実施
/// @li 出力データバッファに格納されている結果を取得
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
/// @brief @ref Runtime のAPIヘッダファイル

/// @brief Errors in @ref Runtime.
typedef enum {
  RT_ERROR_VERSION_UNMATCH = -899, ///< バージョン不整合(-899)
  RT_ERROR_INITVERTEX,             ///< ノード初期化失敗(-898)
  RT_ERROR_UNKNOWN_EDGE,           ///< エッジが未サポート (-897)
  RT_ERROR_NOERROR = 0             ///< 0
} rt_error_enum_t;

typedef void *rt_context_pointer;

/// @brief @ref nn_network_t をパースして必要なバッファ等を確保した@ref
/// ContextDefinitions を作成する
/// @param[out] context
/// 作成したコンテキストを格納するポインタ。利用が終了したら@ref
/// rt_free_context() で開放する必要があります。
/// @param[in] network ネットワーク
/// @return @ref rt_error_enum_t
rt_error_enum_t rt_initialize_context(rt_context_pointer *context,
                                      nn_network_t *network);

/// @brief コンテキストを開放する
/// コンテキスト内にはレイヤ毎のパラメータやweight,
/// biasなどのバッファがmallocされて保持していますので、この関数を用いて開放する必要があります。
/// @param[in] context 開放したいコンテキスト
/// @return @ref rt_error_enum_t
rt_error_enum_t rt_free_context(rt_context_pointer *context);

/// @brief 入力データの数を返す
/// networkは複数の入力を持つことができますので、入力の数を返します。この関数の返り値を@ref
/// rt_input_data_size などのdata_indexとして利用します。
/// @param[in] context コンテキスト
/// @return 入力データ数
int rt_num_of_input_data(rt_context_pointer context);

/// @brief index番目の入力データのノードナンバーを返します。
/// @param[in] context コンテキスト
/// @param[in] index 何番目のデータかを指定する
/// @return ノードナンバー
int rt_input_data_node(rt_context_pointer context, size_t index);

/// @brief index番目の入力データのサイズを返します。
/// ここで返す数値は全ての次元のデータ数を乗算したものと同じです。
/// @param[in] context コンテキスト
/// @param[in] index 何番目のデータかを指定する
/// @return データサイズ
int rt_input_data_size(rt_context_pointer context, size_t index);

/// @brief data_index番目の入力データの次元を返します。
/// @param[in] context コンテキスト
/// @param[in] data_index 何番目のデータかを指定する
/// @return データサイズ
int rt_input_data_dimension(rt_context_pointer context, size_t data_index);

/// @brief data_index番目, shape_index次元のデータサイズを返します。
/// @param[in] context コンテキスト
/// @param[in] data_index 何番目のデータかを指定する
/// @param[in] shape_index 次元を指定
/// @return データサイズ
int rt_input_data_shape(rt_context_pointer context, size_t data_index,
                        size_t shape_index);

/// @brief data_index番目の入力バッファを返します
/// @param[in] context コンテキスト
/// @param[in] data_index 何番目のデータかを指定する
/// @return バッファへのポインタ
float *rt_input_data_buffer(rt_context_pointer context, size_t data_index);

/// @brief 出力データの数を返す
/// networkは複数の出力を持つことができますので、出力の数を返します。この関数の返り値を@ref
/// rt_input_data_size などのdata_indexとして利用します。
/// @param[in] context コンテキスト
/// @return 出力データ数
int rt_num_of_output_data(rt_context_pointer context);

/// @brief index番目の出力データのノードナンバーを返します。
/// @param[in] context コンテキスト
/// @param[in] index 何番目のデータかを指定する
/// @return ノードナンバー
int rt_output_data_node(rt_context_pointer context, size_t index);

/// @brief index番目の出力データのサイズを返します。
/// ここで返す数値は全ての次元のデータ数を乗算したものと同じです。
/// @param[in] context コンテキスト
/// @param[in] index 何番目のデータかを指定する
/// @return データサイズ
int rt_output_data_size(rt_context_pointer context, size_t index);

/// @brief data_index番目の出力データの次元を返します。
/// @param[in] context コンテキスト
/// @param[in] data_index 何番目のデータかを指定する
/// @return データサイズ
int rt_output_data_dimension(rt_context_pointer context, size_t data_index);

/// @brief data_index番目, shape_index次元のデータサイズを返します。
/// @param[in] context コンテキスト
/// @param[in] data_index 何番目のデータかを指定する
/// @param[in] shape_index 次元を指定
/// @return データサイズ
int rt_output_data_shape(rt_context_pointer context, size_t data_index,
                         size_t shape_index);

/// @brief data_index番目の出力バッファを返します
/// @param[in] context コンテキスト
/// @param[in] data_index 何番目のデータかを指定する
/// @return バッファへのポインタ
float *rt_output_data_buffer(rt_context_pointer context, size_t data_index);

/// @brief フィードフォワード計算を実施する
/// コンテキストに与える入力データを指定してフィードフォワード計算を実施し、結果を出力バッファに格納します。
/// この関数では入出力バッファの確保や開放は行わないので、利用者が確保したバッファを渡し、利用後に開放する責務があります。
/// この関数で実行できるレイヤのリストは別文書にて提供する予定です。
/// @param[in] context コンテキスト
/// @param[in] input @ref rt_num_of_input_data
/// 個の入力バッファ。それぞれの入力データはフラットなバッファに行列が格納されたものとなります。
/// @param[in] output  @ref rt_num_of_output_data
/// 個の出力バッファ。それぞれの出力バッファは@ref rt_output_data_size()
/// の値でmallocされているものとします。
/// @return @ref rt_error_enum_t
rt_error_enum_t rt_forward(rt_context_pointer context, float **input,
                           float **output);

/// @}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // H_RUNTIME_H_
