cmake_minimum_required(VERSION 3.5)
project(motion_planning)
SET(ENV{PYTHONPATH} "/opt/ros/foxy/lib/python3.8/site-packages/")

SET(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} home/beyza/projects/install;/opt/ros/foxy")
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

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)

add_executable(sine_path  src/sine_path.cpp)
ament_target_dependencies(sine_path rclcpp std_msgs geometry_msgs)

add_executable(points src/points.cpp)
ament_target_dependencies(points rclcpp std_msgs geometry_msgs visualization_msgs nav_msgs)

add_executable(car  src/car.cpp)
ament_target_dependencies(car rclcpp std_msgs geometry_msgs visualization_msgs nav_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  ament_lint_auto_find_test_dependencies()
endif()



install(TARGETS

        sine_path
        points
        car

        DESTINATION lib/${PROJECT_NAME}
        )

install(DIRECTORY

        launch
        DESTINATION share/${PROJECT_NAME}
        )
ament_package()
