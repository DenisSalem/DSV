#include <algorithm>
#include "DSV/Helpers.hpp"

#ifndef DSV_PHYSICAL_DEVICE_PICKER
#define DSV_PHYSICAL_DEVICE_PICKER

#define DSV_MSG_REQUIRED_QUEUE_FAMILY_UNSUPPORTED "Required queue family unsupported!"

#define FLAGS_MATCH(required, current) ( (current & required) == required)

namespace DSV {
	namespace Helpers {
		struct PhysicalDeviceCandidate {
			VkPhysicalDevice handler;
			VkPhysicalDeviceProperties properties;
			VkPhysicalDeviceFeatures features;
			VkPhysicalDeviceMemoryProperties memoryProperties;
			std::vector<VkQueueFamilyProperties> queueFamilyProperties;
			
			uint32_t score;
			uint32_t index;
			std::vector<std::string> featuresName;
		};

		class PhysicalDevicePicker {
		  	public:
				PhysicalDevicePicker(std::vector<VkPhysicalDevice> physicalDevices);

			protected:
				std::vector<PhysicalDeviceCandidate> m_candidates;
				

		};
	}
}

#endif
