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
import nnabla.utils.nnabla_pb2 as nnabla_pb2
import glob
import os

for f in sorted(glob.glob('{}/succeed/*.nntxt'.format(os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY']))):
    name, ext = os.path.splitext(os.path.basename(f))
    os.system('nnabla_cli nnb_template {} {}/succeed/{}_float32.yaml'.format(
        f, os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'], name))
    parameter_name = []
    proto = nnabla_pb2.NNablaProtoBuf()
    with open(f, 'r') as o:
        text_format.Merge(o.read(), proto)
        for executor in proto.executor:
            for parameter_variable in executor.parameter_variable:
                if parameter_variable is not None:
                    parameter_name.append(parameter_variable.variable_name)
    if parameter_name:
        fixed16_data = ''
        fixed8_data = ''
        with open('{}/succeed/{}_float32.yaml'.format(
                os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'], name), 'r') as f:
            for line in f:
                count = 0
                for name_ in parameter_name:
                    if name_ in line:
                        fixed16_data += line.replace('FLOAT32', 'FIXED16')
                        fixed8_data += line.replace('FLOAT32', 'FIXED8')
                        count += 1
                        break
                if count == 0:
                    fixed16_data += line
                    fixed8_data += line
        with open('{}/succeed/{}_fixed16.yaml'.format(
                os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'], name), 'w') as f:
            f.write(fixed16_data)
        with open('{}/succeed/{}_fixed8.yaml'.format(
                os.environ['NNABLA_C_RUNTIME_REFERENCE_DIRECTORY'], name), 'w') as f:
            f.write(fixed8_data)
