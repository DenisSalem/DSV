#include "DSV/Core/VulkanHandlers.hpp"

namespace DSV {
	namespace Core {

		//----- VulkanRessourceManager -----//

	  	template <typename VkHandler, typename CreateInfo>
		VulkanRessourceManager<VkHandler, CreateInfo>::VulkanRessourceManager(
			std::function<VkResult(CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
			std::function<void(VkHandler, VkAllocationCallbacks*)> destroy,
			VkAllocationCallbacks * pAllocationCallbacks
		) {
		  	this->Create = [=](CreateInfo * pCreateInfo, VkHandler * pHandler) { 
				return create(pCreateInfo, pAllocationCallbacks, pHandler);
			};

			this->Destroy = [=](VkHandler pHandler){
			  	destroy(pHandler, pAllocationCallbacks);
			};
		}

		//----- VulkanHandler -----//
	
		template <typename VkHandler, typename CreateInfo>
		VulkanHandler<VkHandler, CreateInfo>::VulkanHandler(CreateInfo createInfo, VkAllocationCallbacks * pAllocationCallbacks) {	
			m_ressourceManager = nullptr;
			m_pAllocationCallbacks = pAllocationCallbacks;
			m_handler = VK_NULL_HANDLE;
			m_createInfo = createInfo;
			
			auto currentType = typeid(VkHandler).hash_code();
			
			if ( currentType == typeid(VkInstance).hash_code() ) {
				m_ressourceManager = new VulkanRessourceManager<VkHandler, CreateInfo>(vkCreateInstance, vkDestroyInstance, m_pAllocationCallbacks);
			}
		}

		template <typename VkHandler, typename CreateInfo>
		VulkanHandler<VkHandler, CreateInfo>::~VulkanHandler() {
		  	m_ressourceManager->Destroy(m_handler);
			delete m_ressourceManager;
		}
		
		//----- Explicit instanciation -----//
		
		template class VulkanHandler<VkInstance, VkInstanceCreateInfo>;
	}
}
