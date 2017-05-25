#include "DSV/Core/Helpers.hpp"

namespace DSV {
	namespace Core {
		VKAPI_ATTR VkBool32 VKAPI_CALL DefaultDebugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData) {
			std::cerr << "Validation layer: " << msg << std::endl;
			return VK_FALSE;
		}

		std::vector<VkLayerProperties> GetInstanceLayers() {
		  	uint32_t propertiesCount = 0;
			std::vector<VkLayerProperties> pProperties;
			vkEnumerateInstanceLayerProperties(&propertiesCount, nullptr);
			if (propertiesCount != 0) {
			  	pProperties.resize(propertiesCount);
				vkEnumerateInstanceLayerProperties(&propertiesCount, pProperties.data());
			}
			return pProperties;
		}

		std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName) {
	  		uint32_t propertiesCount = 0;
			std::vector<VkExtensionProperties> pProperties;
			vkEnumerateInstanceExtensionProperties(pLayerName, &propertiesCount, nullptr);
			if (propertiesCount != 0) {
			  	pProperties.resize(propertiesCount);
				vkEnumerateInstanceExtensionProperties(pLayerName, &propertiesCount, pProperties.data());

			}
			return pProperties;
		}


		const char * GetNameFromProperties(VkLayerProperties properties) {
			const char * name = properties.layerName;
			return name;
		}

		const char * GetNameFromProperties(VkExtensionProperties properties) {
			const char * name =properties.extensionName;
			return name;
		}

		const char * GetNameFromProperties(VkPhysicalDeviceProperties properties) {
			const char * name =properties.deviceName;
			return name;
		}

		template<typename Properties>
		void PrintNamesFrom(std::vector<Properties> vProperties, const char * header) {
			std::cout << header << "\n";
			for (Properties properties : vProperties) {
				std::cout << "\t" << GetNameFromProperties(properties) << "\n";
			}
		}

		template void PrintNamesFrom(std::vector<VkLayerProperties> vProperties, const char * header);
		template void PrintNamesFrom(std::vector<VkExtensionProperties> vProperties, const char * header);
		template void PrintNamesFrom(std::vector<VkPhysicalDeviceProperties> vProperties, const char * header);

		void AssertInstanceLayersAreAvailable(std::vector<const char *> required) {
			std::vector<VkLayerProperties> supported = GetInstanceLayers();
			for (const auto& r : required) {
				bool layerFound = false;
				for (const auto& s : supported) {
					if (strcmp(s.layerName, r) == 0) {
						layerFound = true;
						break;
					}
				}
				if (!layerFound) {
					throw Exception(REQUIRED_LAYERS_UNAVAILABLE, DSV_MSG_REQUIRED_LAYERS_UNAVAILABLE);
				}
			}
		}

		void AssertInstanceExtensionsAreAvailable(std::vector<const char *> required) {
			std::vector<VkExtensionProperties> supported = GetInstanceExtensions(nullptr);
			for (const auto& r : required) {
    				bool layerFound = false;
				for (const auto& s : supported) {
					if (strcmp(s.extensionName, r) == 0) {
						layerFound = true;
						break;
					}
				}
				if (!layerFound) {
					throw Exception(REQUIRED_EXTENSIONS_UNAVAILABLE,DSV_MSG_REQUIRED_EXTENSIONS_UNAVAILABLE);
				}
			}
		}
	
		Exception::Exception(int code, const char* msg) : Exception(code, msg, NULL) {}
	
		Exception::Exception(int code, const char * msg, const char * context) {
			this->code = code;
			this->msg = std::string(msg);
			if (context != NULL) {
				this->context = std::string(context);
				std::cerr << "DSV: " << this->context << "\n";
			}
			std::cerr << this->msg << "\n";
		}
	}
}
