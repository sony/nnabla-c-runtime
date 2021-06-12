# Copyright 2018,2019,2020,2021 Sony Corporation.
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

import glob
import os

samples = {}
for f in glob.glob('{}/reference/nnp/*.nnp'.format(os.environ['NNABLA_SAMPLE_DATA_DIRECTORY'])):
    name, ext = os.path.splitext(os.path.basename(f))
    samples[name] = f

with open('{}/test_mnist_samples.mk'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY']), 'w') as f:
    f.write('all: \\\n')
    if 'CRUNTIME_TEST_SAMPLE_LIST' in os.environ:
        sample_list = ' '.join(
            os.environ['CRUNTIME_TEST_SAMPLE_LIST'].split(',')).split()
        print(sample_list)
    else:
        sample_list = []

    target_list = []
    for sample in sorted(samples):
        if len(sample_list) > 0:
            if sample in sample_list:
                target_list.append(' test_{}'.format(sample))
        else:
            target_list.append(' test_{}'.format(sample))
    f.write('\t')
    f.write(' \\\n\t'.join(target_list))
    f.write('\n')
    f.write('\t@echo All test finished.\n')
    f.write('\t@echo Result CSV start\n')
    f.write('\t@python build-tools/file-format-converter/check_sample_result.py |tee {}/mnists/result_samples.csv\n'.format(
        os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY']))
    f.write('\t@echo Result CSV end\n')

    f.write('\n')

    for sample in sorted(samples):
        nnp = samples[sample]
        name = os.path.splitext(os.path.basename(nnp))[0]
        log = '{}/mnists/{}.log'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], name)
        csrc_dir = '{}/mnists/{}/csrc'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], name)
        f.write('test_{}:\n'.format(sample))
        f.write('\t@echo Testing {}\n'.format(name))
        f.write('\t@mkdir -p {}\n'.format(csrc_dir))
        f.write('\t@nnabla_cli convert --nnp-expand-network -O CSRC -b 1 {} {} >>{} 2>&1\n'.format(nnp, csrc_dir, log))
        f.write('\t@make -C {}\\\n'.format(csrc_dir))
        f.write('\t\tCFLAGS="-I../../../../../include"\\\n')
        f.write(
            '\t\tLDFLAGS="-L../../../../../build/src/functions" >>{} 2>&1\n'.format(log))
        nnb_dir = '{}/mnists/{}/nnb'.format(
            os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], name)
        nnb = '{}/{}.nnb'.format(nnb_dir, name)
        f.write('\t@mkdir -p {}\n'.format(nnb_dir))
        f.write(
            '\t@nnabla_cli convert --nnp-expand-network -b 1 {} {} >>{} 2>&1\n'.format(nnp, nnb, log))
        for input_bin in glob.glob('{}/sample_data/bin/[49]*.bin'.format(os.environ['NNABLA_SAMPLE_DATA_DIRECTORY'])):
            f.write('\t@valgrind --leak-check=full\\\n')
            output_bin = os.path.splitext(os.path.basename(input_bin))[0]
            f.write('\t\t{}/*_example\\\n'.format(csrc_dir))
            f.write('\t\t\t{}\\\n'.format(input_bin))
            f.write('\t\t\t{}/{} >>{} 2>&1\n'.format(csrc_dir, output_bin, log))

            f.write('\t@valgrind --leak-check=full\\\n')
            output_bin = os.path.splitext(os.path.basename(input_bin))[0]
            f.write(
                '\t\t./build/src/nnablart/nnablart infer\\\n'.format(csrc_dir))
            f.write('\t\t\t{}\\\n'.format(nnb))
            f.write('\t\t\t{}\\\n'.format(input_bin))
            f.write('\t\t\t{}/{} >>{} 2>&1\n'.format(nnb_dir, output_bin, log))

        f.write('\n')
