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
import google.protobuf.text_format as text_format

result_nums = {}


def callback(name, nnp, inputs, outputs):
    if name not in result_nums:
        result_nums[name] = 0

    save_filename = '{}_{:03d}.nntxt'.format(name, result_nums[name])

    for n, i in enumerate(inputs):
        i.tofile('{}_{:03d}_input_{}.bin'.format(
            name, result_nums[name], n))
    for n, o in enumerate(outputs):
        o.tofile('{}_{:03d}_output_{}.bin'.format(
            name, result_nums[name], n))
    with open(save_filename, 'w') as f:
        text_format.PrintMessage(nnp, f)
    result_nums[name] += 1
