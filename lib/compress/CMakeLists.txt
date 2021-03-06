﻿# CMakeList.txt: libcpps 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project(compress)

# 将源代码添加到此项目的可执行文件。

IF(WIN32)
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../include ${PROJECT_SOURCE_DIR}/../../deps/deps/include)
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../bin ${PROJECT_SOURCE_DIR}/../../deps/deps/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/lib/${PROJECT_NAME})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/lib/${PROJECT_NAME})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../../bin/lib/${PROJECT_NAME})


	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/lib/${PROJECT_NAME})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/lib/${PROJECT_NAME})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../../bin/lib/${PROJECT_NAME})
ELSE()
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../include /usr/local/include)
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../bin  /lib /usr/lib)
	SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin/lib/${PROJECT_NAME}) 
ENDIF()

file(GLOB_RECURSE CURRENT_HEADERS  *.h)
file(GLOB_RECURSE CURRENT_HEADERS2  minizip/*.h)
source_group("Include" FILES ${CURRENT_HEADERS}) 
source_group("Include/minizip" FILES ${CURRENT_HEADERS}) 

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} SRC_LIST)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/minizip SRC_LIST2)



ADD_LIBRARY (${PROJECT_NAME} SHARED ${SRC_LIST} ${SRC_LIST2} ${CURRENT_HEADERS})
IF(WIN32)
	target_link_libraries(${PROJECT_NAME} cpps zdll zlib )
ELSE()
	target_link_libraries(${PROJECT_NAME} -lcpps -lz -lrt -ldl -lm -lpthread)
ENDIF()
