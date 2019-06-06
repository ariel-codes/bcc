FROM gcc:9

# Install git, process tools
RUN apt-get update && apt-get -y install git procps
# Install C++ tools
RUN apt-get -y install build-essential cmake clang-format clang-tidy
# Install gcovr
RUN curl "https://bootstrap.pypa.io/get-pip.py" -o "/tmp/get-pip.py" && \
    python /tmp/get-pip.py && \
    pip install gcovr

# Clean up
RUN apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/* \
    && rm -rf /tmp

# Set the default shell to bash instead of sh
ENV SHELL /bin/bash