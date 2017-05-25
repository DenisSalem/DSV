#include <functional>

#include "DSV/Core.hpp"

#ifndef DSV_RESSOURCE_MANAGER
#define DSV_RESSOURCE_MANAGER

#define DSV_MSG_FAILED_TO_CREATE_INSTANCE "DSV: Failed to create instance!"

namespace DSV {
	namespace Core {
		template <typename VkHandler, typename CreateInfo>
		class RessourceManager {
			public:
				RessourceManager(
					std::function<VkResult(CreateInfo *, VkAllocationCallbacks *, VkHandler *)> create,
					std::function<void(VkHandler, VkAllocationCallbacks*)> destroy
				);

				~RessourceManager();

				std::function<void()> Create;
				std::function<void()> Destroy;

			protected:
				CreateInfo m_createInfo;
				VkHandler m_handler;
				VkAllocationCallbacks * m_pAllocationCallbacks;

		};
	}
}

#endif
