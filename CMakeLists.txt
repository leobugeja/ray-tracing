cmake_minimum_required(VERSION 3.16)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(ray_tracing main.cpp vec3.h color.h ray.h hittable.h sphere.h)