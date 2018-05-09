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

/// @mainpage
///
/// @section Documents Documents
///
/// - @ref Usage
/// - @ref Build
/// - @ref FileFormat
///
/// @section Modules
///
/// - @ref Network
/// - @ref Functions
/// - @ref Runtime
///

/// @page Usage Usage
///
/// NNabla C RuntimeはNNablaに内蔵されているFile Format Converterと共
/// に利用します。
///
/// NNablaのネットワーク保存形式であるNNPファイルを入力とし、NNabla C
/// Runtime専用のファイルフォーマットであるNNB、もしくはNNabla C
/// Runtimeの一部ライブラリをリンクして利用するためのCソースコードを出
/// 力します。
///
/// @section WithCSRC Use with C source code conveted from NNP file.
///
/// @code{.sh}
/// $ nnabla_cli convert input.nnp output.nnb
/// @endcode
///
///
///
/// @section WithNNB Use with NNB file converted from NNP file.
///
/// @code{.sh}
/// $ nnabla_cli -O CSRC convert input.nnp output
/// @endcode
///
///
///
/// @section WithCallback Add your own implementation.
///
/// @ref rt_add_callback
/// を用いることにより、ユーザー独自の関数を追加することが可能です。
///
/// ユーザーが用意するべき関数は、
/// - allocate
/// - exec
/// - free
///
/// の3種類ですが、コールバックとして指定するのはallocateのみで、execとfreeは
/// @ref rt_function_context_t にユーザーが自ら登録します。
///
///
///

/// @page Build Build NNabla C Runtime
///
/// @section Update Update function info
///
/// NNabla C Runtime is part of NNabla but source code of this is independent
/// from NNabla code.
///
/// If you want to follow newest NNabla by hand, you can update @c
/// functions.yaml with following command.
///
/// @code{.sh}
/// $ nnabla_cli function_info build-tools/code-generator/functions.yaml
/// @endcode
///
/// @section Compile Compile
/// Otherwise, you can compile NNabla C Runtime just typing @c make .
///
/// @code{.sh}
/// $ make
/// @endcode
///
/// @startuml
/// skinparam monochrome true
/// hide footbox
///
/// actor Developer
///
/// group Update function info
///   note right
///     To update Function info run 'nnabla_cli function_info' after
///     installing nnabla.
///   end note
///   Developer -> NNabla: Create function information
///   activate Developer
///   note left: $ nnabla_cli function_info
///   activate NNabla
///   NNabla --> Developer: functions.yaml
///   deactivate NNabla
///
///   Developer -> Developer: Copy into nnabla-c-runtime
///   activate Developer
///   deactivate Developer
///   deactivate Developer
/// end
///
/// Developer -> Developer: compile
/// activate Developer
/// note left: $ make
///
/// Developer -> NNablaCRuntime: compile
/// activate NNablaCRuntime
///
/// NNablaCRuntime -> NNablaCRuntime: generate source code
/// activate NNablaCRuntime
/// deactivate NNablaCRuntime
///
/// NNablaCRuntime -> NNablaCRuntime: auto-format
/// activate NNablaCRuntime
/// deactivate NNablaCRuntime
///
/// NNablaCRuntime --> Developer : <binary>
/// deactivate NNablaCRuntime
///
/// @enduml

/// @page FileFormat NNB file format
///
/// @ref network.h
///
///

#include <nnablart/network.h>
#include <nnablart/runtime.h>
