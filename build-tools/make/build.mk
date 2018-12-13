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

########################################################################################################################
# Suppress most of make message.
.SILENT:

NNABLA_C_RUNTIME_DIRECTORY ?= $(shell pwd)
NNABLA_C_RUNTIME_REFERENCE_DIRECTORY ?= $(NNABLA_C_RUNTIME_DIRECTORY)/build/test/nnabla
NNABLA_C_RUNTIME_TEST_DIRECTORY ?= $(NNABLA_C_RUNTIME_DIRECTORY)/build/test

export NNABLA_C_RUNTIME_REFERENCE_DIRECTORY
export NNABLA_C_RUNTIME_TEST_DIRECTORY
export CRUNTIME_TEST_FUNCTION_LIST
export CRUNTIME_TEST_FUNCTION_EXCLUDE_LIST

########################################################################################################################
# Build

.PHONY: nnabla-c-runtime-build
nnabla-c-runtime-build: nnabla-c-runtime-generate nnabla-c-runtime-auto-format nnabla-c-runtime-compile

.PHONY: nnabla-c-runtime-generate
nnabla-c-runtime-generate:
	@cd $(NNABLA_C_RUNTIME_DIRECTORY) && python3 build-tools/code-generator/generate.py
	@python3 build-tools/code-generator/header_create.py

.PHONY: nnabla-c-runtime-compile
nnabla-c-runtime-compile:
	@mkdir -p $(NNABLA_C_RUNTIME_DIRECTORY)/build
	@cd $(NNABLA_C_RUNTIME_DIRECTORY)/build && cmake ..
	@cd $(NNABLA_C_RUNTIME_DIRECTORY)/build && cmake --build . --target package

.PHONY: nnabla-c-runtime-examples
nnabla-c-runtime-examples: nnabla-c-runtime-build
	@make -C $(NNABLA_C_RUNTIME_DIRECTORY)/examples/callback

.PHONY: nnabla-c-runtime-clean
nnabla-c-runtime-clean:
	@rm -rf $(NNABLA_C_RUNTIME_DIRECTORY)/build
	@rm -rf $(NNABLA_C_RUNTIME_DIRECTORY)/doc/html

########################################################################################################################
# Document
.PHONY: nnabla-c-runtime-doc
nnabla-c-runtime-doc:
	@cd $(NNABLA_C_RUNTIME_DIRECTORY) && doxygen build-tools/doc/Doxyfile
	@cd $(NNABLA_C_RUNTIME_DIRECTORY) && rm -rf "?"  # plantuml(JRE?) creates '?' directory.

########################################################################################################################
# Auto format
.PHONY: nnabla-c-runtime-auto-format
nnabla-c-runtime-auto-format:
	@find $(NNABLA_C_RUNTIME_DIRECTORY) -type f -name "*.py" |xargs -n1 autopep8 -i
	@find $(NNABLA_C_RUNTIME_DIRECTORY) -type f -name "*.[ch]" |xargs -n1 clang-format -i

########################################################################################################################
# With NNabla

ifneq ("$(NNABLA_DIRECTORY)","")
.PHONY: nnabla-c-runtime-update-function-info
nnabla-c-runtime-update-function-info: nnabla-install
	@nnabla_cli function_info $(NNABLA_C_RUNTIME_DIRECTORY)/build-tools/code-generator/functions.yaml

.PHONY: nnabla-c-runtime-generate-function-test
nnabla-c-runtime-generate-function-test: nnabla-install
	@mkdir -p $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla
	@cd $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla && PYTHONPATH=$$(cd ../../../build-tools/test/callback && pwd) \
		python -m pytest ../../../../nnabla/python/test
	@NNABLA_C_RUNTIME_TEST_DIRECTORY=$(NNABLA_C_RUNTIME_TEST_DIRECTORY) $(NNABLA_C_RUNTIME_DIRECTORY)/build-tools/test/scripts/exec_all_functions.sh
	@python build-tools/test/scripts/generate_yaml.py
	@rm -rf $(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)/functions
	@mkdir -p $(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)/functions
	@ln $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla/succeed/*.nntxt $(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)/functions/
	@ln $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla/succeed/*.yaml $(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)/functions/
	@ln $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla/succeed/*_input_*.bin $(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)/functions/
	@ln $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla/succeed/*_output_?.bin $(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)/functions/
	@rm -f $(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)/functions/*_nnabla_cli_output_?.bin

.PHONY: nnabla-c-runtime-test-all-functions
nnabla-c-runtime-test-all-functions: nnabla-c-runtime-build nnabla-install
	@rm -rf $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla-c-runtime/nnb
	@rm -rf $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla-c-runtime/csrc
	@mkdir -p $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla-c-runtime/
	@python build-tools/test/scripts/create_nnabla_c_runtime_function_test_makefile.py
	@NNABLA_C_RUNTIME_REFERENCE_DIRECTORY=$(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY) \
	 NNABLA_C_RUNTIME_TEST_DIRECTORY=$(NNABLA_C_RUNTIME_TEST_DIRECTORY) \
		$(MAKE) -k -j1 -f $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/nnabla-c-runtime/test_functions.mk

ifneq ("$(NNABLA_EXAMPLES_DIRECTORY)","")

.PHONY: nnabla-c-runtime-generate-mnist-test
nnabla-c-runtime-generate-mnist-test: nnabla-c-runtime-build nnabla-install
	@mkdir -p $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist
	@cd $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist \
		&& python $(NNABLA_EXAMPLES_DIRECTORY)/mnist-collection/classification.py \
			--net lenet --max-iter 10
	@mv $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/tmp.monitor/lenet_result.nnp \
		$(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/
	@rm -f $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/lenet_result.nnb
	@nnabla_cli convert -b 1 $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/lenet_result.nnp \
		 $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/lenet_result.nnb
	@for bin in $(NNABLA_C_RUNTIME_DIRECTORY)/examples/data/[49]*.bin ;\
	do \
		echo $$bin ;\
		out=$$(basename $$bin .bin) ;\
		nnabla_cli infer -b 1 \
			-o $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/output_$$out \
			-c $(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/lenet_result.nnp \
			$$bin ;\
		valgrind $(NNABLA_C_RUNTIME_DIRECTORY)/build/src/nnablart/nnablart \
			infer \
				$(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/lenet_result.nnb \
				$$bin \
				$(NNABLA_C_RUNTIME_TEST_DIRECTORY)/mnist/nnb_$$out || true ;\
	done

endif

endif

.PHONY: build-shell
build-shell: nnabla-install
	PS1="compile-nnablart: " bash --norc -i
