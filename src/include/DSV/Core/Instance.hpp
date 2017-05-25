#include "DSV/Core/RessourceManager.hpp"

#ifndef DSV_INSTANCE
#define DSV_INSTANCE

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
			
			protected:
				VkApplicationInfo m_applicationInfo;
		};
	}
}

#endif
