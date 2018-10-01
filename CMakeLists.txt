cmake_minimum_required(VERSION 2.8.3)
project(rosppm)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   ppm_io.msg
 )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )

###################################
## catkin specific configuration ##
###################################

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES rosppm
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_executable(rosppm_node src/rosppm_node.cpp include/rosppm/rosppm.h src/rosppm.cpp)
target_link_libraries(rosppm_node ${catkin_LIBRARIES})
add_dependencies(rosppm_node rosppm_generate_messages_cpp)