# RabbitMQ C++ Connector

Status: **WIP, not usable yet.**

## What it is RabbitMQ C++ Connector?

**RabbitMQ C++ Connector** is a wrapper to use [RabbitMQ](http://www.rabbitmq.com) services in an object oriented
way.  This software uses the low level library `librabbitmq-c` to connect into
RabbitMQ servers and uses the Observer Pattern to ease integrate into your projects.

## How to compile

First, ensure that you have all needed software:

  `apt-get install build-essential cmake make`

Next, you need to update Git submodules:

  `git submodule init; git submodule update`

Lastly, proceed to build the sources:

  `mkdir build, cd build`
  
  `cmake ..; make`

