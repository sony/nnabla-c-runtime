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
.PHONY: all
all: bwd-nnabla-c-runtime-build bwd-nnabla-c-runtime-doc

.PHONY: clean
clean: nnabla-c-runtime-clean

.PHONY: clean-all
clean-all:
	@git clean -fdx

########################################################################################################################
# Include NNABLA make file if exists.
PYTHON_VERSION_MAJOR ?= 3
PYTHON_VERSION_MINOR ?= 7
BUILD_DIRECTORY_WHEEL_SUFFIX ?= _py$(PYTHON_VERSION_MAJOR)$(PYTHON_VERSION_MINOR)

ifneq ("$(wildcard ../nnabla)","")
	NNABLA_DIRECTORY = $(shell echo `cd ../nnabla ; pwd`)
	DOCKER_RUN_OPTS += -v $(NNABLA_DIRECTORY):$(NNABLA_DIRECTORY)
	include $(NNABLA_DIRECTORY)/build-tools/make/build.mk
	include $(NNABLA_DIRECTORY)/build-tools/make/build-with-docker.mk
endif

ifneq ("$(wildcard ../nnabla-examples)","")
	NNABLA_EXAMPLES_DIRECTORY = $(shell echo `cd ../nnabla-examples ; pwd`)
	DOCKER_RUN_OPTS += -v $(NNABLA_EXAMPLES_DIRECTORY):$(NNABLA_EXAMPLES_DIRECTORY)
endif

########################################################################################################################
# NNabla C Runtime

include build-tools/make/build.mk
include build-tools/make/build-with-docker.mk
