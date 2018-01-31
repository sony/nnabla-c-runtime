// -*- coding:utf-8 -*-
#ifndef H_UTILITIES_H_171218134406_
#define H_UTILITIES_H_171218134406_

#include "utilities/accessor.h"
#include "utilities/list.h"
#include "utilities/shape.h"
#include "utilities/vector.h"

static inline void* context_of(const rt_function_t *f) {
  return f->local_context;
}

static inline rt_list_t shape_of(const rt_variable_t *variable) {
  return variable->shape;
}

static inline void* data_of(const rt_variable_t *variable) {
  return variable->data;
}

static inline rt_variable_t* input_of(const rt_function_t *f, int index) {
  return f->inputs[index];
}

static inline rt_list_t input_shape_of(const rt_function_t *f, int index) {
  return shape_of(input_of(f, index));
}

static inline void* input_data_of(const rt_function_t *f, int index) {
  return data_of(input_of(f, index));
}

static inline rt_variable_t* output_of(const rt_function_t *f, int index) {
  return f->outputs[index];
}

static inline void* output_data_of(const rt_function_t *f, int index) {
  return data_of(output_of(f, index));
}

#endif // H_UTILITIES_H_171218134406_
