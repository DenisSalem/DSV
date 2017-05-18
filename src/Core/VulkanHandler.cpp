#include "VulkanHandler.hpp"

namespace DSV {
	namespace Core {
	  	VulkanHandler::VulkanHandler(std::function<void(VkSomething, VkAllocationCallbacks*)> destroy) {
			this->Destroy = [=](VkSomething vkSomething){ destroy(vkSomething, nullptr) };
		}

	  	VulkanHandler::VulkanHandler(std::function<void(VkSomething, VkAllocationCallbacks*)> destroy, VkAllocationCallbacks * allocCallbacks) {
			this->Destroy = [=](VkSomething vkSomething){ destroy(vkSomething, allocCallbacks) };
		}
	}
	
}
