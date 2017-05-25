#include "DSV/Core/RessourceManager.hpp"

#ifndef DSV_INSTANCE
#define DSV_INSTANCE

namespace DSV {
	namespace Core {
		class Instance : public RessourceManager<VkInstance, VkInstanceCreateInfo> {
			public:
				Instance(const char * applicationName, uint32_t applicationVersion, const char * engineName, uint32_t engineVersion);
				Instance(const char * applicationName, uint32_t applicationVersion, const char * engineName, uint32_t engineVersion, VkAllocationCallbacks * pAllocationCallbacks);
			
			protected:
				VkApplicationInfo m_applicationInfo;
		};
	}
}

#endif
