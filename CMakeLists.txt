cmake_minimum_required(VERSION 3.28.0)
project(cplotlib LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_library(cplotlib ${SOURCES})
target_include_directories(cplotlib PRIVATE include)

find_package(nlohmann_json REQUIRED)
target_link_libraries(cplotlib PUBLIC nlohmann_json::nlohmann_json)

find_package(Python3 COMPONENTS Development REQUIRED)
target_include_directories(cplotlib PUBLIC ${Python3_INCLUDE_DIRS})
target_link_libraries(cplotlib PUBLIC ${Python3_LIBRARIES})

set_target_properties(cplotlib
    PROPERTIES
    CMAKE_CXX_STANDARD 20
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_EXTENSIONS OFF
)

include(GNUInstallDirs)

target_include_directories(cplotlib
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS cplotlib
    EXPORT cplotlibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cplotlib)

install(EXPORT cplotlibTargets
    FILE cplotlibTargets.cmake
    NAMESPACE cplotlib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cplotlib
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/cplotlibConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cplotlib
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cplotlibConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cplotlib
)
