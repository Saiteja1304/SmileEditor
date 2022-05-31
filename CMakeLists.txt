cmake_minimum_required(VERSION 3.23.2)
project(SmileEditor VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
    Smile
    GIT_REPOSITORY https://github.com/Saiteja1304/Smile.git
    GIT_TAG testing-master
)
FetchContent_MakeAvailable(Smile)

file(GLOB SRC src/*.cpp src/*.c)
file(GLOB INCLUDE include/*.hpp include/../*.hpp)

add_executable(${PROJECT_NAME} SmileEditor.cpp
${SRC} ${INCLUDE})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} PUBLIC Smile)