cmake_minimum_required(VERSION 2.8.3)
project(rosppm)

include_directories(${catkin_INCLUDE_DIRS})

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

add_definitions(-std=c++11)

############
# BINARIES #
############
cs_add_executable(rosppm
        src/rosppm_node.cpp src/rosppm.cpp
        )
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})