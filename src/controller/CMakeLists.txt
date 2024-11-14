cmake_minimum_required(VERSION 3.0.2)
project(controller)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  car_model
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES controller
 CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ./include/controller/
)

add_executable(test_nmpc ./src/test_nmpc.cpp ./src/nmpc1.cpp)
target_link_libraries(test_nmpc ${catkin_LIBRARIES})
target_link_libraries(test_nmpc /usr/local/lib/libcasadi.so.3.7) 
