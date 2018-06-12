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
import numpy
import sys

result = True
a_files = sorted(glob.glob('{}[0-9]*.bin'.format(sys.argv[1])))
b_files = sorted(glob.glob('{}[0-9]*.bin'.format(sys.argv[2])))


def merge_files(files):
    if len(files) > 1:
        with open(files[0], "ab") as base:
            for x in files[1:]:
                with open(x, "rb") as append:
                    base.write(append.read())
    return files[0]


def compare_file(a_file, b_file):
    data1 = numpy.fromfile(a_file, numpy.float32)
    data2 = numpy.fromfile(b_file, numpy.float32)
    res = numpy.allclose(data1, data2, atol=1e-4)
    print(a_file, b_file, res)
    if not res:
        print("WARNING: differ with 1e-4, check it again with 1e-2...")
        res = numpy.allclose(data1, data2, atol=1e-2)
        if not res:
            return False
    return True


if len(a_files) == 0 or len(b_files) == 0:
    sys.exit(255)
elif len(a_files) == len(b_files):
    # outputs has same format
    for out1, out2 in zip(a_files, b_files):
        if not compare_file(out1, out2):
            sys.exit(255)
else:
    # merge result and then compare them
    a_file = merge_files(a_files)
    b_file = merge_files(b_files)
    if not compare_file(a_file, b_file):
        sys.exit(255)

sys.exit(0)
