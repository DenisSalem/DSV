#include "DSV/Core/Helpers.hpp"
#include "DSV/Core/RessourceManager.hpp"

namespace DSV {
	namespace Core {
	  	template <typename VkHandler, typename CreateInfo>
		RessourceManager<VkHandler, CreateInfo>::RessourceManager(
			std::function<VkResult(CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
			std::function<void(VkHandler, VkAllocationCallbacks*)> destroy
		) {
			m_handler = nullptr;
			m_pAllocationCallbacks = nullptr;
			m_createInfo = {};
		  	
			this->Create = [this, create]() {
				VkResult result = create(&this->m_createInfo, this->m_pAllocationCallbacks, &this->m_handler);
				if (result != VK_SUCCESS) {
					throw Exception(result, DSV_MSG_FAILED_TO_CREATE_INSTANCE);
				}
			};

			this->Destroy = [this,destroy](){
			  	destroy(this->m_handler, this->m_pAllocationCallbacks);
			};
		}

	  	template <typename VkHandler, typename CreateInfo>
		RessourceManager<VkHandler, CreateInfo>::~RessourceManager() {
			this->Destroy();
		}

		template class RessourceManager<VkInstance, VkInstanceCreateInfo>;
	}
}
