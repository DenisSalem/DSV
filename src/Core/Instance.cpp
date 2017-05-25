#include "DSV/Core/Instance.hpp"

namespace DSV {
	namespace Core {
	  	
		Instance::Instance(const char * applicationName, uint32_t applicationVersion, const char * engineName, uint32_t engineVersion) : Instance(applicationName, applicationVersion, engineName, engineVersion, nullptr) {};
		Instance::Instance(const char * applicationName, uint32_t applicationVersion, const char * engineName, uint32_t engineVersion, 	VkAllocationCallbacks * pAllocationCallbacks) : RessourceManager(vkCreateInstance, vkDestroyInstance) {

		  	m_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			m_applicationInfo.pApplicationName = applicationName;
			m_applicationInfo.applicationVersion = applicationVersion;
			m_applicationInfo.pEngineName = engineName;
			m_applicationInfo.engineVersion = engineVersion;
			m_applicationInfo.apiVersion = VK_API_VERSION_1_0;


			m_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			m_createInfo.pApplicationInfo = &this->m_applicationInfo;

			Create();
		}
	}
}


