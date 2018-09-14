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

# Usage

NNabla C Runtime depends `File Format Converter` that is included in `NNabla`.

## Use with C source code converted from NNP file.

```
$ nnabla_cli convert input.nnp output.nnb
```

## Use with NNB file converted from NNP file.

```
$ nnabla_cli -O CSRC convert input.nnp output
```


## Add your own implementation.

To use user defined functions, use @ref rt_add_callback.

The function that the user should prepare is

- allocate
- exec
- free

that 3 types.

Please see (examples/callback/callback.c) for details.

## Meaning of `nn_function_implement_t`

- `0 to 99`
  - Callback allocator will called when initialize context if it was registered, 
    impl number is used by user.
- `NN_FUNCTION_IMPLEMENT_AUTO(100)`
  - Implementation is automatically selected.
- `NN_FUNCTION_IMPLEMENT_FLOAT(101)`
  - NOT IMPLEMENTED: force use float function.
- `NN_FUNCTION_IMPLEMENT_FIXED16(102)`
  - NOT IMPLEMENTED: force use fixed16 function.
- `NN_FUNCTION_IMPLEMENT_FIXED8(103)`
  - NOT IMPLEMENTED: force use fixed8 function.
