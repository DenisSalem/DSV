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
#define DSV_MSG_FAILED_TO_CREATE_LOGICAL_DEVICE "DSV: Failed to create logical device!"
#define DSV_MSG_QUEUE_FAMILY_INDEX_DEFINED_TWICE "DSV: Queue family index defined twice!"
#define DSV_MSG_REQUIRED_QUEUE_FAMILY_MISSING "DSV: Required queue family missing!"
#define DSV_MSG_FAILED_TO_CREATE_COMMAND_POOL "DSV: Failed to create command pool!"

#define DSV_MSG_AVAILABLE_INSTANCE_LAYERS "DSV: Available instance layers:\n"
#define DSV_MSG_AVAILABLE_INSTANCE_EXTENSIONS "DSV: Available instance extensions:\n"
#define DSV_MSG_AVAILABLE_DEVICE_EXTENSIONS "DSV: Available device extensions:\n"
#define DSV_MSG_AVAILABLE_INSTANCE_PHYSICAL_DEVICES "DSV: Available physical devices:\n"

#define DSV_NO_PHYSICAL_DEVICES	1
#define DSV_QUEUE_FAMILY_INDEX_DEFINED_TWICE 2
#define DSV_REQUIRED_QUEUE_FAMILY_MISSING 3

#define DSV_TRACE { std::cerr << "DSV_TRACE: "<< __FILE__ << ", " << __LINE__ << "\n"; } 

namespace DSV {
	
	
	std::vector<VkLayerProperties> GetInstanceLayers();
	std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName);
	
	void PrintLayers(const char * header, std::vector<VkLayerProperties> pProperties);
	void PrintExtensions(const char * header, std::vector<VkExtensionProperties> pProperties);
	
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
			VulkanApplication() : VulkanApplication("Generic DSV Vulkan Application","No Engine",VK_MAKE_VERSION(1,0,0),VK_MAKE_VERSION(1,0,0)) {};
			VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion);
			~VulkanApplication();
			
			std::vector<VkQueueFamilyProperties> GetQueueFamilies(int physicalDeviceIndex);
			std::vector<VkPhysicalDevice> GetPhysicalDevices();
			std::vector<VkExtensionProperties> GetDeviceExtensions(int physicalDeviceIndex, const char * pLayerName);
			
			void PrintPhysicalDevices();
			void AddQueueFamily(int32_t queueFamilyIndex, uint32_t const queueCount, std::vector<float> queuePriorities);
			void CreateLogicalDevice(int physicalDeviceIndex, const std::vector<const char*> requiredDeviceExtensions);
			void CreateLogicalDevice(int physicalDeviceIndex);
			void SetupCallback(VkDebugReportFlagsEXT flags, PFN_vkDebugReportCallbackEXT debugCallback);	
			void InitVulkan(std::vector<const char *> requiredExtensions, std::vector<const char *> requiredLayers);
			void InitVulkan();
			uint32_t VulkanApplication::GetRequiredQueueFamilyIndex(VkQueueFlagBits flags);	
			void CreateCommandPool(VkQueueFlagBits flags);

			VkInstance GetInstance();
			
		protected:
			std::vector<const char *> m_requiredExtensions;
			std::vector<const char *> m_requiredLayers;
			VkInstance m_pInstance;
			VkDevice m_pDevice;
 			VkApplicationInfo m_appInfo;
			VkInstanceCreateInfo m_instanceCreateInfo;
			std::vector<VkDeviceQueueCreateInfo> m_queueCreateInfos;
			std::vector< std::vector<float> > m_queuePriorities;
			VkDebugReportCallbackCreateInfoEXT m_callbackCreateInfo;
			VkDeviceCreateInfo m_deviceCreateInfo;
			VkDebugReportCallbackEXT m_pCallback;
			std::vector<VkPhysicalDevice> m_physicalDevices;
			VkPhysicalDeviceFeatures m_deviceFeatures;
			
			VkCommandPool m_pCommandPool;
			VkCommandPoolCreateInfo m_commandPoolCreateInfo;
	};
}

#endif
