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
/// @section Modules
///
/// - @ref Network
/// - @ref Functions
/// - @ref Runtime
///
/// @section Development Development workflow
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

#include <network.h>
#include <runtime.h>
