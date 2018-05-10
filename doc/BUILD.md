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
