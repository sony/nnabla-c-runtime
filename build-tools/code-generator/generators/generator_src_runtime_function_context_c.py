# Copyright (c) 2017 Sony Corporation. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


def _generate_context_code(fn, func, fid_num, arg_fmt, fid):
    l = []
    default_arg = func['uniq_name'].split('_').pop()
    default_id = func['id']
    if fid == default_id:
        l.append(
            '    case NN_FUNCTION_{}: {{ // {}'.format(func['snake_name'].upper(), fn))
    else:
        if arg_fmt != default_arg[:len(arg_fmt)]:
            print('Cannot handle not incremental args on {} [{} {}]'.format(
                fn, default_arg, arg_fmt))
            return []
        l.append(
            '    case NN_FUNCTION_{}_{}: {{ // {}'.format(func['snake_name'].upper(), fid_num, fn))

    l.append(
        '      function_context->func.free_local_context_func = free_{}_local_context;'.format(func['snake_name']))

    if 'arguments' in func and len(func['arguments']) > 0:
        l.append(
            '      nn_function_{0}_t *f = (nn_function_{0}_t*)function;'.format(func['snake_name']))
        l.append(
            '      {0}_local_context_t *ctx = rt_malloc_func(sizeof({0}_local_context_t));'.format(func['snake_name']))

        n = 0
        for an, arg in func['arguments'].items():
            if n < len(arg_fmt):
                if arg['type'] == 'bool':
                    l.append('      ctx->{0} = f->{0};'.format(an))
                elif arg['type'] == 'double' or arg['type'] == 'float':
                    l.append('      ctx->{0} = f->{0};'.format(an))
                elif arg['type'] == 'int64':
                    l.append('      ctx->{0} = f->{0};'.format(an))
                elif arg['type'] == 'repeated int64' or arg['type'] == 'Shape':
                    l.append(
                        '      ctx->{0} = create_rt_list_from_nn_list(n, f->{0});'.format(an))
                    n += 1
                elif arg['type'] == 'string':
                    l.append('      ctx->{0} = f->{0};'.format(an))
            else:
                if arg['type'] == 'bool':
                    if arg['default'] == 'True':
                        l.append('      ctx->{} = 1;'.format(an))
                    else:
                        l.append('      ctx->{} = 0;'.format(an))
                elif arg['type'] == 'double' or arg['type'] == 'float':
                    l.append('      ctx->{} = {};'.format(an, arg['default']))
                elif arg['type'] == 'int64':
                    l.append(
                        '      ctx->{} = f->{};'.format(an, arg['default']))
                elif arg['type'] == 'repeated int64' or arg['type'] == 'Shape':
                    # TODO does not support default shape
                    l.append('      ctx->{} = 0;'.format(an))
                    n += 1
                else:
                    # TODO does not support default string.
                    l.append('      ctx->{} = 0;'.format(an))

            n += 1
        l.append('      function_context->func.local_context = ctx;')
    else:
        l.append('      function_context->func.local_context = 0;')
    l.append(
        '      allocate_{}_local_context(&function_context->func);'.format(func['snake_name']))
    l.append('    } break;')
    return l


def generate(filename, info):
    l = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            l.append('#ifdef CONFIG_{}'.format(fn.upper()))
            for n, f in enumerate(func['function_ids'].items()):
                l += _generate_context_code(fn, func, n, f[0], f[1])
            l.append('#endif')
            l.append('')

    from mako.template import Template
    from mako import exceptions
    try:
        tmpl = Template(filename=filename)
        output = tmpl.render(code='\n'.join(l))
        return output
    except:
        print(exceptions.text_error_template().render())
    return None
