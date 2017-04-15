#include "DSV/VulkanApplication.hpp"

namespace DSV {

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

	void PrintInstanceLayers(std::vector<VkLayerProperties> pProperties) {
		std::cout << DSV_MSG_AVAILABLE_INSTANCE_LAYERS;
		for (const auto& layerProperties : pProperties) {
			std::cout << "\t" << layerProperties.layerName << "\n";
		}
	}

	void PrintInstanceExtensions(std::vector<VkExtensionProperties> pProperties) {
		std::cout << DSV_MSG_AVAILABLE_INSTANCE_EXTENSIONS;
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

	VulkanApplication::VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) {
	  	m_pInstance = nullptr;
		m_pCallback = nullptr;
		m_instanceCreateInfo = {};
		m_callbackCreateInfo = {};
		m_appInfo = {};
		
		m_appInfo.pApplicationName = applicationName;
		m_appInfo.applicationVersion = applicationVersion;
		m_appInfo.pEngineName = engineName;
		m_appInfo.engineVersion = engineVersion;

	}

	VulkanApplication::~VulkanApplication() {
		auto DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(m_pInstance, "vkDestroyDebugReportCallbackEXT");
		if (DestroyDebugReportCallback != nullptr && m_pCallback != nullptr) {
			DestroyDebugReportCallback(m_pInstance, m_pCallback, nullptr);
		}
		vkDestroyInstance(m_pInstance, nullptr);
	}

	void VulkanApplication::SetupCallback(VkDebugReportFlagsEXT flags, PFN_vkDebugReportCallbackEXT debugCallback) {
		m_callbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		m_callbackCreateInfo.flags = flags;
		m_callbackCreateInfo.pfnCallback = debugCallback;
		auto CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(m_pInstance, "vkCreateDebugReportCallbackEXT");
		if (CreateDebugReportCallback != nullptr) {
			auto result = CreateDebugReportCallback(m_pInstance, &m_callbackCreateInfo, nullptr, &m_pCallback);
			if (result != VK_SUCCESS) {
				throw Exception(result, DSV_MSG_FAILED_TO_CREATE_CALLBACK);
			}
		}
		else {
			throw Exception(VK_ERROR_EXTENSION_NOT_PRESENT, DSV_MSG_FAILED_TO_CREATE_CALLBACK);
		}
	}

	void VulkanApplication::InitVulkan(std::vector<const char *> requiredExtensions, std::vector<const char *> requiredLayers) {
		m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		m_appInfo.pNext = nullptr;
		m_appInfo.apiVersion = VK_API_VERSION_1_0;

		m_instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		m_instanceCreateInfo.pNext = nullptr;
		m_instanceCreateInfo.flags = 0;
		m_instanceCreateInfo.pApplicationInfo = &m_appInfo;
		m_instanceCreateInfo.enabledLayerCount = requiredLayers.size();
		m_instanceCreateInfo.ppEnabledLayerNames = requiredLayers.data();
		m_instanceCreateInfo.enabledExtensionCount = requiredExtensions.size();
		m_instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

		PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance) vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
		VkResult result = vkCreateInstance(&m_instanceCreateInfo, nullptr, &m_pInstance);
		if (result != VK_SUCCESS) {
    			throw Exception(result, DSV_MSG_FAILED_TO_CREATE_INSTANCE, m_appInfo.pApplicationName);
		}
	}
}
