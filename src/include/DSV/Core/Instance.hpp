#include "DSV/Core/RessourceManager.hpp"

#ifndef DSV_INSTANCE
#define DSV_INSTANCE

#define DSV_MSG_FAILED_TO_CREATE_INSTANCE "DSV: Failed to create instance!"

namespace DSV {
	namespace Core {
		class Instance : public RessourceManager<VkInstance, VkInstanceCreateInfo> {
			public:
				Instance(
					const char * applicationName,
					uint32_t applicationVersion,
					const char * engineName,
					uint32_t engineVersion
				);
				
				Instance(
					const char * applicationName,
					uint32_t applicationVersion, 
					const char * engineName, 
					uint32_t engineVersion, 
					std::vector<const char *> requiredInstanceExtensions, 
					std::vector<const char *> requiredInstanceLayers
				);

				Instance(
					const char * applicationName,
					uint32_t applicationVersion,
					const char * engineName,
					uint32_t engineVersion,
					VkAllocationCallbacks * pAllocationCallbacks
				);
				
				Instance(
					const char * applicationName,
					uint32_t applicationVersion,
					const char * engineName,
					uint32_t engineVersion,
					VkAllocationCallbacks * pAllocationCallbacks,
					std::vector<const char *> requiredInstanceExtensions, 
					std::vector<const char *> requiredInstanceLayers
				);

				std::string GetApplicationName();
				std::string GetEngineName();
				uint32_t GetApplicationVersion();
				uint32_t GetEngineVersion();
				std::vector<VkPhysicalDevice> GetPhysicalDevices();
				std::vector<VkPhysicalDeviceProperties> GetPhysicalDevicesProperties();
				uint32_t PickPhysicalDevice(std::function<uint32_t(std::vector<VkPhysicalDeviceProperties>)> picker);
				VkPhysicalDevice GetPhysicalDevice(uint32_t index);
			
			protected:
				void SetPhysicalDevices();
				VkApplicationInfo m_applicationInfo;
				std::vector<VkPhysicalDevice> m_physicalDevices;
		};
	}
}

#endif
