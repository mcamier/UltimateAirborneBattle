cmake_minimum_required(VERSION 3.3)
project(UAB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CompotePlusPlus_SOURCE_DIR}/cmake")

    set(GLM_ROOT_DIR "c:/VS_DEV_LIB/glm-0.9.7.3")
    set(SDL2_PATH "c:/VS_DEV_LIB/SDL2-2.0.4/i686-w64-mingw32")
    set(RapidXML_ROOT "c:/VS_DEV_LIB/rapidxml-1.13")
    set(RAPIDJSON_INCLUDEDIR "c:/VS_DEV_LIB/rapidjson")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(RAPIDXML REQUIRED)
find_package(RAPIDJSON REQUIRED)


include_directories ("${PROJECT_SOURCE_DIR}/../CompoteLib/include")


set(${SDL2_INCLUDE_DIR} "c:/VS_DEV_LIB/SDL2-2.0.4/i686-w64-mingw32/include")

include_directories("c:/VS_DEV_LIB/SDL2-2.0.4/i686-w64-mingw32/include")
#include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})

include_directories(${GLM_INCLUDE_DIR})
include_directories(${RAPIDJSON_INCLUDE_DIRS})
include_directories(${RAPIDXML_DIR})

file(
        GLOB_RECURSE
        SOURCES
        sources/*
)

set(EXENAME UAB)
set(LIBS ${LIBS} CompoteLib ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})

add_executable(${EXENAME} ${SOURCES})
target_link_libraries(${EXENAME} ${LIBS})

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
#set_target_properties(UAB PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
