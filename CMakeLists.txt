cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project (node-dectalk)
include_directories(${CMAKE_JS_INC})
include_directories(${CMAKE_SOURCE_DIR})
file(GLOB_RECURSE SOURCE_FILES "**.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})


set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)


# Include Node-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})



target_include_directories(${PROJECT_NAME} PRIVATE "/lib/dectalk")

# define NAPI_VERSION
add_definitions(-DNAPI_VERSION=7)