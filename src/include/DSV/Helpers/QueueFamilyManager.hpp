#ifndef DSV_QUEUE_FAMILY_MANAGER
#define DSV_QUEUE_FAMILY_MANAGER

#include <map>

#include "DSV/Helpers.hpp"

namespace DSV {
	namespace Helpers {
		class QueueFamilyManager {
			QueueFamilyManager(VkPhysicalDevice physicalDevice, std::vector<float> graphic, std::vector<float> compute, std::vector<float> transfert, std::vector<float> sparse);
			GetGraphicQueue(uint32_t index);
			GetComputeQueue(uint32_t index);
			GetTransfertQueue(uint32_t index);
			GetSparseQueue(uint32_t index);
		};
	}
}

#define
