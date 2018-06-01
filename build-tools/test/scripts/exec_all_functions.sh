#!/bin/bash
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

set -eu
mkdir -p ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/succeed
mkdir -p ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/output_differ
mkdir -p ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/cannot_test

for f in $(find ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla -maxdepth 1 -name '*_???.nntxt' |sort)
do
    base=$(basename $f .nntxt)
    echo -n $base" "
    inputs=$(find ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla -maxdepth 1 -name ${base}_input_\?.bin |sort)
    output_prefix=${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/${base}_nnabla_cli_output
    if nnabla_cli infer -b 1 -c $f -o $output_prefix $inputs &> ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/${base}.log
    then
        result=0
        if python3 build-tools/test/scripts/diff_function_test_result.py ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/${base}_output_ ${output_prefix}_ # &>/dev/null
        then
            echo " Succeed"
            mv ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/${base}* ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/succeed
        else
            echo " Output Differ"
            mv ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/${base}* ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/output_differ
        fi

    else
        echo Cannot test
        mv ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/${base}* ${NNABLA_C_RUNTIME_TEST_DIRECTORY}/nnabla/cannot_test
    fi
done
