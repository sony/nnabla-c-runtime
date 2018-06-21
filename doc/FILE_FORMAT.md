<!--
 Copyright (c) 2017 Sony Corporation. All Rights Reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
-->

# File format

NNabla C Runtime uses platform independent and portable binary file
format that has name `NNB`.

## Overview

In the `NNB` format, the following structure is adopted in order to
eliminate model dependency and realize a portable format.


@dotfile nnb.dot

- All members of the structure shall adopt something with a clear
  size. Since size often changes depending on system, enum specifies
  the size in the bit field.
- All actual data is managed by ID. When accessing data, refer to the
  relative position from the buffer area corresponding to the ID, as
  shown in the figure below, so that the pointer of the actual data
  can be acquired.
- In order to maintain downward compatibility, IDs determined at the
  time of implementation such as `nn_function_t::type` and`
  nn_variable_t::type` are kept unchanged, when new functions are
  added, when dealing with a new format We do not use the existing ID.

@dotfile nnb_memory.dot

## Detailed description

@startuml
skinparam monochrome true

hide methods

class nn_list_t {
  nn_size_t size
  pointer_index_t list
}

class nn_data_type_t {
  NN_DATA_TYPE_FLOAT
  NN_DATA_TYPE_INT16
  NN_DATA_TYPE_INT8
  NN_DATA_TYPE_SIGN
  END_OF_NN_DATA_TYPE
}

class nn_variable_t {
  uint32_t id
  nn_list_t shape
  nn_data_type_t type
  unsigned int fp_pos
  int32_t data_index
}

class  nn_function_type_t {
  NN_FUNCTION_XXXXX
  ...
  NN_END_OF_FUNCTION
}

class nn_function_implement_t {
  NN_FUNCTION_IMPLEMENT_FLOAT
  NN_FUNCTION_IMPLEMENT_FIXED16
  NN_FUNCTION_IMPLEMENT_FIXED8
  NN_END_OF_SYSTEM_DEFINED_FUNCTION_IMPLEMENT
  NN_END_OF_IMPLEMENT
}

class nn_function_t{
  nn_function_type_t type
  nn_function_implement_t impl
  nn_list_t inputs
  nn_list_t outputs
}

class nn_function_xxxxx_t {
  nn_function_type_t type
  nn_function_implement_t impl
  nn_list_t inputs
  nn_list_t outputs
  int32_t arg_for_xxxxx
}

class nn_memory_t {
  nn_size_t num_of_data
  nn_size_t data_size
}

class nn_network_t {
  uint32_t version
  nn_list_t buffers
  nn_list_t variables
  nn_list_t functions
  nn_list_t inputs
  nn_list_t outputs
  nn_memory_t memory
}

nn_network_t *--- nn_list_t
nn_function_t *--- nn_list_t
nn_variable_t *--- nn_list_t

nn_variable_t *- nn_data_type_t

nn_network_t *-- nn_variable_t
nn_network_t *-- nn_variable_t
nn_network_t *-- nn_variable_t
nn_network_t *-- nn_memory_t
nn_network_t *- nn_function_t

nn_function_t <|-- nn_function_xxxxx_t
nn_function_t *---- nn_function_type_t
nn_function_t *---- nn_function_implement_t

@enduml


# NNB Operation

## Creating NNB

## Using NNB

### Read NNB from file.

### Embed NNB into source code
