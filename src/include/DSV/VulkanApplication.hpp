#ifndef DSV_VULKAN_APPLICATION
#define DSV_VULKAN_APPLICATION

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <vulkan/vulkan.h>

#define DSV_MSG_FAILED_TO_CREATE_INSTANCE "DSV: Failed to create instance!" 
#define DSV_MSG_FAILED_TO_CREATE_CALLBACK "DSV: Failed to create callback!" 
#define DSV_MSG_NO_PHYSICAL_DEVICES "DSV: No physical devices!"

#define DSV_MSG_AVAILABLE_INSTANCE_LAYERS "DSV: Available instance layers:\n"
#define DSV_MSG_AVAILABLE_INSTANCE_EXTENSIONS "DSV: Available instance extensions:\n"
#define DSV_MSG_AVAILABLE_INSTANCE_PHYSICAL_DEVICES "DSV: Available instance physical devices:\n"

#define DSV_NO_PHYSICAL_DEVICES	1

#define DSV_TRACE { std::cerr << "DSV: "<< __FILE__ << ", " << __LINE__ << "\n"; } 

namespace DSV {
	
	
	std::vector<VkLayerProperties> GetInstanceLayers();
	std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName);
	
	void PrintInstanceLayers(std::vector<VkLayerProperties> pProperties);
	void PrintInstanceExtensions(std::vector<VkExtensionProperties> pProperties);
	
	bool IsInstanceLayersAvailable(std::vector<const char *> required);
	bool IsInstanceExtensionsAvailable(std::vector<const char *> required);

	struct Exception {
		Exception(int code, const char * msg);
		Exception(int code, const char * msg, const char * context);

		int code;
		
		std::string msg;
		std::string context;
	};

	class VulkanApplication {
		public:
			VulkanApplication() : VulkanApplication("Generic DSV Vulkan Application","No Engine",VK_MAKE_VERSION(1,0,0),VK_MAKE_VERSION(1,0,0)) {}
			VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion);
			~VulkanApplication();

			void PrintPhysicalDevices();
			void CreateLogicalDevice(int index, uint32_t queueCount);
			void SetupCallback(VkDebugReportFlagsEXT flags, PFN_vkDebugReportCallbackEXT debugCallback);	
			void InitVulkan(std::vector<const char *> requiredExtensions, std::vector<const char *> requiredLayers);
			virtual void Run() = 0;

		protected:
			VkInstance m_pInstance;
 			VkApplicationInfo m_appInfo;
			VkInstanceCreateInfo m_instanceCreateInfo;
			VkDebugReportCallbackCreateInfoEXT m_callbackCreateInfo;
			VkDebugReportCallbackEXT m_pCallback;
			std::vector<VkPhysicalDevice> m_physicalDevices;
	};
}

#endif
