// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "../../utilities/shape.h"
#include "arithmetic.h"
#include <nnablart/config.h>
#include <nnablart/functions.h>

#ifdef CONFIG_MULSCALAR

rt_function_error_t exec_mul_scalar_generic(rt_function_t *f);
rt_function_error_t exec_mul_scalar_fixed16(rt_function_t *f);
rt_function_error_t exec_mul_scalar_fixed8(rt_function_t *f);

// MulScalar
rt_function_error_t allocate_mul_scalar_local_context(rt_function_t *f) {
  if (f->num_of_inputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_INPUTS;
  }
  if (f->num_of_outputs != 1) {
    return RT_FUNCTION_ERROR_INVALID_NUM_OF_OUTPUTS;
  }
  int input_size = calc_shape_size(f->inputs[0]->shape);
  int output_size = calc_shape_size(f->outputs[0]->shape);
  if (input_size != output_size) {
    return RT_FUNCTION_ERROR_INVALID_SHAPE;
  }
  if (f->inputs[0]->type == NN_DATA_TYPE_FLOAT &&
      f->outputs[0]->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_MULSCALAR_FLOAT32
    f->exec_func = exec_mul_scalar;
#endif /* CONFIG_MULSCALAR_FLOAT32 */
  }

  else if (f->inputs[0]->type == NN_DATA_TYPE_INT16 &&
           f->outputs[0]->type == NN_DATA_TYPE_INT16) {
#ifdef CONFIG_MULSCALAR_FIXED16
    f->exec_func = exec_mul_scalar_fixed16;
#endif /* CONFIG_MULSCALAR_FIXED16 */
  }

  else if (f->inputs[0]->type == NN_DATA_TYPE_INT8 &&
           f->outputs[0]->type == NN_DATA_TYPE_INT8) {
#ifdef CONFIG_MULSCALAR_FIXED8
    f->exec_func = exec_mul_scalar_fixed8;
#endif /* CONFIG_MULSCALAR_FIXED8 */
  }

  else {
#ifdef CONFIG_MULSCALAR_GENERIC
    f->exec_func = exec_mul_scalar_generic;
#endif /* CONFIG_MULSCALAR_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

rt_function_error_t free_mul_scalar_local_context(rt_function_t *f) {
  return RT_FUNCTION_ERROR_NOERROR;
}

#ifdef CONFIG_MULSCALAR_FLOAT32
rt_function_error_t exec_mul_scalar(rt_function_t *f) {
  mul_scalar_local_context_t *context =
      (mul_scalar_local_context_t *)(f->local_context);
  calc_scalar(f, context->val, calc_mul);
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_MULSCALAR_FLOAT32 */

#ifdef CONFIG_MULSCALAR_FIXED8
rt_function_error_t exec_mul_scalar_fixed8(rt_function_t *f) {
  mul_scalar_local_context_t *context =
      (mul_scalar_local_context_t *)(f->local_context);
  calc_scalar_fixed8_largebuff(f, context->val, calc_mul_fixed8);
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_MULSCALAR_FIXED8 */

#ifdef CONFIG_MULSCALAR_FIXED16
rt_function_error_t exec_mul_scalar_fixed16(rt_function_t *f) {
  mul_scalar_local_context_t *context =
      (mul_scalar_local_context_t *)(f->local_context);
  calc_scalar_fixed16_largebuff(f, context->val, calc_mul_fixed16);
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_MULSCALAR_FIXED16 */

#ifdef CONFIG_MULSCALAR_GENERIC
rt_function_error_t exec_mul_scalar_generic(rt_function_t *f) {
  mul_scalar_local_context_t *context =
      (mul_scalar_local_context_t *)(f->local_context);
  calc_scalar_generic(f, context->val, calc_mul);
  return RT_FUNCTION_ERROR_NOERROR;
}
#endif /* CONFIG_MULSCALAR_GENERIC */

#endif /* CONFIG_MULSCALAR */
