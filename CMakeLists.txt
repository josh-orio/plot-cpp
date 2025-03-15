cmake_minimum_required(VERSION 3.15)
project(plot-cpp-example)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(plot-cpp)

add_executable(${PROJECT_NAME} main.cpp)

# target_link_libraries(${PROJECT_NAME} PRIVATE plot-cpp)

# find & link Python3
find_package(Python3 COMPONENTS Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Python3_LIBRARIES})

# find & link a json librarys
find_package(nlohmann_json REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

find_package(plot-cpp REQUIRED) # find plot-cpp
target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include/) # include to make header visible to main
target_link_libraries(${PROJECT_NAME} PRIVATE plot-cpp::plot-cpp) # link the plot-cpp .a
