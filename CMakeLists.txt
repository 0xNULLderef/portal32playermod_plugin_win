cmake_minimum_required(VERSION 3.0.0)
project(portal32playermod_plugin VERSION 0.1.0)

# set(TARGET_DIR "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Portal 2\\portal2")

FILE(GLOB cppSrc *.cpp)
add_library(32pmod SHARED ${cppSrc})
target_include_directories(32pmod PRIVATE .)
# add_custom_command(TARGET 32pmod POST_BUILD
	# COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:32pmod> ${TARGET_DIR}\\32pmod.dll
	# COMMENT "Created ${TARGET_DIR}\\32pmod.dll"
# )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -g -Wall -Werror -O0")
SET(CMAKE_SHARED_LINKER_FLAGS "-m32 -static")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
