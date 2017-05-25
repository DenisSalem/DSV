#include "DSV/Core/Helpers.hpp"
#include "DSV/Core/RessourceManager.hpp"

namespace DSV {
	namespace Core {
	  	template <typename VkHandler, typename CreateInfo>
		RessourceManager<VkHandler, CreateInfo>::RessourceManager(
			std::function<VkResult(CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
			std::function<void(VkHandler, VkAllocationCallbacks*)> destroy
		) : RessourceManager() {
			this->Create = [this, create]() {
				VkResult result = create(&this->m_createInfo, this->m_pAllocationCallbacks, &this->m_pHandler);
				if (result != VK_SUCCESS) {
					throw Exception(result, this->m_msgFailedToCreate);
				}
			};

			this->Destroy = [this,destroy](){
			  	//destroy(this->m_pHandler, this->m_pAllocationCallbacks);
			};
		}

	  	template <typename VkHandler, typename CreateInfo>
		RessourceManager<VkHandler, CreateInfo>::RessourceManager(
			std::function<VkResult(VkInstance, CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
			std::function<void(VkInstance, VkHandler, VkAllocationCallbacks*)> destroy
		) : RessourceManager() {
			this->Create = [this, create]() {
				VkResult result = create(this->m_pInstance, &this->m_createInfo, this->m_pAllocationCallbacks, &this->m_pHandler);
				if (result != VK_SUCCESS) {
					throw Exception(result, this->m_msgFailedToCreate);
				}
			};

			this->Destroy = [this,destroy](){
			  	destroy(this->m_pInstance, this->m_pHandler, this->m_pAllocationCallbacks);
			};
		}

	  	template <typename VkHandler, typename CreateInfo>
		RessourceManager<VkHandler, CreateInfo>::RessourceManager() {
			m_pHandler = nullptr;
			m_pAllocationCallbacks = nullptr;
			m_createInfo = {};
		}

	  	template <typename VkHandler, typename CreateInfo>
		RessourceManager<VkHandler, CreateInfo>::~RessourceManager() {
		  	std::cout << "Destroy " << typeid(VkHandler).name() <<"\n";
			this->Destroy();
		}

	  	template <typename VkHandler, typename CreateInfo>
		VkHandler RessourceManager<VkHandler, CreateInfo>::GetHandler() {
			return m_pHandler;
		}

		

		template class RessourceManager<VkInstance, VkInstanceCreateInfo>;
		template class RessourceManager<VkDebugReportCallbackEXT, VkDebugReportCallbackCreateInfoEXT>;
	}
}
