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
for out1, out2 in zip(sorted(glob.glob('{}[0-9]*.bin'.format(sys.argv[1]))),
                      sorted(glob.glob('{}[0-9]*.bin'.format(sys.argv[2])))):
    data1 = numpy.fromfile(out1, numpy.float32)
    data2 = numpy.fromfile(out2, numpy.float32)
    res = numpy.allclose(data1, data2, atol=1e-4)
    print(out1, out2, res)
    if not res:
        result = False
if not result:
    sys.exit(255)
