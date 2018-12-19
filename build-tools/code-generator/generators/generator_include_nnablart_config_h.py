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


def get_func_list(info):
    func_list = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            for t in func['func_type']:
                if t == 'None':
                    break
                elif t == 'ALL':
                    func_list.append(fn)
                    func_list.append(fn+'_FLOAT32')
                    func_list.append(fn+'_GENERIC')
                elif t == 'FLOAT32':
                    func_list.append(fn)
                    func_list.append(fn+'_FLOAT32')
                elif t == 'FIXED8' or t == 'FIXED16':
                    func_list.append(fn)
                    func_list.append(fn+'_GENERIC')
    return list(set(func_list))


def generate(filename, info):
    defines = []
    func_list = get_func_list(info)
    func_list = [x.upper() for x in func_list]
    func_list.sort()
    for n in func_list:
        defines.append('#define CONFIG_{} 1'.format(n))

    from mako.template import Template
    from mako import exceptions
    try:
        tmpl = Template(filename=filename)
        output = tmpl.render(CONFIG_DEFINES='\n'.join(defines))
        return output
    except:
        print(exceptions.text_error_template().render())
    return None
