cmake_minimum_required(VERSION 3.23.2)
project(SmileEditor VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
    Smile
    GIT_REPOSITORY https://github.com/Saiteja1304/Smile.git
)
FetchContent_MakeAvailable(Smile)

file(GLOB SRC src/*.cpp src/*.c)
file(GLOB INCLUDE include/*.hpp include/../*.hpp)

add_executable(${PROJECT_NAME} SmileEditor.cpp
${SRC} ${INCLUDE})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} PUBLIC Smile)