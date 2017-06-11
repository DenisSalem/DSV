#include "DSV/Helpers/QueueFamilyManager.hpp"

namespace DSV {
	namespace Helpers {
		QueueFamilyManager::QueueFamilyManager(VkPhysicalDevice physicalDevice, std::vector<float> graphic, std::vector<float> compute, std::vector<float> transfert, std::vector<float> sparse) {
			std::vector<VkQueueFamilyProperties> queueFamilyProperties = GetQueueFamilyProperties(physicalDevice);
			std::map<int, VkQueueFlagBits, std::greater<int>> queueFamilyRequirements;

			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(graphic.size(), VK_QUEUE_GRAPHICS_BIT));
			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(compute.size(), VK_QUEUE_COMPUTE_BIT));
			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(transfert.size(), VK_QUEUE_TRANSFER_BIT));
			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(sparse.size(), VK_QUEUE_SPARSE_BINDING_BIT));

			std::map<int, VkQueueFlagBits>::iterator it;

			for ( it = queueFamilyRequirements.begin(); it != queueFamilyRequirements.end(); it++ ) {
    				std::cout << it->first << ':'<< it->second << "\n";
			}
		}
	}
}
