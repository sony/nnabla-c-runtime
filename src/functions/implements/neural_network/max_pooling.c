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

#include "pooling.h"

#include <nnablart/config.h>
#include <nnablart/functions.h>

#include <math.h>

#ifdef CONFIG_MAXPOOLING

rt_function_error_t allocate_max_pooling_local_context(rt_function_t *f) {
  max_pooling_local_context_t *context =
      (max_pooling_local_context_t *)(f->local_context);
  pooling_private_t *p = rt_malloc_func(sizeof(pooling_private_t));
  rt_function_error_t ret =
      allocate_pooling(f, (pooling_context_t *)context, p);
  ((max_pooling_local_context_t *)(f->local_context))->data = (void *)p;
  f->exec_func = exec_max_pooling;
  return ret;
}

rt_function_error_t free_max_pooling_local_context(rt_function_t *f) {
  pooling_private_t *p =
      (pooling_private_t *)(((max_pooling_local_context_t *)(f->local_context))
                                ->data);
  return free_pooling(p);
}

rt_function_error_t exec_max_pooling(rt_function_t *f) {
  max_pooling_local_context_t *context =
      (max_pooling_local_context_t *)(f->local_context);
  pooling_private_t *p =
      (pooling_private_t *)(((max_pooling_local_context_t *)(f->local_context))
                                ->data);
  if (p->calc_context.x->type == NN_DATA_TYPE_FLOAT &&
      p->calc_context.y->type == NN_DATA_TYPE_FLOAT) {
#ifdef CONFIG_MAXPOOLING_FLOAT32
    return exec_pooling(f, (pooling_context_t *)context, p, calc_max);
#endif /* CONFIG_MAXPOOLING_FLOAT32 */
  }

  else if (p->calc_context.x->type == NN_DATA_TYPE_INT8 &&
           p->calc_context.y->type == NN_DATA_TYPE_INT8) {
#ifdef CONFIG_MAXPOOLING_FIXED8
    return exec_pooling_fixed8(f, (pooling_context_t *)context, p,
                               calc_max_fixed8);
#endif /* CONFIG_MAXPOOLING_FIXED8 */
  }

  else if (p->calc_context.x->type == NN_DATA_TYPE_INT16 &&
           p->calc_context.y->type == NN_DATA_TYPE_INT16) {
#ifdef CONFIG_MAXPOOLING_FIXED16
    return exec_pooling_fixed16(f, (pooling_context_t *)context, p,
                                calc_max_fixed16);
#endif /* CONFIG_MAXPOOLING_FIXED16 */
  }

  else {
#ifdef CONFIG_MAXPOOLING_GENERIC
    return exec_pooling_generic(f, (pooling_context_t *)context, p,
                                calc_max_generic);
#endif /* CONFIG_MAXPOOLING_GENERIC */
  }
  return RT_FUNCTION_ERROR_NOERROR;
}

#endif /* CONFIG_MAXPOOLING */
