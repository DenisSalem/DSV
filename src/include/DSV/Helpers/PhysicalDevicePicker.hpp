#include <algorithm>

#ifndef DSV_PHYSICAL_DEVICE_PICKER
#define DSV_PHYSICAL_DEVICE_PICKER

#include "DSV/Helpers.hpp"

#define DSV_MSG_REQUIRED_QUEUE_FAMILY_UNSUPPORTED "Required queue family unsupported!"
#define DSV_MSG_THERE_IS_NO_MORE_DEVICE_AVAILABLE "There is no more device available!"

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
		};

		class PhysicalDevicePickerInterface {
		  	public:
				PhysicalDevicePickerInterface(std::vector<VkPhysicalDevice> physicalDevices);
				uint32_t PickMostRated();
				virtual void SetScore() = 0;

			protected:
				std::vector<PhysicalDeviceCandidate> m_candidates;
				

		};

		class PhysicalDeviceDefaultPicker : public PhysicalDevicePickerInterface {
			public: 
				PhysicalDeviceDefaultPicker(std::vector<VkPhysicalDevice> physicalDevices);
				void SetScore();
		};
	}
}

#endif
