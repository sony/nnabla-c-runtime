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


def generate(filename, info):
    l = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            l.append(
                '    case NN_FUNCTION_{}: {{ // {}'.format(func['snake_name'].upper(), fn))
            l.append('      function_context->exec_func = exec_{};'.format(
                func['snake_name']))
            l.append('      function_context->free_local_context_func = free_{}_local_context;'.format(
                func['snake_name']))
            if 'arguments' in func and len(func['arguments']) > 0:
                l.append(
                    '      nn_function_{0}_t *f = (nn_function_{0}_t*)function;'.format(func['snake_name']))
                l.append(
                    '      {0}_local_context_t *ctx = malloc(sizeof({0}_local_context_t));'.format(func['snake_name']))

                for an, arg in func['arguments'].items():
                    if arg['type'] == 'bool':
                        l.append('      ctx->{0} = f->{0};'.format(an))
                    elif arg['type'] == 'double' or arg['type'] == 'float':
                        l.append('      ctx->{0} = f->{0};'.format(an))
                    elif arg['type'] == 'int64':
                        l.append('      ctx->{0} = f->{0};'.format(an))
                    elif arg['type'] == 'repeated int64' or arg['type'] == 'Shape':
                        l.append(
                            '      ctx->{0} = create_rt_list_from_nn_list(n, f->{0});'.format(an))
                    elif arg['type'] == 'string':
                        l.append('      ctx->{0} = f->{0};'.format(an))
                l.append('      function_context->func.local_context = ctx;')
            else:
                l.append('      function_context->func.local_context = 0;')
            l.append('      allocate_{}_local_context(&function_context->func);'.format(
                func['snake_name']))
            l.append('    } break;')
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
