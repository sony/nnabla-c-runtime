# Usage

NNabla C RuntimeはNNablaに内蔵されているFile Format Converterと共
に利用します。

NNablaのネットワーク保存形式であるNNPファイルを入力とし、NNabla C
Runtime専用のファイルフォーマットであるNNB、もしくはNNabla C
Runtimeの一部ライブラリをリンクして利用するためのCソースコードを出
力します。

## Use with C source code conveted from NNP file.

```
$ nnabla_cli convert input.nnp output.nnb
```



## Use with NNB file converted from NNP file.

```
$ nnabla_cli -O CSRC convert input.nnp output
```


## Add your own implementation.

@ref rt_add_callback
を用いることにより、ユーザー独自の関数を追加することが可能です。

ユーザーが用意するべき関数は、
- allocate
- exec
- free

の3種類ですが、コールバックとして指定するのはallocateのみで、execとfreeは
@ref rt_function_context_t にユーザーが自ら登録します。


Callbackの使い方について詳しくは、(examples/callback/callback.c)を参照してください。

