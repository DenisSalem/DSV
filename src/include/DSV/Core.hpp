#include <vulkan/vulkan.h>

#define _TEST_ 1

#ifndef DSV_CORE
#define DSV_CORE

#include "DSV/Helpers.hpp"
#include "DSV/Core/Instance.hpp"
#include "DSV/Core/Callback.hpp"
#include "DSV/Core/LogicalDevice.hpp"

#define DSV_TRACE { std::cerr << "DSV_TRACE: "<< __FILE__ << ", " << __LINE__ << "\n"; } 

#endif
