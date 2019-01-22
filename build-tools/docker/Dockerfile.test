FROM ubuntu:16.04

ENV LANG en_US.UTF-8

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    bzip2 \
    clang-format \
    wget \
    cmake \
    make \
    valgrind \
    wget \
    && apt-get -yqq clean \
    && rm -rf /var/lib/apt/lists/*

RUN umask 0 \
    && wget --no-check-certificate https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && bash Miniconda3-latest-Linux-x86_64.sh -b -p /opt/miniconda3 \
    && rm -rf Miniconda3-latest-Linux-x86_64.sh

ENV PATH /opt/miniconda3/bin:$PATH

RUN set -xe \
    && umask 0 \
    && conda update -y -n base conda -c defaults \
    && conda create -y -n py35 python=3.5

RUN /bin/bash -c "source activate py35 \
    && pip install 'Cython>=0.25,<0.26' autopep8 boto3 \
       configparser contextlib2 futures h5py mako \
       'numpy<1.16' protobuf pyyaml requests scikit-image scikit_image scipy tqdm \
    && pip install pytest"

ENV PATH /opt/miniconda3/envs/py35/bin:$PATH
