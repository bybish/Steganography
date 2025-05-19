FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    g++ cmake git libboost-all-dev \
    qtbase5-dev qtbase5-dev-tools qtchooser \
    qt5-qmake qttools5-dev qttools5-dev-tools \
    libpthread-stubs0-dev \
    libx11-xcb1 libxcb-xinerama0 libxcb-icccm4 libxcb-image0 libxcb-keysyms1 libxcb-render-util0 \
    libxcb-shape0 libxcb-sync1 libxcb-xfixes0 libxcb-randr0 libxcb-render0 libxcb-shm0 libxcb-glx0 \
    gdb gdbserver

WORKDIR /build
COPY ./src /src

RUN #cmake /src && make

CMD ["/bin/bash"]