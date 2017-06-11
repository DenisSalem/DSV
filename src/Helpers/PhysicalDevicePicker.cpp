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
				m_candidates.at(index).queueFamilyProperties = GetQueueFamilyProperties(physicalDevices.at(index));
			}
		}

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

		void PhysicalDevicePickerInterface::FilterByPhysicalDeviceType(VkPhysicalDeviceType physicalDeviceType, bool remove) {
			std::vector<uint32_t> toRemove = std::vector<uint32_t>();
			for (uint32_t index =0; index < m_candidates.size(); index++) {
			  	bool match = m_candidates.at(index).properties.deviceType == physicalDeviceType;
			  	if (remove == match) {
					toRemove.push_back(index);
				}
			}
			Remove(toRemove, DSV_MSG_NO_GPU_MATCHING_REQUIRED_DEVICE_TYPE);
		}

		void PhysicalDevicePickerInterface::FilterByPhysicalDeviceNameSubstring(const char * substring, bool remove) {
			std::vector<uint32_t> toRemove = std::vector<uint32_t>();
			for (uint32_t index =0; index < m_candidates.size(); index++) {
			  	bool match = std::string(m_candidates.at(index).properties.deviceName).find(substring) != std::string::npos;
			  	if( remove == match ) {
						toRemove.push_back(index);
				}
			}
			Remove(toRemove, DSV_MSG_NO_GPU_MATCHING_REQUIRED_DEVICE_NAME);
		}

		void PhysicalDevicePickerInterface::FilterByQueueFamily(VkQueueFlagBits queueFlag) {
			if ( queueFlag != VK_QUEUE_GRAPHICS_BIT && queueFlag != VK_QUEUE_COMPUTE_BIT && queueFlag != VK_QUEUE_TRANSFER_BIT && queueFlag != VK_QUEUE_SPARSE_BINDING_BIT) {
				throw Exception(DSV_MSG_WRONG_GIVEN_QUEUE_FLAG);
			}

			std::vector<uint32_t> toRemove = std::vector<uint32_t>();
			bool match = false;
			for (uint32_t index =0; index < m_candidates.size(); index++) {
				match = false;
				for (const auto& properties : m_candidates.at(index).queueFamilyProperties) {
					match = properties.queueFlags & queueFlag != 0;
					if(match) {
						break;
					}
				}
				if (!match) {
					toRemove.push_back(index);
				}
			}
			Remove(toRemove, DSV_MSG_NO_GPU_MATCHING_REQUIRED_QUEUE_FLAG);
		}

		void PhysicalDevicePickerInterface::Remove(std::vector<uint32_t> toRemove, const char * error) {
			for (auto index : toRemove) {
				m_candidates.erase(m_candidates.begin() + index);
			}

			if (m_candidates.size() == 0) {
				throw Exception(error);
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


	}
}
