cmake_minimum_required(VERSION 3.10)

project(multiemu-c99)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64" OR CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")
endif()

set(FEATURES_SOURCES
    src/features/gen_avsmp.c
    src/features/gen_oldrevemu.c
    src/features/gen_revemu.c
    src/features/gen_revemu2013.c
    src/features/gen_sc2009.c
    src/features/gen_setti.c
    src/features/gen_steamemu.c
)

set(UTILS_SOURCES
    src/utils/rev_data.c
    src/utils/rev_spoofer.c
    src/utils/sse_hash.c
)

set(IMPL_SOURCES
    src/impl/emu_impl.c
)

set(CRYPTO_SOURCES
    vendor/rijndael-c99/rijndael_c99.c
    vendor/crypto-algorithms/sha256.c
)

set(SOURCES
    ${FEATURES_SOURCES}
    ${UTILS_SOURCES}
    ${CRYPTO_SOURCES}
    ${IMPL_SOURCES}
)

add_library(multiemu SHARED src/main.c ${SOURCES})