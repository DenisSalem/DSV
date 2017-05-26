#include "DSV/Core/RessourceManager.hpp"

#ifndef DSV_LOGICAL_DEVICE
#define DSV_LOGICAL_DEVICE

namespace DSV {
	namespace Core {
		class LogicalDevice : public RessourceManager<VkDevice, VkDeviceCreateInfo> {
			public:
				LogicalDevice(VkPhysicalDevice physicalDevice, std::vector<VkDeviceQueueCreateInfo> queuesCreateInfo, VkPhysicalDeviceFeatures deviceFeatures);

			protected:
				std::vector<VkDeviceQueueCreateInfo> m_queuesCreateInfo;
				VkPhysicalDeviceFeatures m_deviceFeatures;
		};
	}
}

#endif
