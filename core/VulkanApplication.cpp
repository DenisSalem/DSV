#include "VulkanApplication.hpp"

namespace DSV {

	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else
		const bool enableValidationLayers = true;
		const std::vector<const char*> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};
	#endif

	std::vector<VkExtensionProperties> GetVkExtensionsProperties() {
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		return extensions;
	}

	bool CheckRequiredValidationLayerSupport() {
		uint32_t layerCount = 0;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		std::cout << layerCount << "\n";
		std::vector<VkLayerProperties> availableLayers(layerCount);
    		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
		for (const char* layerName : validationLayers) {
			bool layerFound = false;
			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
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

	VulkanApplication::VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) {
		m_appInfo.pApplicationName = applicationName;
		m_appInfo.applicationVersion = applicationVersion;
		m_appInfo.pEngineName = engineName;
		m_appInfo.engineVersion = engineVersion;
	}

	VulkanApplication::~VulkanApplication() {
		vkDestroyInstance(m_pInstance, NULL);
	}

	void VulkanApplication::SetupDebugCallBack() {
    		if (!enableValidationLayers)
			return;

		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanApplication::debugCallback(VkDebugReportFlagsEXT flags,VkDebugReportObjectTypeEXT objType,uint64_t obj,size_t location,int32_t code,const char* layerPrefix,const char* msg,void* userData) {
    			std::cerr << "DSV: Validation layer: " << msg << std::endl;
    			return VK_FALSE;
		}


	void VulkanApplication::initVulkan( std::vector<const char *> requiredExtensions) {
		m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		m_appInfo.pNext = NULL;
		m_appInfo.apiVersion = VK_API_VERSION_1_0;

		m_instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		m_instanceCreateInfo.pNext = NULL;
		m_instanceCreateInfo.flags = 0;
		m_instanceCreateInfo.pApplicationInfo = &m_appInfo;
		
		if (enableValidationLayers && !CheckRequiredValidationLayerSupport()) {
        		throw std::runtime_error(DSV_MSG_VALIDATION_LAYER_REQUESTED);
    		}
	
		m_instanceCreateInfo.enabledLayerCount = validationLayers.size();
		m_instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
		
		m_instanceCreateInfo.enabledExtensionCount = requiredExtensions.size();
		m_instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

		m_pInstance = NULL;
		if (vkCreateInstance(&m_instanceCreateInfo, nullptr, &m_pInstance) != VK_SUCCESS) {
    			throw std::runtime_error(DSV_MSG_FAILED_TO_CREATE_INSTANCE);
		}
	}
}
