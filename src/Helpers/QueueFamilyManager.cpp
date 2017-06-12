#include "DSV/Helpers/QueueFamilyManager.hpp"

namespace DSV {
	namespace Helpers {
		QueueFamilyManager::QueueFamilyManager(VkPhysicalDevice physicalDevice) {
			m_physicalDevice = physicalDevice;
			m_queueFamilyProperties = GetQueueFamilyProperties(physicalDevice);
			
			// Initiate stocks
			
			uint32_t index =0;
			for(auto properties : m_queueFamilyProperties) {
				QueueFamilyStock stock;
				stock.familyIndex = index;
				stock.remains = properties.queueCount;
				stock.flags = properties.queueFlags;

				// We're storing queue family in the reverse order so we can process the most specific ones first.

				m_queueFamilyStocks.insert(m_queueFamilyStocks.begin(), stock);
				index++;
			}
		}

		void QueueFamilyManager::Manage(std::vector<float> graphic, std::vector<float> compute, std::vector<float> transfert, std::vector<float> sparse) {
			std::map<int, VkQueueFlagBits, std::greater<int>> queueFamilyRequirements;

			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(graphic.size(), VK_QUEUE_GRAPHICS_BIT));
			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(compute.size(), VK_QUEUE_COMPUTE_BIT));
			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(transfert.size(), VK_QUEUE_TRANSFER_BIT));
			queueFamilyRequirements.insert(std::pair<int, VkQueueFlagBits>(sparse.size(), VK_QUEUE_SPARSE_BINDING_BIT));

			std::map<int, VkQueueFlagBits>::iterator it;
			for (it = queueFamilyRequirements.begin(); it != queueFamilyRequirements.end(); it++) {
				switch (it->second) {
					case VK_QUEUE_SPARSE_BINDING_BIT:
						ProcessQueues(&m_sparseQueuesInUse, VK_QUEUE_SPARSE_BINDING_BIT, sparse);
						break;
					case VK_QUEUE_TRANSFER_BIT:
						break;
					case VK_QUEUE_COMPUTE_BIT:
						break;
					case VK_QUEUE_GRAPHICS_BIT:
						break;
				}
			}
		}

		void QueueFamilyManager::ProcessQueues(std::vector<QueueInUse> * queues, VkQueueFlagBits flag, std::vector<float> priorities) {
			for (auto priority : priorities) {
				QueueFamilyStock * stock = GetStockByFlag(flag);
				QueueInUse queue = {};
				queue.priority = priority;
				queue.familyIndex = stock.familyIndex;
				queue.index = 
				queues->push_back();
				
			}
		}
		
		QueueFamilyStock * QueueFamilyManager::GetStockByFlag(VkQueueFlagBits flag) {
			for (auto& stock : m_queueFamilyStocks) {
				if(stock.remains > 0 && (stock.flags & flag != 0)) {
				  	stock.remains--;
					return &stock;
				}
			}
			throw Exception(DSV_MSG_THERE_IS_NOT_ENOUGH_QUEUES_AVAILABLE);
		}
	}
}
