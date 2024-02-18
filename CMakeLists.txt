cmake_minimum_required(VERSION 3.16)
project(OrbitalProspector LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 938e90b7d2b345d06783ba88fe8d8e1ca2f09855)
FetchContent_MakeAvailable(SFML)

include_directories(include/)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(OrbitalProspector ${SRC_FILES})
target_link_libraries(OrbitalProspector PRIVATE sfml-graphics)
target_link_libraries(OrbitalProspector PRIVATE sfml-audio)
target_compile_features(OrbitalProspector PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET OrbitalProspector
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:OrbitalProspector>
        VERBATIM)
endif()

install(TARGETS OrbitalProspector)
