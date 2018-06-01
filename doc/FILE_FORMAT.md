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

@dotfile nnb.dot

@startuml
skinparam monochrome true

hide empty members

class nn_list_t {
    nn_size_t size
    pointer_index_t list
}

class nn_variable_buffer_t {
    int id
    int size
}

class nn_variable_t {
    uint32_t id
    nn_list_t shape
    nn_data_type_t type
    unsigned int fp_pos
    int32_t data_index
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

nn_network_t *- nn_variable_buffer_t : nn_list_t buffers 
nn_network_t *- nn_variable_t : nn_list_t variables 
nn_network_t *- nn_function_t : nn_list_t functions 
nn_network_t *- nn_variable_t : nn_list_t inputs
nn_network_t *- nn_variable_t : nn_list_t outputs


@enduml
TBD
