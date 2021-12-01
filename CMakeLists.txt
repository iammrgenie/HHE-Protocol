cmake_minimum_required(VERSION 3.13)
project(HHEnisec)

add_executable(hheseal)

target_sources(hheseal
    PRIVATE
        HHE_NISEC_seal.cpp
        HHE/ciphers/common/SEAL_Cipher.cpp
        HHE/ciphers/common_Zp/SEAL_Cipher.cpp
        HHE/ciphers/pasta_3/seal/pasta_3_seal.cpp
        HHE/ciphers/pasta_3/plain/pasta_3_plain.cpp
)

find_package(SEAL 3.6.2 REQUIRED
    # Optionaly providing a path so this can be built without installing SEAL
    PATHS HHE/thirdparty/SEAL/build/cmake
)

#=======================================================================================================================================
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(CheckCCompilerFlag)
function(check_c_compiler_flag_and_add flag result)
  check_c_compiler_flag("${flag}" ${result})
  if(${result})
    add_compile_options("${flag}")
  endif()
endfunction()

# check_c_compiler_flag_and_add(-pedantic CC_SUPPORTS_PEDANTIC)
# check_c_compiler_flag_and_add(-Wall CC_SUPPORTS_WALL)
# check_c_compiler_flag_and_add(-Wextra CC_SUPPORTS_WEXTRA)
# check_c_compiler_flag_and_add(-Wshadow CC_SUPPORTS_WSHADOW)
# check_c_compiler_flag_and_add(-Werror=vla CC_SUPPORTS_ERRORVLA)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build." FORCE)
endif()

# for AES code
if(MSVC)
  add_definitions("-DOC_ENABLE_SSE2")
  message("-- Enabling SSE2 for AES")
  add_definitions("-DOC_ENABLE_AESNI")
  message("-- Enabling AES_NI")
else()
  check_c_compiler_flag_and_add(-msse2 CC_SUPPORTS_SSE2)
  if(CC_SUPPORTS_SSE2)
    add_definitions("-DOC_ENABLE_SSE2")
    message("-- Enabling SSE2 for AES")
  endif()

  check_c_compiler_flag_and_add(-maes CC_SUPPORTS_AES)
  if(CC_SUPPORTS_AES)
    add_definitions("-DOC_ENABLE_AESNI")
    message("-- Enabling AES_NI")
  else()
    add_definitions("-DOC_ENABLE_PORTABLE_AES")
  endif()
endif()
#=============================================================================================================================================

add_subdirectory(HHE/util)

set(M4RI_PREFIX "HHE/thirdparty/m4ri/installed")
set(M4RI_INCLUDE_DIR "${M4RI_PREFIX}/include")
set(M4RI_LIB "${M4RI_PREFIX}/lib/libm4ri.so")


target_include_directories(hheseal PRIVATE ${M4RI_INCLUDE_DIR})
target_link_libraries(hheseal SEAL::seal keccak aes)