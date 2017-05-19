#ifndef DSV_VULKAN_HELPERS
#define DSV_VULKAN_HELPERS

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

#include "DSV/Core.hpp"

namespace DSV {
	namespace Core {
		std::vector<VkLayerProperties> GetInstanceLayers();
		std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName);
	
		void PrintLayers(const char * header, std::vector<VkLayerProperties> pProperties);
		void PrintExtensions(const char * header, std::vector<VkExtensionProperties> pProperties);
	
		bool IsInstanceLayersAvailable(std::vector<const char *> required);
		bool IsInstanceExtensionsAvailable(std::vector<const char *> required);

		struct Exception {
			Exception(int code, const char * msg);
			Exception(int code, const char * msg, const char * context);

			int code;
		
			std::string msg;
			std::string context;
		};
	}
}

#endif
