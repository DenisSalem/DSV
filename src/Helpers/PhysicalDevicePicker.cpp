#include "DSV/Helpers/PhysicalDevicePicker.hpp"

namespace DSV {
	namespace Helpers {
	  	PhysicalDevicePickerInterface::PhysicalDevicePickerInterface(std::vector<VkPhysicalDevice> physicalDevices) {
		  	m_candidates = std::vector<PhysicalDeviceCandidate>();
			for (uint32_t index = 0; index < physicalDevices.size(); index++) {
				m_candidates.push_back({});
				m_candidates.at(index).handler = physicalDevices.at(index);
				vkGetPhysicalDeviceProperties(physicalDevices.at(index), &m_candidates.at(index).properties);
				vkGetPhysicalDeviceFeatures(physicalDevices.at(index), &m_candidates.at(index).features);
				uint32_t queueFamilyCount = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices.at(index), &queueFamilyCount, nullptr);
				m_candidates.at(index).queueFamilyProperties.resize(queueFamilyCount);
				vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices.at(index), &queueFamilyCount, m_candidates.at(index).queueFamilyProperties.data());
			}
		}
		

		void PhysicalDeviceDefaultPicker::SetScore() {
			for (uint32_t index = 0; index < m_candidates.size(); index++) {
				switch(m_candidates.at(index).properties.deviceType) {
					case VK_PHYSICAL_DEVICE_TYPE_OTHER:
						break;
					case VK_PHYSICAL_DEVICE_TYPE_CPU:
						m_candidates.at(index).score += 1000;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
						m_candidates.at(index).score += 1000;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
						m_candidates.at(index).score += 2000;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
						m_candidates.at(index).score += 3000;
						break;
				}

				m_candidates.at(index).score += m_candidates.at(index).properties.limits.maxImageDimension2D;

				for (auto properties : m_candidates.at(index).queueFamilyProperties) {
					m_candidates.at(index).score += 100 * properties.queueCount;
				}
			}
		}


		PhysicalDeviceDefaultPicker::PhysicalDeviceDefaultPicker(std::vector<VkPhysicalDevice> physicalDevices) : PhysicalDevicePickerInterface(physicalDevices) {}

		uint32_t PhysicalDevicePickerInterface::PickMostRated() {
			if (m_candidates.size() == 0) {
				throw Exception(std::string(DSV_MSG_THERE_IS_NO_MORE_DEVICE_AVAILABLE));
			}

			uint32_t score = 0;
			uint32_t physicalDeviceIndex = 0;

			for (uint32_t index = 0; index < m_candidates.size(); index++) {
				if (m_candidates.at(index).score > score) {
					physicalDeviceIndex = index;
				}
			}
			m_candidates.erase(m_candidates.begin() + physicalDeviceIndex);
			return physicalDeviceIndex;
		}
	}
}
