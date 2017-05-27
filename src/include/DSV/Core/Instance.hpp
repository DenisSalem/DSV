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
					uint32_t engineVersion,
					uint32_t apiVersion
				);
				
				Instance(
					const char * applicationName,
					uint32_t applicationVersion, 
					const char * engineName, 
					uint32_t engineVersion, 
					uint32_t apiVersion,
					std::vector<const char *> requiredInstanceExtensions, 
					std::vector<const char *> requiredInstanceLayers
				);

				Instance(
					const char * applicationName,
					uint32_t applicationVersion,
					const char * engineName,
					uint32_t engineVersion,
					uint32_t apiVersion,
					VkAllocationCallbacks * pAllocationCallbacks
				);
				
				Instance(
					const char * applicationName,
					uint32_t applicationVersion,
					const char * engineName,
					uint32_t engineVersion,
					uint32_t apiVersion,
					VkAllocationCallbacks * pAllocationCallbacks,
					std::vector<const char *> requiredInstanceExtensions, 
					std::vector<const char *> requiredInstanceLayers
				);

				std::string GetApplicationName();
				std::string GetEngineName();
				uint32_t GetApplicationVersion();
				uint32_t GetEngineVersion();
				std::vector<VkPhysicalDevice> GetPhysicalDevices();
				uint32_t PickPhysicalDevice(std::function<uint32_t(std::vector<VkPhysicalDevice>)> picker);
				VkPhysicalDevice GetPhysicalDevice(uint32_t index);
			
			protected:
				void SetPhysicalDevices();
				VkApplicationInfo m_applicationInfo;
				std::vector<VkPhysicalDevice> m_physicalDevices;
		};
	}
}

#endif
