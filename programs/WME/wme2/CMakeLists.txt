#
# Xin YUAN, 2019, BSD (2)
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
INCLUDE("${CMAKE_SOURCE_DIR}/../third/CSL/csl-base.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/../third/CSL/csl-main.cmk")
INCLUDE("${CMAKE_SOURCE_DIR}/../third/fltk/fltk.cmk")

PROJECT(tools)

ADD_DEFINITIONS(${STRING_CXX_FLAGS})

SET_CSL_PATH("${CMAKE_SOURCE_DIR}/../third/CSL/")
SET_FLTK_PATH("${CMAKE_SOURCE_DIR}/../third/fltk/")

#directories

ADD_SUBDIRECTORY(WmEditor WmEditor)

# end
