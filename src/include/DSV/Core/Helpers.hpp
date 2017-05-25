#ifndef DSV_HELPERS
#define DSV_HELPERS

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

#include "DSV/Core.hpp"

#define DSV_MSG_REQUIRED_LAYERS_UNAVAILABLE "DSV: One ore more required layers are unavailable!"
#define DSV_MSG_REQUIRED_EXTENSIONS_UNAVAILABLE "DSV: On ore more required extensions are unavailable!"

namespace DSV {
	namespace Core {

		typedef enum HelpersErrorCode {
			REQUIRED_LAYERS_UNAVAILABLE,
			REQUIRED_EXTENSIONS_UNAVAILABLE
		} HelpersErrorCode;

		std::vector<VkLayerProperties> GetInstanceLayers();
		std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName);
	
		void PrintLayers(const char * header, std::vector<VkLayerProperties> pProperties);
		void PrintExtensions(const char * header, std::vector<VkExtensionProperties> pProperties);
	
		void AssertInstanceLayersAreAvailable(std::vector<const char *> required);
		void AssertInstanceExtensionsAreAvailable(std::vector<const char *> required);

		struct Exception{
			Exception(int code, const char * msg);
			Exception(int code, const char * msg, const char * context);

			int code;
		
			std::string msg;
			std::string context;
		};
	}
}

#endif
