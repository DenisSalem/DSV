cmake_minimum_required (VERSION 3.7)

project(FirstGraphicVulkanApplication)

if (DEFINED DSV_PATH)
  add_subdirectory("${DSV_PATH}/src" DSV)
  include_directories("${DSV_PATH}/src/include")
else()
	message( FATAL_ERROR "DSV_PATH isn't defined. Call cmake with -DDSV_PATH:STRING=path/to/DSV")
endif()

set(DEPENDENCIES "-lvulkan -lglfw")

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} DSV ${DEPENDENCIES})
