cmake_minimum_required (VERSION 3.7)

project(DSV)

set(
	SRC_FILES
	"Helpers/Helpers.cpp"
	"Core/RessourceManager.cpp"
	"Core/Instance.cpp"
	"Core/Callback.cpp"
	"Core/LogicalDevice.cpp"
	"Helpers/PhysicalDevicePicker.cpp"
	"Helpers/QueueFamilyManager.cpp"
)

set(
	EXTRA_DEPENDENCIES
	"-lvulkan"
)

include_directories("include")

add_library(${PROJECT_NAME} ${SRC_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} ${EXTRA_DEPENDENCIES})
