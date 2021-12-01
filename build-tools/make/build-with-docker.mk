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

########################################################################################################################
# General settings

NNABLA_C_RUNTIME_DIRECTORY ?= $(shell pwd)

NNABLA_C_RUNTIME_DOCKER_IMAGE_NAME_BASE ?= nnabla-c-runtime-build

NNABLA_C_RUNTIME_DOCKER_IMAGE_AUTO_FORMAT ?= $(NNABLA_C_RUNTIME_DOCKER_IMAGE_NAME_BASE)-auto-format
NNABLA_C_RUNTIME_DOCKER_IMAGE_DOC ?= $(NNABLA_C_RUNTIME_DOCKER_IMAGE_NAME_BASE)-doc
NNABLA_C_RUNTIME_DOCKER_IMAGE_BUILD ?= $(NNABLA_C_RUNTIME_DOCKER_IMAGE_NAME_BASE)-build
NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST ?= $(NNABLA_C_RUNTIME_DOCKER_IMAGE_NAME_BASE)-test

NNABLA_C_RUNTIME_DOCKER_RUN_OPTS +=--rm
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -v $$(pwd):$$(pwd)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -w $$(pwd)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -u $$(id -u):$$(id -g)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e HOME=/tmp

NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -v $(NNABLA_C_RUNTIME_DIRECTORY):$(NNABLA_C_RUNTIME_DIRECTORY)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e NNABLA_DIRECTORY=$(NNABLA_DIRECTORY)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e NNABLA_C_RUNTIME_DIRECTORY=$(NNABLA_C_RUNTIME_DIRECTORY)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e NNABLA_C_RUNTIME_REFERENCE_DIRECTORY=$(NNABLA_C_RUNTIME_REFERENCE_DIRECTORY)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e NNABLA_C_RUNTIME_TEST_DIRECTORY=$(NNABLA_C_RUNTIME_TEST_DIRECTORY)

NNABLA_C_RUNTIME_DOCKER_RUN_OPTS+= -e CRUNTIME_TEST_FUNCTION_LIST=$(CRUNTIME_TEST_FUNCTION_LIST)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS+= -e CRUNTIME_TEST_FUNCTION_EXCLUDE_LIST=$(CRUNTIME_TEST_FUNCTION_EXCLUDE_LIST)


## If your environment is under proxy uncomment following lines.
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS = --build-arg HTTP_PROXY=${http_proxy} --build-arg HTTPS_PROXY=${https_proxy}
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg http_proxy=${http_proxy} --build-arg https_proxy=${https_proxy}
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e http_proxy=${http_proxy}
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e https_proxy=${https_proxy}
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e ftp_proxy=${ftp_proxy}

# For pip install ${PIP_INS_OPTS} options
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg PIP_INS_OPTS='${PIP_INS_OPTS}' --build-arg PYTHONWARNINGS='${PYTHONWARNINGS}'
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e PIP_INS_OPTS="${PIP_INS_OPTS}"

# For yum install ${YUM_OPTS} options
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg YUM_OPTS='${YUM_OPTS}'

# For apt install ${APT_OPTS} options
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg APT_OPTS='${APT_OPTS}'

# For --add-host while docker build/run
ifneq  ("${http_proxy}","")

ADD_HOST=$(shell echo $(subst http://,,${http_proxy}) | cut -d ':' -f1)
ADD_HOST_IP=$(shell getent ahostsv4 ${ADD_HOST} | grep RAW | cut -d ' ' -f1)
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --add-host '${ADD_HOST}:${ADD_HOST_IP}'
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += --add-host '${ADD_HOST}:${ADD_HOST_IP}'

endif

# For download utils options
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg CURL_OPTS='${CURL_OPTS}'
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg WGET_OPTS='${WGET_OPTS}'
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e CURL_OPTS="${CURL_OPTS}"
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e WGET_OPTS="${WGET_OPTS}"

# For pytest options
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e PYTEST_OPTS="${PYTEST_OPTS}"

PYTHON_VERSION_MAJOR ?= 3
export PYTHON_VERSION_MAJOR
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg PYTHON_VERSION_MAJOR=$(PYTHON_VERSION_MAJOR)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e PYTHON_VERSION_MAJOR=$(PYTHON_VERSION_MAJOR)

PYTHON_VERSION_MINOR ?= 6
export PYTHON_VERSION_MINOR
NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS += --build-arg PYTHON_VERSION_MINOR=$(PYTHON_VERSION_MINOR)
NNABLA_C_RUNTIME_DOCKER_RUN_OPTS += -e PYTHON_VERSION_MINOR=$(PYTHON_VERSION_MINOR)

########################################################################################################################
# Docker images
.PHONY: nnabla-c-runtime-docker_image_auto_format
nnabla-c-runtime-docker_image_auto_format:
	docker pull ubuntu:18.04
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker build $(NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS) -t $(NNABLA_C_RUNTIME_DOCKER_IMAGE_AUTO_FORMAT) \
		-f build-tools/docker/Dockerfile.auto-format .

.PHONY: nnabla-c-runtime-docker_image_doc
nnabla-c-runtime-docker_image_doc:
	docker pull ubuntu:18.04
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker build $(NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS) -t $(NNABLA_C_RUNTIME_DOCKER_IMAGE_DOC) \
		-f build-tools/docker/Dockerfile.document .

.PHONY: nnabla-c-runtime-docker_image_build
nnabla-c-runtime-docker_image_build:
	docker pull ubuntu:18.04
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker build $(NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS) -t $(NNABLA_C_RUNTIME_DOCKER_IMAGE_BUILD) \
		-f build-tools/docker/Dockerfile.build .

.PHONY: nnabla-c-runtime-docker_image_test
nnabla-c-runtime-docker_image_test:
	docker pull ubuntu:18.04
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker build $(NNABLA_C_RUNTIME_DOCKER_BUILD_ARGS) -t $(NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST) \
		-f build-tools/docker/Dockerfile.test .

########################################################################################################################
# Auto Format

.PHONY: bwd-nnabla-c-runtime-auto-format
bwd-nnabla-c-runtime-auto-format: nnabla-c-runtime-docker_image_auto_format
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_AUTO_FORMAT) make nnabla-c-runtime-auto-format

########################################################################################################################
# Copyright check

.PHONY: bwd-nnabla-c-runtime-check-copyright
bwd-nnabla-c-runtime-check-copyright: nnabla-c-runtime-docker_image_auto_format
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) -v $$(pwd)/..:$$(pwd)/.. \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_AUTO_FORMAT) make nnabla-c-runtime-check-copyright


########################################################################################################################
# Doc
.PHONY: bwd-nnabla-c-runtime-doc
bwd-nnabla-c-runtime-doc: bwd-nnabla-c-runtime-build nnabla-c-runtime-docker_image_doc
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_DOC) make nnabla-c-runtime-doc

########################################################################################################################
# Build
.PHONY: bwd-nnabla-c-runtime-build
bwd-nnabla-c-runtime-build: nnabla-c-runtime-docker_image_build
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_BUILD) make nnabla-c-runtime-build

########################################################################################################################
# Examples
.PHONY: bwd-nnabla-c-runtime-examples
bwd-nnabla-c-runtime-examples: nnabla-c-runtime-docker_image_build
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_BUILD) make nnabla-c-runtime-examples

ifneq ("$(NNABLA_DIRECTORY)","")

########################################################################################################################
# Update function definition
.PHONY: bwd-nnabla-c-runtime-update-function-info
bwd-nnabla-c-runtime-update-function-info: nnabla-c-runtime-docker_image_test
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST) make nnabla-c-runtime-update-function-info

########################################################################################################################
# Check api_level of NNabla
.PHONY: bwd-check-api_level
bwd-check-api_level: nnabla-c-runtime-docker_image_test
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST) make check-api_level

########################################################################################################################
# Tests
.PHONY: bwd-nnabla-c-runtime-generate-function-test
bwd-nnabla-c-runtime-generate-function-test: nnabla-c-runtime-docker_image_test
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST) make nnabla-c-runtime-generate-function-test

.PHONY: bwd-nnabla-c-runtime-test-all-functions
bwd-nnabla-c-runtime-test-all-functions: nnabla-c-runtime-docker_image_test
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST) make nnabla-c-runtime-test-all-functions

ifneq ("$(NNABLA_EXAMPLES_DIRECTORY)","")

.PHONY: bwd-nnabla-c-runtime-generate-mnist-test
bwd-nnabla-c-runtime-generate-mnist-test: nnabla-c-runtime-docker_image_test
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST) make nnabla-c-runtime-generate-mnist-test

endif

endif

.PHONY: bwd-nnabla-c-runtime-shell
bwd-nnabla-c-runtime-shell:
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run -it $(NNABLA_C_RUNTIME_DOCKER_RUN_OPTS) \
		$(NNABLA_C_RUNTIME_DOCKER_IMAGE_TEST) make build-shell
