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


def search_function_ancestor(func_name, functions):
    ancestor = None
    matched = []
    for fn in functions:
        fn_s = fn.split('_')
        func_name_s = func_name.split('_')
        if fn_s == func_name_s[:len(fn_s)]:
            matched.append(fn)
    if len(matched) > 0:
        ancestor = sorted(matched).pop()
        return ancestor, func_name_s[len(ancestor.split('_')):]


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
    implement_types = []
    impl_length = 14
    for root, dirs, files in walk(abspath(join(dirname(abspath(__file__)),
                                               '..', '..', '..', 'src'))):
        for fn in files:
            if splitext(fn)[1] == '.c':
                with open(join(root, fn), encoding='utf-8') as f:
                    for l in f.readlines():
                        l = l.rstrip()
                        m = re.search(
                            '^rt_function_error_t exec_([0-9a-z_]+)', l)
                        if m:
                            method_name = m.groups(0)[0]
                            if method_name != 'func':
                                aa = search_function_ancestor(
                                    method_name, functions)
                                if aa:
                                    ancestor, implements = aa
                                    if ancestor not in implemented:
                                        implemented[ancestor] = []
                                    for impl in implements:
                                        if impl not in implement_types:
                                            implement_types.append(impl)
                                            if impl_length < len(impl):
                                                impl_length = len(impl)
                                        implemented[ancestor].append(impl)

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
                    if impl in implemented[func['snake_name']]:
                        line += '{{:^{}}}|'.format(impl_length).format('yes')
                    else:
                        line += '{{:^{}}}|'.format(impl_length).format('-')
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
