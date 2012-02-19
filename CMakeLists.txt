cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
project(gnf-native CXX C)

# set paths to all Find* modules and tasks
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/rabbitmq-c/cmake" ${CMAKE_MODULE_PATH})

include(CTags)

# variables to build RabbitMQ extensions
set(RABBITMQ_CODEGEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/rabbitmq-codegen")

# add projects and dependencies to build process
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/rabbitmq-c)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
