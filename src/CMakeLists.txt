cmake_minimum_required (VERSION 3.7)

project(DSV)

set(
	SRC_FILES
	"Core/VulkanApplication.cpp"
	"Core/VulkanHandler.cpp"
)

set(EXTRA_DEPENDENCIES "-lvulkan")

include_directories("include/Core")

add_library(${PROJECT_NAME} ${SRC_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} ${EXTRA_DEPENDENCIES})
