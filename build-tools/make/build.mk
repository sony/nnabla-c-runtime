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

########################################################################################################################
# Suppress most of make message.
.SILENT:

NNABLA_C_RUNTIME_DIRECTORY ?= $(shell pwd)
NNABLA_C_RUNTIME_REFERENCE_DIRECTORY ?= $(NNABLA_C_RUNTIME_DIRECTORY)/build/test/nnabla
NNABLA_C_RUNTIME_TEST_DIRECTORY ?= $(NNABLA_C_RUNTIME_DIRECTORY)/build/test
NNABLA_VERSION ?= $$(cat $(NNABLA_DIRECTORY)/VERSION.txt)
API_LEVEL ?= $$(nnabla_cli function_info --api -1|grep API_LEVEL)

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
# Check copyright
.PHONY: nnabla-c-runtime-check-copyright
nnabla-c-runtime-check-copyright:
	python3 $(NNABLA_DIRECTORY)/build-tools/code_formatter/copyright_checker.py --rootdir=$(NNABLA_C_RUNTIME_DIRECTORY)


########################################################################################################################
# With NNabla

ifneq ("$(NNABLA_DIRECTORY)","")
.PHONY: nnabla-c-runtime-update-function-info
nnabla-c-runtime-update-function-info: nnabla-install
	@nnabla_cli function_info -x Einsum -o $(NNABLA_C_RUNTIME_DIRECTORY)/build-tools/code-generator/functions.yaml
	@sed -i -e "s/\(NNABLA_VERSION: \).*/\1$(NNABLA_VERSION)/" $(NNABLA_C_RUNTIME_DIRECTORY)/VERSION.txt
	@sed -i -e "s/API_LEVEL:.*/$(API_LEVEL)/" $(NNABLA_C_RUNTIME_DIRECTORY)/VERSION.txt

.PHONY: check-api_level
check-api_level: nnabla-c-runtime-build nnabla-install
	@bash ./build-tools/test/scripts/check_api_level.sh $(NNABLA_C_RUNTIME_DIRECTORY)

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
