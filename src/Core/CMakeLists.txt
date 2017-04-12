cmake_minimum_required(VERSION 3.7)
project(VulkanApplication)
add_library(VulkanApplication OBJECT VulkanApplication.cpp) 
set_property(TARGET VulkanApplication PROPERTY CXX_STANDARD 11)
