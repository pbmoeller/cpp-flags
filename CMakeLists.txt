####################################################################################################
### Project
cmake_minimum_required(VERSION 3.15)

project(cppflags
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

####################################################################################################
### Library
set(CPPFLAGS_HEADERS
    "${PROJECT_SOURCE_DIR}/include/cppflags/cppflags.hpp"
)

add_library(cppflags INTERFACE)

target_include_directories(cppflags
    INTERFACE
        $<BUILD_INTERFACE:"${CMAKE_CURRENT_SOURCE_DIR}/include">
        $<INSTALL_INTERFACE:"${CMAKE_INSTALL_INCLUDEDIR}">
)
target_sources(cppflags
    PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
        FILES ${CPPFLAGS_HEADERS}
)

####################################################################################################
### CMake Config
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cppflagsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cppflagsConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cppflags"
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cppflagsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

####################################################################################################
### Install
include(GNUInstallDirs)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cppflagsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cppflagsConfigVersion.cmake"
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/cppflags"
)
install(
    TARGETS     cppflags
    EXPORT      cppflagsTargets
    LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME     DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET    public_headers
)
install(
    EXPORT cppflagsTargets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cppflags"
)