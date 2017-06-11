#include "DSV/Helpers/QueueFamilyManager.hpp"

namespace DSV {
	namespace Helpers {
		QueueFamilyManager::QueueFamilyManager(VkPhysicalDevice physicalDevice, std::vector<float> graphic, std::vector<float> compute, std::vector<float> transfert, std::vector<float> sparse) {
			VkQueueFamilyProperties queueFamilyProperties = GetQueueFamilyProperties(physicalDevice);
			std::map queueFamilyRequirements;

			queueFamilyRequirement.insert(std::pair<int, VkQueueFlagBits>(graphic.size(), VK_QUEUE_GRAPHICS_BIT));
			queueFamilyRequirement.insert(std::pair<int, VkQueueFlagBits>(compute.size(), VK_QUEUE_COMPUTE_BIT));
			queueFamilyRequirement.insert(std::pair<int, VkQueueFlagBits>(transfert.size(), VK_QUEUE_TRANSFER_BIT));
			queueFamilyRequirement.insert(std::pair<int, VkQueueFlagBits>(sparse.size(), VK_QUEUE_SPARSE_BINDING_BIT));

			map<string, int>::iterator it;

			for ( it = queueFamilyRequirement.begin(); it != queueFamilyRequirement.end(); it++ ) {
    				std::cout << it->first << ':'<< it->second << "\n";
			}
	}
}
