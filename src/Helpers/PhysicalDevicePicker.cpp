#include "DSV/Helpers/PhysicalDevicePicker.hpp"

namespace DSV {
	namespace Helpers {
		PhysicalDevicePicker::PhysicalDevicePicker(std::vector<VkPhysicalDevice> physicalDevices) {
		  	m_candidates = std::vector<PhysicalDeviceCandidate>();
			for (uint32_t index = 0; index < physicalDevices.size(); index++) {
				PhysicalDeviceCandidate candidate = {};
				candidate.handler = physicalDevices.at(index);
				vkGetPhysicalDeviceProperties(physicalDevices.at(index), &candidate.properties);
				vkGetPhysicalDeviceFeatures(physicalDevices.at(index), &candidate.features);
				vkGetPhysicalDeviceMemoryProperties(physicalDevices.at(index), &candidate.memoryProperties);
				
			}
		}
	}
}
