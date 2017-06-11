#ifndef DSV_QUEUE_FAMILY_MANAGER
#define DSV_QUEUE_FAMILY_MANAGER

#include <map>

#include "DSV/Helpers.hpp"

namespace DSV {
	namespace Helpers {

		typedef struct QueueFamilyStock {
			uint32_t familyIndex;
			uint32_t remains;
		} QueueFamilyStock;

		typedef struct QueueFamilyInUse {
			float priority;
			uint32_t familyIndex;
			uint32_t index;
		} QueueFamilyInUse;

		class QueueFamilyManager {
			public:
				QueueFamilyManager(VkPhysicalDevice physicalDevice, std::vector<float> graphic, std::vector<float> compute, std::vector<float> transfert, std::vector<float> sparse);

				VkQueue GetGraphicQueue(uint32_t index);
				VkQueue GetComputeQueue(uint32_t index);
				VkQueue GetTransfertQueue(uint32_t index);
				VkQueue GetSparseQueue(uint32_t index);
		};
	}
}

#endif
