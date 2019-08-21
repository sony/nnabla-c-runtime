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

import numpy
import sys

data1 = numpy.fromfile(sys.argv[1], numpy.float32)
data2 = numpy.fromfile(sys.argv[2], numpy.float32)
res = numpy.allclose(data1, data2, atol=1e-4)
print(data1)
print(data2)
print(res)

sys.exit(0)
