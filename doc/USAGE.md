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
