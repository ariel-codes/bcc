#-------------------------------------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See https://go.microsoft.com/fwlink/?linkid=2090316 for license information.
#-------------------------------------------------------------------------------------------------------------

FROM debian:9

# Install git, process tools
RUN apt-get update && apt-get -y install git procps curl

# Install C++ tools
# RUN add-apt-repository ppa:jonathonf/gcc-9.0 \
#     && apt-get -y install gcc-9 g++-9
RUN apt-get -y install build-essential cmake clang-format clang-tidy
# Install gcovr
RUN curl "https://bootstrap.pypa.io/get-pip.py" -o "/tmp/get-pip.py" \
    && python /tmp/get-pip.py \
    && pip install gcovr

# Clean up
RUN apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

# Set the default shell to bash instead of sh
ENV SHELL /bin/bash
