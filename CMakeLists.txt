## This file is a quick tutorial on writing CMakeLists for targeting the Vita
cmake_minimum_required(VERSION 3.2)


## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is
# highly recommended that you include this block for all projects.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()


## Define project parameters here
# Name of the project
project(vitanet)
# This line adds Vita helper macros, must go after project definition in order
# to build Vita specific artifacts (self/vpk).
include("${VITASDK}/share/vita.cmake" REQUIRED)


## Configuration options for this app
# Display name (under bubble in LiveArea)
set(VITA_APP_NAME "Vitanet")
# Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X =
# unique string of developer and Y = a unique number for this app
set(VITA_TITLEID "VSDK00006")
# Optional version string to show in LiveArea's more info screen
set(VITA_VERSION "01.00")


add_compile_options(
  -Ofast -std=gnu11
  -Wall -Wextra -Wdouble-promotion -Wshadow -Wundef -Wno-write-strings -Wno-unused-parameter
  -fsingle-precision-constant -fno-common
)


## Flags and includes for building
# Note that we make sure not to overwrite previous flags
# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")
set(PSVITAIP "192.168.2.208" CACHE STRING "PSVita IP (for FTP access)")


# Add any additional include paths here
include_directories(
  $ENV{VITASDK}/arm-vita-eabi/include/python2.7
)


## Build and link
# Add all the files needed to compile here
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/classes/search_result_class.hpp
  src/services/scraper.hpp
  src/services/ime.hpp
  src/screens/home_screen.hpp
  src/screens/search_screen.hpp
  src/screens/article_screen.hpp
)


# Library to link to (drop the -l prefix). This will mostly be stubs.
target_link_libraries(${PROJECT_NAME}
  python2.7
  pthread
  debugnet
  curl
  vita2d
  freetype
  png
  jpeg
  bz2
  ScePgf_stub
  ScePvf_stub
  SceGxm_stub
  SceCtrl_stub
  SceTouch_stub
  SceAppUtil_stub
  SceDisplay_stub
  SceLibKernel_stub
  SceSysmodule_stub
  ScePower_stub
  SceCommonDialog_stub
  SceRegistryMgr_stub
  SceAppMgr_stub
  SceHttp_stub
  SceNet_stub
  SceNetCtl_stub
  SceIme_stub
  ssl
  crypto
  mpdec
  z
  m
  c
)


## Create Vita files
vita_create_self(eboot.bin ${PROJECT_NAME})
# The FILE directive lets you add additional files to the VPK, the syntax is
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} eboot.bin
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE assets/font.ttf assets/font.ttf
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE src/services/scraper.py lib/services/scraper.py
  FILE $ENV{VITASDK}/arm-vita-eabi/lib/python27.zip lib/python27.zip
)


add_custom_target(send ALL
  COMMAND echo destroy | nc ${PSVITAIP} 1338
  COMMAND curl -T eboot.bin ftp://${PSVITAIP}:1337/ux0:/app/${VITA_TITLEID}/
  COMMAND curl -T ${CMAKE_CURRENT_SOURCE_DIR}/src/services/scraper.py ftp://${PSVITAIP}:1337/ux0:/app/${VITA_TITLEID}/lib/services/
  COMMAND echo launch ${VITA_TITLEID} | nc ${PSVITAIP} 1338
  DEPENDS ${PROJECT_NAME}.vpk-vpk
)
