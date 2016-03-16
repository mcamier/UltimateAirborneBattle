cmake_minimum_required(VERSION 3.3)
project(UAB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static-libstdc++ -static-libgcc -pthread -I/usr/include/SDL2 -Dmain=SDL_main -L/usr/lib -lSDL2main -lSDL2 -mwindows")

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(RAPIDXML REQUIRED)
find_package(RAPIDJSON REQUIRED)

include_directories ("${PROJECT_SOURCE_DIR}/../CompoteLib/include")

include_directories(${SDL2_INCLUDE_DIR})
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
set(LIBS kernel32 user32 gdi32 comdlg32 advapi32 shell32 ole32 oleaut32 odbc32 winspool uuid odbccp32 ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} CompoteLib)

add_executable(${EXENAME} WIN32 ${SOURCES})
target_link_libraries(${EXENAME} ${LIBS})

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
#set_target_properties(UAB PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
