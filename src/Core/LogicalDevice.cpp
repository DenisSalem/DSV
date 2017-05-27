#include "DSV/Core/LogicalDevice.hpp"

namespace DSV {
	namespace Core {
		LogicalDevice::LogicalDevice(VkPhysicalDevice physicalDevice, std::vector<VkDeviceQueueCreateInfo> queuesCreateInfo, VkPhysicalDeviceFeatures deviceFeatures) : RessourceManager(vkCreateDevice, vkDestroyDevice) {
			m_queuesCreateInfo = queuesCreateInfo;
			m_deviceFeatures = deviceFeatures;
			
			m_createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			m_createInfo.pQueueCreateInfos = m_queuesCreateInfo.data();
		      	m_createInfo.queueCreateInfoCount = m_queuesCreateInfo.size();
			m_createInfo.pEnabledFeatures = &m_deviceFeatures;
			
			m_pPhysicalDevice = physicalDevice;
			//Create();
		}

	}
}
