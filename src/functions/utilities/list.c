// -*- coding:utf-8 -*-
#include <assert.h>

#include "list.h"

rt_list_t allocate_list(int length) {
  rt_list_t ret;
  assert(length >= 0);
  ret.size = length;
  ret.data = (int *)calloc(sizeof(int), length);
  return ret;
}

void free_list(rt_list_t s) {
  if (s.data) {
    free(s.data);
  }
  s.data = 0;
}

rt_list_t clone_list(rt_list_t src) {
  int i;
  rt_list_t dst = allocate_list(src.size);
  for (i = 0; i < src.size; i++) {
    dst.data[i] = src.data[i];
  }
  return dst;
}

