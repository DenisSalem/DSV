#ifndef DSV_VULKAN_HANDLER
#define DSV_VULKAN_HANDLER

#include <functional>

#include "DSV/Core.hpp"

namespace DSV {
	namespace Core {
		//----- VulkanRessourceManager -----//
		
		template <typename VkHandler, typename CreateInfo>
		class VulkanRessourceManager {
			public:
				VulkanRessourceManager(
					std::function<VkResult(CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
					std::function<void(VkHandler, VkAllocationCallbacks*)> destroy,
					VkAllocationCallbacks * pAllocationCallbacks
				);

				std::function<VkResult(CreateInfo * pCreateInfo, VkHandler * pHandler)> Create; 
				std::function<void(VkHandler pHandler)> Destroy; 
		};

		//----- VukanHandler -----//
	
		template <typename VkHandler, typename CreateInfo>
		class VulkanHandler {
			public:
				VulkanHandler(CreateInfo pCreateInfo, VkAllocationCallbacks * pAllocationCallbacks);
				VulkanHandler(VkAllocationCallbacks * pAllocationCallbacks);
				VulkanHandler(CreateInfo pCreateInfo);

				~VulkanHandler();

			protected:
				VkHandler m_handler;
				CreateInfo m_CreateInfo;
				VkAllocationCallbacks * m_pAllocationCallbacks;
				CreateInfo m_createInfo;
				VulkanRessourceManager<VkHandler, CreateInfo> * m_ressourceManager;

		};
		
		typedef VulkanHandler<VkInstance, VkInstanceCreateInfo> InstanceHandler;
	}
}

#endif
