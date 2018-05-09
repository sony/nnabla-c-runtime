# Build

@section Update Update function info

NNabla C Runtime is part of NNabla but source code of this is independent
from NNabla code.

If you want to follow newest NNabla by hand, you can update @c
functions.yaml with following command.

@code{.sh}
$ nnabla_cli function_info build-tools/code-generator/functions.yaml
@endcode

@section Compile Compile
Otherwise, you can compile NNabla C Runtime just typing @c make .

@code{.sh}
$ make
@endcode

@startuml
skinparam monochrome true
hide footbox

actor Developer

group Update function info
  note right
    To update Function info run 'nnabla_cli function_info' after
    installing nnabla.
  end note
  Developer -> NNabla: Create function information
  activate Developer
  note left: $ nnabla_cli function_info
  activate NNabla
  NNabla --> Developer: functions.yaml
  deactivate NNabla

  Developer -> Developer: Copy into nnabla-c-runtime
  activate Developer
  deactivate Developer
  deactivate Developer
end

Developer -> Developer: compile
activate Developer
note left: $ make

Developer -> NNablaCRuntime: compile
activate NNablaCRuntime

NNablaCRuntime -> NNablaCRuntime: generate source code
activate NNablaCRuntime
deactivate NNablaCRuntime

NNablaCRuntime -> NNablaCRuntime: auto-format
activate NNablaCRuntime
deactivate NNablaCRuntime

NNablaCRuntime --> Developer : <binary>
deactivate NNablaCRuntime

@enduml


