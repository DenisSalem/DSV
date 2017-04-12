#include "DSV/VulkanApplication.hpp"

namespace DSV {
	VulkanApplication::VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) {
	  	m_pInstance = nullptr;
		m_instanceCreateInfo = {};
		m_appInfo = {};
		
		m_appInfo.pApplicationName = applicationName;
		m_appInfo.applicationVersion = applicationVersion;
		m_appInfo.pEngineName = engineName;
		m_appInfo.engineVersion = engineVersion;

	}

	VulkanApplication::~VulkanApplication() {
		vkDestroyInstance(m_pInstance, nullptr);
	}

	void VulkanApplication::InitVulkan( std::vector<const char *> requiredExtensions ) {
		m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		m_appInfo.pNext = nullptr;
		m_appInfo.apiVersion = VK_API_VERSION_1_0;

		m_instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		m_instanceCreateInfo.pNext = nullptr;
		m_instanceCreateInfo.flags = 0;
		m_instanceCreateInfo.pApplicationInfo = &m_appInfo;

		PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance) vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
		if (vkCreateInstance(&m_instanceCreateInfo, nullptr, &m_pInstance) != VK_SUCCESS) {
    			throw std::runtime_error(DSV_MSG_FAILED_TO_CREATE_INSTANCE);
		}
	}
}
