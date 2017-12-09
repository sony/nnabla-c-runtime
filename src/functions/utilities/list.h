// -*- coding:utf-8 -*-
#ifndef H_LIST_H_171210064151_
#define H_LIST_H_171210064151_

#include <nnablart/functions.h>

/// Allocate shape
rt_list_t allocate_list(int length);

/// Free allocated shape.
void free_list(rt_list_t s);

/// Calclate size of list
int calc_list_size(rt_list_t list);

/// Clone shape
///
/// list.shape will be allocated inside this function.
/// User must free cloned shape.
rt_list_t clone_list(rt_list_t src);

#endif // H_LIST_H_171210064151_

