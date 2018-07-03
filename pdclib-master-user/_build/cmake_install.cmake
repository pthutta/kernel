# Install script for directory: /home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/_build/libpdc.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/assert.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/ctype.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/float.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/inttypes.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/iso646.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/limits.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/locale.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/stdarg.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/stdbool.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/stddef.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/stdint.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/stdio.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/stdlib.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/stdnoreturn.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/string.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/threads.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/time.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/uchar.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/wchar.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/includes/wctype.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/internals/_PDCLIB_aux.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/internals/_PDCLIB_encoding.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/internals/_PDCLIB_float.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/internals/_PDCLIB_glue.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/internals/_PDCLIB_int.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/internals/_PDCLIB_io.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/internals/_PDCLIB_locale.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/opt/nothread/_PDCLIB_threadconfig.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/opt/tss_errno/errno.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/platform/example/includes/signal.h"
    "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/platform/example/internals/_PDCLIB_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/peter/Dokumenty/PB173/Kernel/kernel/pdclib-master-user/_build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
