cmake_minimum_required(VERSION 3.8)
project(topic_demo_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(topic_demo_interfaces REQUIRED)

add_executable(custom_talker src/custom_talker.cpp)
ament_target_dependencies(custom_talker rclcpp topic_demo_interfaces)

add_executable(custom_listener src/custom_listener.cpp)
ament_target_dependencies(custom_listener rclcpp topic_demo_interfaces)

install(TARGETS
  custom_talker
  custom_listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
