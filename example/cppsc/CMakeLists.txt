﻿# CMakeList.txt: libcpps 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project(cppsc)

# 将源代码添加到此项目的可执行文件。
message(${PROJECT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../bin)

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}  SRC_LIST)


IF(WIN32)
	
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin)

ELSE()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)
ENDIF()

add_executable (${PROJECT_NAME} ${SRC_LIST})

IF(WIN32)
	target_link_libraries(${PROJECT_NAME} cpps)
ELSE()
	target_link_libraries(${PROJECT_NAME} -lrt -ldl -lm -lpthread -lcpps)

	add_custom_command(TARGET cppsc
	  POST_BUILD 
	  COMMAND rm -rf ${CMAKE_INSTALL_PREFIX}/local/bin/cppsc
	  COMMAND ln -s ${PROJECT_SOURCE_DIR}/../../bin/cppsc ${CMAKE_INSTALL_PREFIX}/local/bin/cppsc
	 )
#	不在安装 cppsc 到系统目录,需要手动建立软连接.
# 	install(TARGETS cppsc
#	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/local/bin/)
ENDIF()
