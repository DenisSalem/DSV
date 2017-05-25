#include <functional>

#include "DSV/Core.hpp"

#ifndef DSV_RESSOURCE_MANAGER
#define DSV_RESSOURCE_MANAGER

namespace DSV {
	namespace Core {
		template <typename VkHandler, typename CreateInfo>
		class RessourceManager {
			public:
				RessourceManager(
					std::function<VkResult(CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
					std::function<void(VkHandler, VkAllocationCallbacks*)> destroy
				);

				RessourceManager(
					std::function<VkResult(VkInstance pInstance, CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
					std::function<void(VkInstance, VkHandler, VkAllocationCallbacks*)> destroy
				);

				RessourceManager(
					std::function<VkResult(VkDevice pDevice, CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
					std::function<void(VkDevice, VkHandler, VkAllocationCallbacks*)> destroy
				);

				~RessourceManager();

				VkHandler GetHandler();

				std::function<void()> Create;
				std::function<void()> Destroy;

			protected:
				const char * m_msgFailedToCreate;
				RessourceManager();
				CreateInfo m_createInfo;
				VkHandler m_pHandler;

				VkInstance m_pInstance;
				VkDevice m_pDevice;
				VkAllocationCallbacks * m_pAllocationCallbacks;

		};
	}
}

#endif
