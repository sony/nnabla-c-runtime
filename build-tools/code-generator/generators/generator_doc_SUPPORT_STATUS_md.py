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

import re
from os.path import basename, abspath, dirname, join, splitext
from os import walk


def generate(filename, info):

    functions = []
    function_length = 0
    for cn, cat in info.items():
        for fn, func in cat.items():
            functions.append(func['snake_name'])
            if function_length < len(fn):
                function_length = len(fn)
    function_length += 2

    unimplemented = []
    with open(abspath(join(
        dirname(abspath(__file__)),
        '..', '..', '..',
            'src', 'functions', 'implements', 'unimplemented.c'))) as f:
        for l in f.readlines():
            l = l.rstrip()
            m = re.search('exec_([0-9a-z_]+)', l)
            if m:
                unimplemented.append(m.groups(0)[0])

    implemented = {}
    implement_types = ['float', 'generic']
    impl_length = 14
    for root, dirs, files in walk(abspath(join(dirname(abspath(__file__)),
                                               '..', '..', '..', 'src'))):
        for fn in files:
            if splitext(fn)[1] == '.c':
                with open(join(root, fn), encoding='utf-8') as f:
                    code = f.read()
                    m = re.findall('allocate_([0-9a-z_]+)_local_context', code)
                    if m:
                        func_name = m[0]
                        if func_name not in implemented:
                            implemented[func_name] = []
                        func_f = re.findall('exec_{}'.format(func_name), code)
                        if func_f:
                            implemented[func_name].append('float')
                        func_g = re.findall('([0-9a-z_]+)_generic', code)
                        if func_g:
                            implemented[func_name].append('generic')

    count = 0
    count_impl = 0
    counts = {}
    counts_impl = {}
    for cn, cat in info.items():
        counts[cn] = 0
        counts_impl[cn] = 0
        for fn, func in cat.items():
            count += 1
            counts[cn] += 1
            if func['snake_name'] not in unimplemented:
                count_impl += 1
                counts_impl[cn] += 1

    table = ''
    table += '# Implement status\n'
    table += '\n'
    table += 'Total {}/{}\n'.format(count_impl, count)
    table += '\n'
    implement_types = sorted(implement_types)
    header = '|{{:^{}}}|{{:^{}}}|'.format(
        function_length, impl_length).format('Function', 'Available')
    for impl in implement_types:
        header += '{{:^{}}}|'.format(impl_length).format(impl)
    header += '\n'
    header += '|{{:^{}}}|{{:^{}}}|'.format(
        function_length, impl_length).format('-' * function_length, '-' * impl_length)
    for impl in implement_types:
        header += '{{:^{}}}|'.format(impl_length).format('-'*impl_length)
    header += '\n'

    for cn, cat in info.items():
        table += '\n'
        table += '## {}\n'.format(cn)
        table += 'Count {}/{}\n'.format(counts_impl[cn], counts[cn])
        table += '\n'
        table += header
        for fn, func in cat.items():
            name = fn
            if func['snake_name'] in unimplemented:
                line = '|{{:^{}}}|{{:^{}}}|'.format(
                    function_length, impl_length).format(fn, 'no')
                for impl in implement_types:
                    line += '{{:^{}}}|'.format(impl_length).format('-')
            else:
                line = '|{{:^{}}}|{{:^{}}}|'.format(
                    function_length, impl_length).format(fn, 'yes')
                for impl in implement_types:
                    if func['snake_name'] in implemented:
                        if impl in implemented[func['snake_name']]:
                            line += '{{:^{}}}|'.format(
                                impl_length).format('yes')
                        else:
                            line += '{{:^{}}}|'.format(impl_length).format('-')
                    else:
                        line += '{{:^{}}}|'.format(impl_length).format('?')
            table += line + '\n'

    from mako.template import Template
    from mako import exceptions
    try:
        tmpl = Template(filename=filename)
        output = tmpl.render(table=table)
        return output
    except:
        print(exceptions.text_error_template().render())
    return None
