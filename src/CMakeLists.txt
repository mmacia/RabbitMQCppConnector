cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

project(rabbitmqcppconn CXX)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -std=c++0x -g")
set(CMAKE_CXX_FLAGS "-std=c++0x")


file(GLOB SOURCES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/ideup/amqp/*.cpp")
file(GLOB INCLUDES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/ideup/amqp/*.hpp")

# Include RabbitMQ C headers
include_directories(${rabbitmq-c_SOURCE_DIR} "${CMAKE_BINARY_DIR}/lib/rabbitmq-c")
link_directories(${rabbitmq-c_BINARY_DIR})

add_library(rabbitmqcppconn ${SOURCES_CPP} ${INCLUDES_CPP})
target_link_libraries(rabbitmqcppconn rabbitmq)
