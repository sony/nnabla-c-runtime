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
/// - @ref Development
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
/// @section WithCSRC Use with C source code conveted from NNP file.
///
/// @section WithNNB Use with NNB file converted from NNP file.
///
///
///
///

/// @page Development Development itself
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

#include <network.h>
#include <runtime.h>
