FROM gcc:11.3.0
FROM drogon:latest

# директория для сборки GoogleTest
RUN mkdir /gtest_build && cd /gtest_build

RUN apt-get update && \
    apt-get install -y \
        cmake \
        libgtest-dev \
        libboost-dev libboost-program-options-dev \
        google-mock \
    && \
    cmake -DCMAKE_BUILD_TYPE=Release /usr/src/gtest && \
    cmake --build .
    #mv lib/lib*.a /usr/lib

# директория бэкенда
ADD ./backend /app/backend

# директория сборки бэкенда
RUN mkdir /app/build && cd /app/build

# установление зависимостей для основго проекта
RUN apt-get install -y \
        qtbase5-dev \
        qtchooser \
        qtbase5-dev-tools \ 
        libpqxx-dev \
        mysql-server \
        libmysqlcppconn-dev \
        libpng-dev \ 
        zlib1g-dev \
        libjsoncpp-dev \
        libboost-dev \
        libssl-dev \
        lcov \
        libboost-all-dev

# поддержка jwt
RUN rm -rf /jwt-cpp && \
    git clone https://github.com/pokowaka/jwt-cpp.git && \
    cd /jwt-cpp && \
    mkdir ./release && \
    #ls /jwt-cpp && \
    cd ./release \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    #mv -t /jwt-cpp/release /CMakeCache.txt /CMakeFiles /cmake_install.cmake /Makefile  && \
    #cd / && \
    pwd && \
    ls /jwt-cpp/release && \
    #pwd && \
    #ls /jwt-cpp/release && \
    #make install
    cd / && make install
    #/jwt-cpp/ext /jwt-cpp/src /jwt-cpp/test

# поддержка redis
RUN cd / && \
    git clone https://github.com/sewenew/redis-plus-plus.git && \
    cd redis-plus-plus && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install && \
    cd ..

# сборка приложения
RUN cd /app/build && \
    pwd && \
    cmake /app/backend/ppo_cg_course && \
    cmake --build .


