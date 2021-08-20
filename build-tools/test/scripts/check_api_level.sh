# Copyright 2020,2021 Sony Corporation.
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
check_api_level_error=0
NNabla_api_level=`nnabla_cli function_info --api -1 | awk -F 'API_LEVEL: ' '{print $2}'`
Runtime_api_level=""

if [ ! $NNabla_api_level ]; then
  echo "nnabla_cli not found"
  exit -1
fi

for line in $($1/build/src/nnablart/nnablart version);
do
  if [[ $line =~ "API_LEVEL" ]]
  then
    Runtime_api_level=`echo $line | awk -F "_" '{print $3}' | sed "s/]//g"`
  fi
done

if [ "$NNabla_api_level" -ne "$Runtime_api_level" ];then
  echo "The api_level version of NNabla and NNabla-c-runtime are not synchronized." >&2
  check_api_level_error=1
fi
exit $check_api_level_error
