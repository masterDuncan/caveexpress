cmake_minimum_required(VERSION 2.6)

set(ROOT_DIR ${PROJECT_SOURCE_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR})

option(RELEASE "Build a release build" OFF)

#-------------------------------------------------------------------------------
# macros
#-------------------------------------------------------------------------------

macro(texture_file_write TARGET_FILE FILEENTRY)
	file(READ ${FILEENTRY} CONTENTS)
	string(REGEX REPLACE ";" "\\\\;" CONTENTS "${CONTENTS}")
	string(REGEX REPLACE "\n" ";" CONTENTS "${CONTENTS}")
	list(REMOVE_AT CONTENTS 0 -2)
	foreach(LINE ${CONTENTS})
		file(APPEND ${TARGET_FILE} "${LINE}\n")
	endforeach()
endmacro()

macro(texture_merge TARGET_FILE FILELIST_BIG FILELIST_SMALL)
	file(WRITE ${TARGET_FILE} "")

	file(APPEND ${TARGET_FILE} "texturesbig = {\n")
	foreach(FILEENTRY ${FILELIST_BIG})
		texture_file_write(${TARGET_FILE} ${FILEENTRY})
	endforeach()
	file(APPEND ${TARGET_FILE} "}\n")

	file(APPEND ${TARGET_FILE} "texturessmall = {\n")
	foreach(FILEENTRY ${FILELIST_SMALL})
		texture_file_write(${TARGET_FILE} ${FILEENTRY})
	endforeach()
	file(APPEND ${TARGET_FILE} "}\n")
endmacro()

macro(textures PROJECTNAME)
	file(GLOB FILELIST_BIG ${ROOT_DIR}/contrib/assets/png-packed/${PROJECTNAME}-*-big.lua)
	file(GLOB FILELIST_SMALL ${ROOT_DIR}/contrib/assets/png-packed/${PROJECTNAME}-*-small.lua)
	message("build complete.lua: ${ROOT_DIR}/contrib/assets/png-packed/${PROJECTNAME}")
	texture_merge(${PROJECT_BINARY_DIR}/complete.lua.in "${FILELIST_BIG}" "${FILELIST_SMALL}")
	configure_file(${PROJECT_BINARY_DIR}/complete.lua.in ${ROOT_DIR}/base/${PROJECTNAME}/textures/complete.lua COPYONLY)
endmacro()

#-------------------------------------------------------------------------------
# macros end
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# variables
#-------------------------------------------------------------------------------

set(WINDOWS 0)
set(DARWIN 0)
set(LINUX 0)
if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
	set(WINDOWS 1)
elseif (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
	set(DARWIN 1)
elseif (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
	set(LINUX 1)
else()
	message(WARNING "Unknown host system - default to linux")
	set(LINUX 1)
endif()

#-------------------------------------------------------------------------------
# end variables
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# options
#-------------------------------------------------------------------------------

option(NETWORKING "Enable networking" ON)

#-------------------------------------------------------------------------------
# end options
#-------------------------------------------------------------------------------

if (NOT CMAKE_TOOLCHAIN_FILE)
	if (WINDOWS)
		include(${ROOT_DIR}/cmake/windows.cmake)
	elseif (DARWIN)
		include(${ROOT_DIR}/cmake/darwin.cmake)
	else()
		include(${ROOT_DIR}/cmake/linux.cmake)
	endif()
endif()

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/libs")

if(CMAKE_BUILD_TYPE STREQUAL "")
set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_program(CCACHE "ccache")
if (CCACHE)
	message("Using ccache")
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE})
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE})
else()
	message(WARNING "ccache not found")
endif()

include_directories("${PROJECT_SOURCE_DIR}/src/libs/lua")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/Box2D")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/tinyxml2")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/sqlite")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/gtest/include")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/gtest")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/libogg-1.3.1/include")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/libpng-1.6.2")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/yajl")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL_mixer")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL_net")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL_image")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL/include")
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL/src")
include_directories("${PROJECT_SOURCE_DIR}/src/modules")
include_directories("${PROJECT_SOURCE_DIR}/src/modules/game")

if(UNIX)
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL/linux")
include_directories("/usr/include/dbus-1")
else()
include_directories("${PROJECT_SOURCE_DIR}/src/libs/SDL/general")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src/libs)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/modules)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/tests)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/cavepacker)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/caveexpress)
