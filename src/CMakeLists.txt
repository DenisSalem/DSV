cmake_minimum_required (VERSION 3.7)

project(DSV)

option(USE_CORE "Use Core DSV" ON)
option(USE_GLFW "Use GLFW" ON)

set(CORE_SRC_FILES "")
if (USE_CORE)
  set(CORE_SRC_FILE "Core/VulkanApplication.cpp")
endif(USE_CORE)

set(EXTRA_DEPENDENCIES "-lvulkan")

include_directories("include")

add_library(${PROJECT_NAME} ${CORE_SRC_FILE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} ${EXTRA_DEPENDENCIES})
