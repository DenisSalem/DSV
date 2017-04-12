#ifndef DSV_VULKAN_APPLICATION
#define DSV_VULKAN_APPLICATION

#include <iostream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

#define DSV_MSG_FAILED_TO_CREATE_INSTANCE "DSV: Failed to create instance!" 
#define DSV_MSG_AVAILABLE_INSTANCE_LAYERS "DSV: Available instance layers:\n" 

namespace DSV {

	std::vector<VkLayerProperties> GetInstanceLayers();
	void PrintInstanceLayers(std::vector<VkLayerProperties> pProperties);

	class VulkanApplication {
		public:
			VulkanApplication() : VulkanApplication("Generic DSV Vulkan Application","No Engine",VK_MAKE_VERSION(1,0,0),VK_MAKE_VERSION(1,0,0)) {}
			VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion);
			~VulkanApplication();

			void InitVulkan(std::vector<const char *> requiredExtensions);
			
			virtual void Run() = 0;

		protected:
			VkInstance m_pInstance;
 			VkApplicationInfo m_appInfo;
			VkInstanceCreateInfo m_instanceCreateInfo;
	};
}

#endif
