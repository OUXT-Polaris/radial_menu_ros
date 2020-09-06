cmake_minimum_required(VERSION 3.5)
project(radial_menu_backend)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(radial_menu_model REQUIRED)
find_package(radial_menu_msgs REQUIRED)

include_directories(
  include
)

## Declare a C++ library
add_library(
  radial_menu_backend_plugins
  src/radial_menu_backend_plugins.cpp
)
ament_target_dependencies(radial_menu_backend_plugins
  rclcpp sensor_msgs radial_menu_model radial_menu_msgs)

ament_export_include_directories(include)
ament_package()