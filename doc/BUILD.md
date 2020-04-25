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
$ nnabla_cli function_info -o build-tools/code-generator/functions.yaml
```

## Compile
Otherwise, you can compile NNabla C Runtime just typing @c make .

```bash
$ make
```

## Cross compiling
The developer can add cmake in the directory `build-tools/cmake/` for cross compiling.

```bash
$ make CMAKE_TOOLCHAIN_FILE=./build-tools/cmake/$(cross-compiling-cmake) TOOLCHAIN_PREFIX=$(cross-compiling-tool-chain)
```

> _Note_: Running `make` without `docker` may require the installation of `clang-format` and `autopep8`
> 

__Example__

```bash
$ make CMAKE_TOOLCHAIN_FILE=./build-tools/cmake/spresense.cmake TOOLCHAIN_PREFIX=~/spresenseenv/usr/
```

## Make targets

### Targets for NNabla C Runtime

#### Build
- all
- nnabla-c-runtime-build
- nnabla-c-runtime-docker_image_build

- nnabla-c-runtime-generate
- bwd-nnabla-c-runtime-build

- nnabla-c-runtime-compile

#### Clean
- nnabla-c-runtime-clean
- clean
- clean-all


#### Auto format
- nnabla-c-runtime-auto-format
- nnabla-c-runtime-docker_image_auto_format
- bwd-nnabla-c-runtime-auto-format

#### Documents
- nnabla-c-runtime-doc
- bwd-nnabla-c-runtime-doc

- nnabla-c-runtime-docker_image_doc
- nnabla-c-runtime-docker_image_test

#### Examples
- nnabla-c-runtime-examples
- bwd-nnabla-c-runtime-examples



#### Update function info (Needs `nnabla` directory)
- nnabla-c-runtime-update-function-info
- bwd-nnabla-c-runtime-update-function-info

#### Tests (Needs `nnabla` directory)
- nnabla-c-runtime-generate-function-test
- bwd-nnabla-c-runtime-generate-function-test

- nnabla-c-runtime-test-all-functions
- bwd-nnabla-c-runtime-test-all-functions

#### Development in docker container (Needs `nnabla` directory)
- bwd-nnabla-c-runtime-shell

### Targets for NNabla

- nnabla-auto-format
- nnabla-clean
- nnabla-clean-all
- nnabla-cpplib
- nnabla-doc
- nnabla-install
- nnabla-install-cpplib
- nnabla-test
- nnabla-test-cpplib
- nnabla-test-local
- nnabla-wheel

- docker_image_auto_format
- docker_image_build
- docker_image_doc

- bwd-nnabla-auto-format
- bwd-nnabla-cpplib
- bwd-nnabla-doc
- bwd-nnabla-test
- bwd-nnabla-test-cpplib
- bwd-nnabla-wheel
