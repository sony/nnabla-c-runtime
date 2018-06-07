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

import glob
import os

functions = {}
for f in glob.glob('{}/functions/*.nntxt'.format(os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'])):
    name, ext = os.path.splitext(os.path.basename(f))
    functions[name] = f

with open('{}/nnabla-c-runtime/test_functions.mk'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY']), 'w') as f:
    f.write('all: \\\n')

    func_list = []
    if 'CRUNTIME_TEST_FUNCTION_LIST' in os.environ:
        func_list = ' '.join(
            os.environ['CRUNTIME_TEST_FUNCTION_LIST'].split(',')).split()
    func_exclude_list = []
    if 'CRUNTIME_TEST_FUNCTION_EXCLUDE_LIST' in os.environ:
        func_exclude_list = ' '.join(
            os.environ['CRUNTIME_TEST_FUNCTION_EXCLUDE_LIST'].split(',')).split()
    print('FUNCTION_LIST: {}, FUNCTION_EXCLUDE_LIST: {}'.format(
        func_list, func_exclude_list))

    target_list = []
    for function in sorted(functions):
        name = function.rsplit('_', 1)[0]
        if len(func_list) > 0:
            if name in func_list:
                if name not in func_exclude_list:
                    target_list.append(' test_{}'.format(function))
        else:
            if name not in func_exclude_list:
                target_list.append(' test_{}'.format(function))
    f.write('\t')
    f.write(' \\\n\t'.join(target_list))
    f.write('\n')
    f.write('\t@echo All test finished.\n')
    f.write('\t@echo Result CSV start\n')
    f.write('\t@python build-tools/test/scripts/check_function_result.py |tee {}/nnabla-c-runtime/result.csv\n'.format(
        os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY']))
    f.write('\t@echo Result CSV end\n')

    f.write('\n')

    for function in sorted(functions):
        nntxt = functions[function]
        csrclog = '{}/nnabla-c-runtime/csrc/{}.log'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function)
        nnblog = '{}/nnabla-c-runtime/nnb/{}.log'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function)
        f.write('test_{}:\n'.format(function))
        f.write('\t@echo Testing {}\n'.format(function))
        f.write('\t@mkdir -p {}/nnabla-c-runtime/csrc/{}\n'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function))
        f.write('\t@nnabla_cli convert -O CSRC {} {}/nnabla-c-runtime/csrc/{} >>{} 2>&1\n'.format(
            nntxt, os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function, csrclog))
        f.write(
            '\t@$(MAKE) -C {}/nnabla-c-runtime/csrc/{}\\\n'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function))
        f.write('\t\tCFLAGS="-I ../../../../../include"\\\n')
        f.write(
            '\t\tLDFLAGS="-L../../../../../build/src/functions" >>{} 2>&1\n'.format(csrclog))
        f.write('\t@valgrind  --leak-check=full {}/nnabla-c-runtime/csrc/{}/network1_example\\\n'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function))
        f.write(
            '\t\t{}/functions/{}_input_*.bin\\\n'.format(os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'], function))
        f.write(
            '\t\t{}/nnabla-c-runtime/csrc/{}/network1_example_output >>{} 2>&1\n'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function, csrclog))
        f.write('\t@mkdir -p {}/nnabla-c-runtime/nnb\n'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY']))
        f.write('\t@nnabla_cli convert {} {}/nnabla-c-runtime/nnb/{}.nnb >>{} 2>&1\n'.format(
            nntxt, os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function, nnblog))
        f.write(
            '\t@valgrind  --leak-check=full ./build/src/nnablart/nnablart dump\\\n')
        f.write(
            '\t\t{}/nnabla-c-runtime/nnb/{}.nnb >>{} 2>&1\n'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function, nnblog))
        f.write(
            '\t@valgrind  --leak-check=full ./build/src/nnablart/nnablart infer\\\n')
        f.write('\t\t{}/nnabla-c-runtime/nnb/{}.nnb\\\n'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function))
        f.write(
            '\t\t{}/functions/{}_input_*.bin\\\n'.format(os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'], function))
        f.write(
            '\t\t{}/nnabla-c-runtime/nnb/{}_output >>{} 2>&1\n'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function, nnblog))
        for output in sorted(glob.glob('{}/functions/{}_output_?.bin'.format(os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'], function))):
            name, ext = os.path.splitext(output)
            num = name.rsplit('_', 1)[1]
            f.write(
                '\t@python build-tools/test/scripts/diff_result.py\\\n'.format(output))
            f.write('\t\t{}\\\n'.format(output))
            f.write(
                '\t\t{}/nnabla-c-runtime/csrc/{}/network1_example_output_{}.bin >>{} 2>&1\n'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function, num, csrclog))
            f.write(
                '\t@python build-tools/test/scripts/diff_result.py\\\n'.format(output))
            f.write('\t\t{}\\\n'.format(output))
            f.write(
                '\t\t{}/nnabla-c-runtime/nnb/{}_output_{}.bin >>{} 2>&1\n'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], function, num, nnblog))
        f.write('')
        f.write('')
        f.write('\n')
