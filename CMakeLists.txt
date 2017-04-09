cmake_minimum_required (VERSION 3.7)

project(DSV)

option(USE_CORE "Use Core DSV" ON)

set(CORE_SRC_FILES "")

if (USE_CORE)
  set(CORE_SRC_FILE "core/VulkanApplication.cpp")
endif(USE_CORE)

set(DEPENDENCEIS "-lvulkan")

add_library(${PROJECT_NAME} ${CORE_SRC_FILE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
