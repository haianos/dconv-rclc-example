cmake_minimum_required(VERSION 3.5)

project(dconv_rclc_example)

find_package(ament_cmake_ros REQUIRED)
# find_package(rcl REQUIRED)
find_package(rclc REQUIRED)
# find_package(rosidl_generator_c REQUIRED)
# find_package(rosidl_typesupport_c REQUIRED)
find_package(geometry_msgs REQUIRED)

# Hardcoded path here!
# find_package(lua5.2 REQUIRED)
INCLUDE_DIRECTORIES(/usr/include/lua5.2/ )
LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu/)


ament_export_include_directories(include)
include_directories(include)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

add_library(ros-c99
  SHARED
  src/ros-c99.c
)
add_executable(publishme src/publishme.c)
add_executable(subme src/subme.c)

ament_target_dependencies(ros-c99
  geometry_msgs
  rclc
)

ament_target_dependencies(publishme
  geometry_msgs
  rclc
)

ament_target_dependencies(subme
  geometry_msgs
  rclc
)

ament_export_dependencies(
  rclc
  geometry_msgs
)

#ament_export_include_directories(include)
#ament_export_libraries(${PROJECT_NAME})

ament_package()

# target_link_libraries(publishme rclc)
target_link_libraries(subme lua5.2)

# install(
#   DIRECTORY include/
#   DESTINATION include
# )
install(
  TARGETS subme publishme ros-c99
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
