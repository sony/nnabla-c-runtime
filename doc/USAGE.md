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

## Use with C source code conveted from NNP file.

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
