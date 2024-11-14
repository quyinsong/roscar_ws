cmake_minimum_required(VERSION 3.0.2)
project(car_model)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  states.msg
  controls.msg
  test.msg
)


## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES car_model
 CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ./include/car_model/
)


add_executable(test_pub ./src/test_pub.cpp)
target_link_libraries(test_pub ${catkin_LIBRARIES})

add_executable(test_car_model ./src/test_car_model.cpp ./src/car_model.cpp)
target_link_libraries(test_car_model ${catkin_LIBRARIES})
