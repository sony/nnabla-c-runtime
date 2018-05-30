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
import re
import sys


def check_error(lines):
    diff_errors = 0
    memory_errors = 0
    for n, l in enumerate(lines):
        l = l.rstrip()
        match = re.search('ERROR SUMMARY: ([0-9]+) errors', l)
        if match:
            memory_errors += int(match.group(1))
        if l == 'False':
            diff_errors += 1
    return memory_errors, diff_errors


print('Testname, Memleak(CSRC), Diff(CSRC), Memleak(NNB), Diff(NNB)')
for csrclog in sorted(glob.glob('{}/nnablart/csrc/*.log'.format(os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY']))):
    nnblog = '{}/nnb/{}'.format(
        os.environ['NNABLA_C_RUNTIME_TEST_DIRECTORY'], os.path.basename(csrclog))
    with open(csrclog, 'r') as f:
        csrc_memory_errors, csrc_diff_errors = check_error(f.readlines())
    with open(nnblog, 'r') as f:
        nnb_memory_errors, nnb_diff_errors = check_error(f.readlines())
    filename = os.path.basename(csrclog)
    name, ext = os.path.splitext(filename)
    print('{}, {}, {}, {}, {}'.format(name, csrc_memory_errors,
                                      csrc_diff_errors, nnb_memory_errors, nnb_diff_errors))
    if csrc_memory_errors != 0 or csrc_diff_errors != 0:
        sys.stderr.write(
            '\tCSRC has some error plese see {}\n'.format(csrclog))
    if nnb_memory_errors != 0 or nnb_diff_errors != 0:
        sys.stderr.write('\tNNB has some error plese see {}\n'.format(csrclog))
