cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

project(rabbitmqcppconn_examples CXX)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -std=c++0x -g")
set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories("${rabbitmqcppconn_SOURCE_DIR}/ideup/amqp" )
link_directories("${rabbitmqcppconn_BINARY_DIR}" )

file(GLOB SOURCES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Include RabbitMQ C headers
list(APPEND LIB_INCLUDE_DIR "${CMAKE_BINARY_DIR}/lib/rabbitmq-c")
list(APPEND LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/rabbitmq-c")
include_directories(${LIB_INCLUDE_DIR})

add_executable(basic_consumer ${SOURCES_CPP})
target_link_libraries(basic_consumer rabbitmqcppconn)
