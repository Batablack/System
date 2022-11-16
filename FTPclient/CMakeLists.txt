cmake_minimum_required(VERSION 3.10)
project(FTPclient)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_BUILD_TYPE Release)
SET(CROSS_COMPILE 1)
IF(CROSS_COMPILE)
    SET(CMAKE_SYSTEM_NAME linux)
    SET(TOOLCHAIN_DIR /opt/hisi-linux/x86-arm/arm-himix200-linux/)

    # specify the cross compiler
    SET(CMAKE_C_COMPILER   ${TOOLCHAIN_DIR}/bin/arm-himix200-linux-gcc)
    SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/arm-himix200-linux-g++)
    SET(GNU_FLAGS "-mfpu=vfp -fPIC")
    SET(CMAKE_CXX_FLAGS "${GNU_FLAGS} ")
    SET(CMAKE_C_FLAGS "${GNU_FLAGS} ")

    # where is the target environment
    SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_DIR}
            ${TOOLCHAIN_DIR}/include
            ${TOOLCHAIN_DIR}/lib)

    # search for programs in the build host directories (notnecessary)
    SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

    # for libraries and headers in the target directories
    SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    SET(CMAKE_CXX_FLAGS "-O3 -mfpu=neon-vfpv4 -mfloat-abi=softfp")
ENDIF(CROSS_COMPILE)



link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/nanomsg)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(ftp.exe
      demo.cpp
        src/THFTPAPI.c
        src/THFTPAPI.h
        src/json.hpp src/rjson.cpp src/rjson.h
        src/bcflag.cpp src/bcflag.h
        src/FTPcfg.h)

