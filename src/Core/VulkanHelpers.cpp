#include "DSV/Core/VulkanHelpers.hpp"

namespace DSV {
	namespace Core {
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

		void PrintLayers(const char * header, std::vector<VkLayerProperties> pProperties) {
			std::cout << header;
			for (const auto& layerProperties : pProperties) {
				std::cout << "\t" << layerProperties.layerName << "\n";
			}
		}

		void PrintExtensions(const char * header, std::vector<VkExtensionProperties> pProperties) {
			std::cout << header;
			for (const auto& layerProperties : pProperties) {
				std::cout << "\t" << layerProperties.extensionName << "\n";
			}
		}

		bool IsInstanceLayersAvailable(std::vector<const char *> required) {
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
					return false;
				}
			}
			return true;
		}

		bool IsInstanceExtensionsAvailable(std::vector<const char *> required) {
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
					return false;
				}
			}
			return true;
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
