#include "DSV/Core/Instance.hpp"

namespace DSV {
	namespace Core {
	  	
		Instance::Instance(
			const char * applicationName,
			uint32_t applicationVersion,
			const char * engineName,
			uint32_t engineVersion,
			uint32_t apiVersion
		) : Instance(applicationName, applicationVersion, engineName, engineVersion, apiVersion, nullptr, std::vector<const char *>(), std::vector<const char *>()) {};
		
		Instance::Instance(
			const char * applicationName,
			uint32_t applicationVersion,
			const char * engineName,
			uint32_t engineVersion,
			uint32_t apiVersion,
			std::vector<const char *> requiredInstanceExtensions, 
			std::vector<const char *> requiredInstanceLayers
		) : Instance(applicationName, applicationVersion, engineName, engineVersion, apiVersion, nullptr, requiredInstanceExtensions, requiredInstanceLayers) {};
		
		Instance::Instance(
			const char * applicationName,
			uint32_t applicationVersion,
			const char * engineName,
			uint32_t engineVersion,
			uint32_t apiVersion,
			VkAllocationCallbacks * pAllocationCallbacks
		) : Instance(applicationName, applicationVersion, engineName, engineVersion, apiVersion, pAllocationCallbacks, std::vector<const char *>(), std::vector<const char *>()) {};

		Instance::Instance(
			const char * applicationName,
			uint32_t applicationVersion,
			const char * engineName,
			uint32_t engineVersion,
			uint32_t apiVersion,
			VkAllocationCallbacks * pAllocationCallbacks,
			std::vector<const char *> requiredInstanceExtensions, 
			std::vector<const char *> requiredInstanceLayers
		) : RessourceManager(vkCreateInstance, vkDestroyInstance) {
		  	m_msgFailedToCreate = DSV_MSG_FAILED_TO_CREATE_INSTANCE;
			m_physicalDevices = std::vector<VkPhysicalDevice>();

		  	m_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			m_applicationInfo.pApplicationName = applicationName;
			m_applicationInfo.applicationVersion = applicationVersion;
			m_applicationInfo.pEngineName = engineName;
			m_applicationInfo.engineVersion = engineVersion;
			m_applicationInfo.apiVersion = apiVersion;

			m_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			m_createInfo.pApplicationInfo = &this->m_applicationInfo;
			m_createInfo.enabledExtensionCount = requiredInstanceExtensions.size();
			m_createInfo.ppEnabledExtensionNames = requiredInstanceExtensions.data();
			m_createInfo.enabledLayerCount = requiredInstanceLayers.size();
			m_createInfo.ppEnabledLayerNames = requiredInstanceLayers.data();

			Create();
			SetPhysicalDevices();

			
		}

		std::string Instance::GetApplicationName() {
			return std::string(m_applicationInfo.pApplicationName);
		}

		std::string Instance::GetEngineName() {
			return std::string(m_applicationInfo.pEngineName);
		}

		uint32_t Instance::GetApplicationVersion() {
			return m_applicationInfo.applicationVersion;
		}

		uint32_t Instance::GetEngineVersion() {
			return m_applicationInfo.engineVersion;
		}

		std::vector<VkPhysicalDevice> Instance::GetPhysicalDevices() {
			return m_physicalDevices;
		}

		uint32_t Instance::PickPhysicalDevice(std::function<uint32_t(std::vector<VkPhysicalDevice>)> picker) {
			if (m_physicalDevices.size() == 1) {
				return 0;
			}
			else {
				return picker(GetPhysicalDevices());
			}
		}

		VkPhysicalDevice Instance::GetPhysicalDevice(uint32_t index) {
			return m_physicalDevices.at(index);
		}

		void Instance::SetPhysicalDevices() {
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(m_pHandler, &deviceCount, nullptr);
			m_physicalDevices.resize(deviceCount);
			vkEnumeratePhysicalDevices(m_pHandler, &deviceCount, m_physicalDevices.data());
		}
	}
}


