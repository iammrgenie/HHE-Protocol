# Install script for directory: /home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so.2.1.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so.2.1.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so.2.1.0"
         RPATH "$ORIGIN/:/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/NTL/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/lib/libhelib.so.2.1.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so.2.1.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so.2.1.0")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so.2.1.0"
         OLD_RPATH "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/NTL/usr/local/lib:::::::::"
         NEW_RPATH "$ORIGIN/:/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/NTL/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so.2.1.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so"
         RPATH "$ORIGIN/:/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/NTL/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/lib/libhelib.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so"
         OLD_RPATH "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/NTL/usr/local/lib:::::::::"
         NEW_RPATH "$ORIGIN/:/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/NTL/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libhelib.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/helib" TYPE FILE FILES
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/helib.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/apiAttributes.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/ArgMap.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/binaryArith.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/binaryCompare.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/bluestein.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/ClonedPtr.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/CModulus.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/CtPtrs.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/Ctxt.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/debugging.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/DoubleCRT.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/EncryptedArray.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/EvalMap.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/Context.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/FHE.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/keys.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/keySwitching.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/log.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/hypercube.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/IndexMap.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/IndexSet.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/intraSlot.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/JsonWrapper.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/matching.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/matmul.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/Matrix.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/multicore.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/norms.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/NumbTh.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/PAlgebra.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/partialMatch.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/permutations.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/polyEval.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/PolyMod.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/PolyModRing.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/powerful.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/primeChain.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/PtrMatrix.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/PtrVector.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/Ptxt.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/randomMatrices.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/range.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/recryption.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/replicate.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/sample.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/scheme.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/set.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/SumRegister.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/tableLookup.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/timing.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/zzX.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/assertions.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/exceptions.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/PGFFT.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/fhe_stats.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/zeroValue.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/include/helib/EncodedPtxt.h"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/src/helib/version.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/helib/helibTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/helib/helibTargets.cmake"
         "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/src/CMakeFiles/Export/share/cmake/helib/helibTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/helib/helibTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/helib/helibTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/helib" TYPE FILE FILES "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/src/CMakeFiles/Export/share/cmake/helib/helibTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/helib" TYPE FILE FILES "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/src/CMakeFiles/Export/share/cmake/helib/helibTargets-relwithdebinfo.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/helib" TYPE FILE FILES
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/src/helibConfig.cmake"
    "/home/mrgenie/Projects/HHE-Protocol/HHE/thirdparty/HElib/src/helibConfigVersion.cmake"
    )
endif()

