# Copyright 2017,2018,2019,2020,2021 Sony Corporation.
# Copyright 2021 Sony Group Corporation.
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
    defines = []
    for cn, cat in info.items():
        defines.append(
            '////////////////////////////////////////////////////////////////////////////////')
        defines.append(
            '/// @defgroup {} {}'.format(cn.split(',').pop().replace(' ', ''), cn.split(',').pop()))
        defines.append('/// @{')
        for fn, func in cat.items():
            defines.append('')
            defines.append('/// @defgroup {0} {0}'.format(fn))
            defines.append('/// @{')
            defines.append('')
            name = func['snake_name']
            if 'arguments' in func and len(func['arguments']) > 0:

                for an, arg in func['arguments'].items():
                    if 'available_values' in arg:
                        defines.append(
                            '/// Named values for {}.{}'.format(fn, an))
                        defines.append('typedef enum {')
                        for t in arg['available_values']:
                            defines.append('    {}_{}_{},'.format(
                                name.upper(), an.upper(), t.upper()))
                        defines.append('    END_OF_{}_{}'.format(
                            name.upper(), an.upper()))
                        defines.append('}} {}_{}_value_t;'.format(name, an))
                        defines.append('')
                defines.append('/// Local context for {}'.format(fn))
                defines.append('typedef struct {')

                for an, arg in func['arguments'].items():

                    if arg['type'] == 'bool':
                        defines.append(
                            '  uint8_t {}; ///< {}'.format(an, arg['type']))

                    elif arg['type'] == 'double' or arg['type'] == 'float':
                        defines.append(
                            '  float {}; ///< {}'.format(an, arg['type']))

                    elif arg['type'] == 'int64':
                        defines.append(
                            '  int32_t {}; ///< {}'.format(an, arg['type']))

                    elif arg['type'] == 'repeated int64' or arg['type'] == 'Shape':
                        defines.append(
                            '  rt_list_t {}; ///< Original type is [{}]'.format(an, arg['type']))

                    elif arg['type'] == 'string':
                        defines.append(
                            '{0}_{1}_value_t {1}; ///< {2}'.format(name, an, arg['type']))

                defines.append('  void* data; ///< General purpose data area')
                defines.append('}} {}_local_context_t;'.format(name))
            defines.append('')
            defines.append('/// Allocate {} local context'.format(fn))
            defines.append(
                'rt_function_error_t allocate_{}_local_context(rt_function_t* f);'.format(name))
            defines.append('')
            defines.append('/// Free {} local context '.format(fn))
            defines.append(
                'rt_function_error_t free_{}_local_context(rt_function_t* f);'.format(name))
            defines.append('')
            defines.append('/// Exec {}'.format(fn))
            defines.append(
                'rt_function_error_t exec_{}(rt_function_t* f);'.format(name))
            defines.append('/// @}')
            defines.append('')
        defines.append('/// @}')
        defines.append('')

    from mako.template import Template
    from mako import exceptions
    try:
        tmpl = Template(filename=filename)
        output = tmpl.render(FUNCTION_DEFINES='\n'.join(defines))
        return output
    except:
        print(exceptions.text_error_template().render())
    return None
