# checkp2p build
FROM nvidia/cuda:12.1.1-devel-ubuntu22.04 as build
ENV PATH /usr/local/cuda/bin${PATH:+:${PATH}}
ENV LD_LIBRARY_PATH /usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}

# Update
RUN apt-get update

# Install dependencies
RUN apt-get install -y build-essential && \
    apt-get install -y clang && \
    apt-get install -y cmake && \
    apt-get install -y g++ && \

WORKDIR /checkp2p

# Build project
RUN make

# checp2p image
FROM nvidia/cuda:12.1.1-devel-ubuntu22.04
ENV PATH /usr/local/cuda/bin${PATH:+:${PATH}}
ENV LD_LIBRARY_PATH /usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}

# Update
RUN apt-get update

ENTRYPOINT [ "./checkp2p/p2pDevices" ]