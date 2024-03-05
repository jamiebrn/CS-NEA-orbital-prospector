cmake_minimum_required(VERSION 3.18)
project(OrbitalProspector LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(PHYSFS_BUILD_DOCS OFF)
option(PHYSFS_BUILD_SHARED OFF)
option(PHYSFS_DISABLE_INSTALL "Disable installing PhysFS" ON)
option(PHYSFS_BUILD_TEST OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 938e90b7d2b345d06783ba88fe8d8e1ca2f09855
)

FetchContent_Declare(
    physfs
    GIT_REPOSITORY https://github.com/icculus/physfs
    GIT_TAG "release-3.2.0"
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(physfs)

include_directories(include/)
include_directories(${physfs_SOURCE_DIR}/src)
link_directories(${physfs_BUILD_DIR})

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(OrbitalProspector ${SRC_FILES})
target_link_libraries(OrbitalProspector PRIVATE sfml-graphics)
target_link_libraries(OrbitalProspector PRIVATE sfml-audio)
target_link_libraries(OrbitalProspector PRIVATE physfs-static)
target_link_options(OrbitalProspector PRIVATE -static)
target_compile_features(OrbitalProspector PRIVATE cxx_std_17)
target_sources(OrbitalProspector PRIVATE "dev_resources/icon_data.rc")

if(WIN32)
    add_custom_command(
        TARGET OrbitalProspector
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:OrbitalProspector>
        VERBATIM)
endif()

ADD_CUSTOM_COMMAND(
    TARGET OrbitalProspector
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E tar cvf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data.bin --format=zip -- .
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dev_resources/Data
)

install(TARGETS OrbitalProspector)
