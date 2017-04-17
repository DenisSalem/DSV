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

	VulkanApplication::VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) {
	  	m_pInstance = nullptr;
	  	m_pDevice = nullptr;
		m_pCallback = nullptr;
		m_physicalDevices = std::vector<VkPhysicalDevice>(0);
		m_queueCreateInfos = std::vector<VkDeviceQueueCreateInfo>(0);
		m_queuePriorities = std::vector<std::vector<float>>(0);
		m_instanceCreateInfo = {};
		m_deviceCreateInfo = {};
		m_callbackCreateInfo = {};
	  	m_deviceFeatures = {};
		m_appInfo = {};
		
		m_appInfo.pApplicationName = applicationName;
		m_appInfo.applicationVersion = applicationVersion;
		m_appInfo.pEngineName = engineName;
		m_appInfo.engineVersion = engineVersion;

	}

	VulkanApplication::~VulkanApplication() {
	  	if (m_pDevice != nullptr) {
			vkDestroyDevice(m_pDevice, nullptr);
		}

		auto DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(m_pInstance, "vkDestroyDebugReportCallbackEXT");
		if (DestroyDebugReportCallback != nullptr && m_pCallback != nullptr) {
			DestroyDebugReportCallback(m_pInstance, m_pCallback, nullptr);
		}

		vkDestroyInstance(m_pInstance, nullptr);
	}

	void VulkanApplication::PrintPhysicalDevices() {
	  	std::cout << DSV_MSG_AVAILABLE_INSTANCE_PHYSICAL_DEVICES;
		for (const auto& device : m_physicalDevices) {
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			std::cout << "\t" << deviceProperties.deviceName << "\n";
		}
	}

	std::vector<VkPhysicalDevice> VulkanApplication::GetPhysicalDevices() {
		return m_physicalDevices;
	}

	std::vector<VkQueueFamilyProperties> VulkanApplication::GetQueueFamilies(int physicalDeviceIndex) {
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices.at(physicalDeviceIndex), &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices.at(physicalDeviceIndex), &queueFamilyCount, queueFamilies.data());
		return queueFamilies;
	}

	void VulkanApplication::AddQueueFamily(int32_t queueFamilyIndex, uint32_t const queueCount, std::vector<float> queuePriorities) {
		for (const auto& queueCreateInfo :  m_queueCreateInfos) {
			if (queueFamilyIndex == queueCreateInfo.queueFamilyIndex) {
				throw Exception(DSV_QUEUE_FAMILY_INDEX_DEFINED_TWICE, DSV_MSG_QUEUE_FAMILY_INDEX_DEFINED_TWICE);
			}
		}
		
		m_queuePriorities.push_back(queuePriorities);

		VkDeviceQueueCreateInfo queueCreateInfo = {};
	  	
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
		queueCreateInfo.queueCount = queueCount;
		queueCreateInfo.pQueuePriorities = m_queuePriorities.back().data();

		m_queueCreateInfos.push_back(queueCreateInfo);
	}

	std::vector<VkExtensionProperties> VulkanApplication::GetDeviceExtensions(int physicalDeviceIndex, const char * pLayerName) {
		uint32_t propertiesCount = 0;
		std::vector<VkExtensionProperties> pProperties;
		vkEnumerateDeviceExtensionProperties(m_physicalDevices.at(physicalDeviceIndex), pLayerName, &propertiesCount, nullptr);
		if (propertiesCount != 0) {
		  	pProperties.resize(propertiesCount);
			vkEnumerateDeviceExtensionProperties(m_physicalDevices.at(physicalDeviceIndex), pLayerName, &propertiesCount, pProperties.data());

		}
		return pProperties;
		
	}

	void VulkanApplication::CreateLogicalDevice(int physicalDeviceIndex) {
		CreateLogicalDevice(physicalDeviceIndex, std::vector<const char*>(0));
	}

	void VulkanApplication::CreateLogicalDevice(int physicalDeviceIndex, const std::vector<const char*> requiredDeviceExtensions) {
		m_deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		m_deviceCreateInfo.pEnabledFeatures = &m_deviceFeatures;
		m_deviceCreateInfo.pQueueCreateInfos = m_queueCreateInfos.data();
		m_deviceCreateInfo.queueCreateInfoCount = m_queueCreateInfos.size();
		m_deviceCreateInfo.enabledLayerCount = 0;
		m_deviceCreateInfo.ppEnabledLayerNames = nullptr;
		m_deviceCreateInfo.enabledExtensionCount = requiredDeviceExtensions.size();
		m_deviceCreateInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();

		auto result = vkCreateDevice(m_physicalDevices.at(physicalDeviceIndex), &m_deviceCreateInfo, nullptr, &m_pDevice);

		if (result != VK_SUCCESS) {
			throw Exception(result, DSV_MSG_FAILED_TO_CREATE_LOGICAL_DEVICE);
		}
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

	void VulkanApplication::InitVulkan() {
		InitVulkan(std::vector<const char *>(0), std::vector<const char *>(0));
	}

	void VulkanApplication::InitVulkan(std::vector<const char *> requiredExtensions, std::vector<const char *> requiredLayers) {
	  	m_requiredExtensions = requiredExtensions;
	  	m_requiredLayers = requiredLayers;
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

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_pInstance, &deviceCount, nullptr);
		if (deviceCount == 0) {
			throw Exception(DSV_NO_PHYSICAL_DEVICES, DSV_MSG_NO_PHYSICAL_DEVICES);
		}
		m_physicalDevices.resize(deviceCount);
		vkEnumeratePhysicalDevices(m_pInstance, &deviceCount, m_physicalDevices.data());
	}
}
