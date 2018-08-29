# Development

Here is some rules and notes for implementation.

## Coding conventions.

Since the code is automatically formatted at compile time, user does
not have to mention about the indentation depth, parenthesis position
and so on.


Let's not use abbreviations as much as possible. However, except when
"i", "j", "k" are used as an iterator variable for for loop, it is an
exception.


### Naming Rule.

- Functions and variables.
  - Snake case with all lowercase 
- MACRO
  - Snake case with all uppercase 
- Type
  - User defined type has `_t` suffix.
  - Types belongs to network definition add `nn_` prefix.
    Otherwise add `rt_` prefix.


## Function implementation.

`exec_XXX` with no suffix means `float` exec function.
It only allows input/output variable with FLOAT32, and do all internal calculation with float.

`exec_XXX_generic` is general implementation.
It allows any type of input/output and do all internal calculation with float.
But it is very slow.

for example, in `affine.c` select execution function with following code.
```
  if (p->input->type == NN_DATA_TYPE_FLOAT &&
      p->output->type == NN_DATA_TYPE_FLOAT &&
      p->weight->type == NN_DATA_TYPE_FLOAT &&
      ((p->bias && p->bias->type == NN_DATA_TYPE_FLOAT) || !p->bias)) {
    f->exec_func = exec_affine;
  } else {
    f->exec_func = exec_affine_generic;
  }
```
