#include "DSV/Core/RessourceManager.hpp"

#ifndef DSV_CALLBACK
#define DSV_CALLBACK

#define DSV_MSG_FAILED_TO_CREATE_CALLBACK "DSV: Failed to create callback!"

namespace DSV {
	namespace Core {
		class Callback : public RessourceManager<VkDebugReportCallbackEXT, VkDebugReportCallbackCreateInfoEXT> {
			public:
				Callback(VkInstance pInstance, VkDebugReportFlagsEXT flags, PFN_vkDebugReportCallbackEXT pfnCallback);
				Callback(VkInstance pInstance, VkDebugReportFlagsEXT flags, PFN_vkDebugReportCallbackEXT pfnCallback, VkAllocationCallbacks * pAllocationCallbacks);
		};
	}
}
#endif

