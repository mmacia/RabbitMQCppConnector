cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

project(rabbitmqcppconn_examples CXX)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -std=c++0x -g")
set(CMAKE_CXX_FLAGS "-std=c++0x -O2 -s")

include_directories("${rabbitmqcppconn_SOURCE_DIR}/ideup/amqp" )
link_directories("${rabbitmqcppconn_BINARY_DIR}" )

# Include RabbitMQ C headers
list(APPEND LIB_INCLUDE_DIR "${CMAKE_BINARY_DIR}/lib/rabbitmq-c")
list(APPEND LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/rabbitmq-c")
include_directories(${LIB_INCLUDE_DIR})

add_executable(basic_consumer "${CMAKE_CURRENT_SOURCE_DIR}/basic_consumer.cpp")
target_link_libraries(basic_consumer rabbitmqcppconn)

add_executable(basic_publisher "${CMAKE_CURRENT_SOURCE_DIR}/basic_publisher.cpp")
target_link_libraries(basic_publisher rabbitmqcppconn)
