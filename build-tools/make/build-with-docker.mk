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

########################################################################################################################
# General settings

NNABLA_C_RUNTIME_DIRECTORY ?= $(shell pwd)

DOCKER_IMAGE_NAME_BASE ?= nnabla-c-runtime-build

DOCKER_IMAGE_AUTO_FORMAT ?= $(DOCKER_IMAGE_NAME_BASE)-auto-format
DOCKER_IMAGE_DOC ?= $(DOCKER_IMAGE_NAME_BASE)-doc
DOCKER_IMAGE_BUILD ?= $(DOCKER_IMAGE_NAME_BASE)-build

DOCKER_RUN_OPTS +=--rm
DOCKER_RUN_OPTS += -v $$(pwd):$$(pwd)
DOCKER_RUN_OPTS += -w $$(pwd)
DOCKER_RUN_OPTS += -u $$(id -u):$$(id -g)
DOCKER_RUN_OPTS += -e HOME=/tmp

## If your environment is under proxy uncomment following lines.
DOCKER_BUILD_ARGS = --build-arg http_proxy=${http_proxy} --build-arg https_proxy=${https_proxy}
DOCKER_RUN_OPTS += -e http_proxy=${http_proxy}
DOCKER_RUN_OPTS += -e https_proxy=${https_proxy}
DOCKER_RUN_OPTS += -e ftp_proxy=${ftp_proxy}

########################################################################################################################
# Docker images
.PHONY: docker_image_auto_format
docker_image_auto_format:
	docker pull ubuntu:16.04
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker build $(DOCKER_BUILD_ARGS) -t $(DOCKER_IMAGE_AUTO_FORMAT) -f build-tools/docker/Dockerfile.auto-format .

.PHONY: docker_image_doc
docker_image_doc:
	docker pull ubuntu:16.04
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker build $(DOCKER_BUILD_ARGS) -t $(DOCKER_IMAGE_DOC) -f build-tools/docker/Dockerfile.doc .

.PHONY: docker_image_build
docker_image_build:
	docker pull ubuntu:16.04
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker build $(DOCKER_BUILD_ARGS) -t $(DOCKER_IMAGE_BUILD) -f build-tools/docker/Dockerfile.build .

########################################################################################################################
# Auto Format

.PHONY: bwd-auto-format
bwd-auto-format: docker_image_auto_format
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(DOCKER_RUN_OPTS) $(DOCKER_IMAGE_AUTO_FORMAT) make auto-format

########################################################################################################################
# Doc
.PHONY: bwd-doc
bwd-doc: bwd-build docker_image_doc
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(DOCKER_RUN_OPTS) $(DOCKER_IMAGE_DOC) make doc

########################################################################################################################
# Build
.PHONY: bwd-build
bwd-build: docker_image_build
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(DOCKER_RUN_OPTS) $(DOCKER_IMAGE_BUILD) make build

########################################################################################################################
# Examples
.PHONY: bwd-examples
bwd-examples: docker_image_build
	cd $(NNABLA_C_RUNTIME_DIRECTORY) \
	&& docker run $(DOCKER_RUN_OPTS) $(DOCKER_IMAGE_BUILD) make examples

