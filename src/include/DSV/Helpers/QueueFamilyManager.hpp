#ifndef DSV_QUEUE_FAMILY_MANAGER
#define DSV_QUEUE_FAMILY_MANAGER

#include <map>

#include "DSV/Helpers.hpp"

#define DSV_MSG_THERE_IS_NOT_ENOUGH_QUEUES_AVAILABLE "There is not enough queues available!"

namespace DSV {
	namespace Helpers {

		typedef struct QueueFamilyStock {
			uint32_t familyIndex;
			uint32_t remains;
			VkQueueFlags flags;
		} QueueFamilyStock;

		typedef struct QueueInUse {
			float priority;
			uint32_t familyIndex;
			uint32_t index;
		} QueueInUse;

		class QueueFamilyManager {
			public:
				QueueFamilyManager(VkPhysicalDevice physicalDevice);
				void Manage(std::vector<float> graphic, std::vector<float> compute, std::vector<float> transfert, std::vector<float> sparse);

				VkQueue GetGraphicQueue(uint32_t index);
				VkQueue GetComputeQueue(uint32_t index);
				VkQueue GetTransfertQueue(uint32_t index);
				VkQueue GetSparseQueue(uint32_t index);
			private:
				void ProcessQueues(std::vector<QueueInUse> * queues, VkQueueFlagBits flag, std::vector<float> priorities);
				QueueFamilyStock * GetStockByFlag(VkQueueFlagBits flag);

				VkPhysicalDevice m_physicalDevice;
				std::vector<VkQueueFamilyProperties> m_queueFamilyProperties;
				std::vector<QueueFamilyStock> m_queueFamilyStocks;
				std::vector<QueueInUse> m_graphicQueuesInUse;
				std::vector<QueueInUse> m_computeQueuesInUse;
				std::vector<QueueInUse> m_transfertQueuesInUse;
				std::vector<QueueInUse> m_sparseQueuesInUse;
		};
	}
}

#endif
