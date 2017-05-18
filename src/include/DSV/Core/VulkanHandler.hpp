#include <functionnal>

namespace DSV {
	namespace Core {
		templace <typename VkSomething> class VulkanHandler {
			public:
				VulkanHandler(std::function<void(VkSomething, VkAllocationCallbacks*)> deleter);
				VulkanHandler(std::function<void(VkSomething, VkAllocationCallbacks*)> deleter, VkAllocationCallbacks * allocCallbacks);
		}
	}
}
