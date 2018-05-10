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

# Build

## Update function info

NNabla C Runtime is part of NNabla but source code of this is independent
from NNabla code.

If you want to follow newest NNabla by hand, you can update @c
functions.yaml with following command.

```bash
$ nnabla_cli function_info build-tools/code-generator/functions.yaml
```

## Compile
Otherwise, you can compile NNabla C Runtime just typing @c make .

```bash
$ make
```
