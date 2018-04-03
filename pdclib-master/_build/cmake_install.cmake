# Install script for directory: /home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/_build/libpdc.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/assert.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/ctype.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/float.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/inttypes.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/iso646.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/limits.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/locale.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/stdarg.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/stdbool.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/stddef.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/stdint.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/stdio.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/stdlib.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/stdnoreturn.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/string.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/threads.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/time.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/uchar.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/wchar.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/includes/wctype.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/internals/_PDCLIB_aux.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/internals/_PDCLIB_encoding.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/internals/_PDCLIB_float.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/internals/_PDCLIB_glue.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/internals/_PDCLIB_int.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/internals/_PDCLIB_io.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/internals/_PDCLIB_locale.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/opt/nothread/_PDCLIB_threadconfig.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/opt/tss_errno/errno.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/platform/example/includes/signal.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/platform/example/internals/_PDCLIB_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master/_build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
