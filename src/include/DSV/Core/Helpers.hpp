#ifndef DSV_HELPERS
#define DSV_HELPERS

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

#include "DSV/Core.hpp"

#define DSV_MSG_REQUIRED_LAYERS_UNAVAILABLE "DSV: One ore more required layers are unavailable!"
#define DSV_MSG_REQUIRED_EXTENSIONS_UNAVAILABLE "DSV: On ore more required extensions are unavailable!"


#define DSV_CALLBACK_REPORT_ALL VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT

namespace DSV {
	namespace Core {

		typedef enum HelpersErrorCode {
			REQUIRED_LAYERS_UNAVAILABLE,
			REQUIRED_EXTENSIONS_UNAVAILABLE
		} HelpersErrorCode;
		
		VKAPI_ATTR VkBool32 VKAPI_CALL DefaultDebugCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* msg,
			void* userData
		);

		std::vector<VkLayerProperties> GetInstanceLayers();
		std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName);
	
		std::string GetNameFromProperties(VkLayerProperties properties);
		std::string GetNameFromProperties(VkExtensionProperties properties);
		std::string GetNameFromProperties(VkPhysicalDeviceProperties properties);

		template<typename Properties> void PrintNamesFrom(std::vector<Properties> vProperties, const char * header);
	
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
