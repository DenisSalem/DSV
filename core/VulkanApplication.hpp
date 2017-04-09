#ifndef DSV_VULKAN_APPLICATION
#define DSV_VULKAN_APPLICATION

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <functional>
#include <vector>

#define DSV_MSG_FAILED_TO_CREATE_INSTANCE "DSV: Failed to create instance!" 
#define DSV_MSG_VALIDATION_LAYER_REQUESTED "DSV: validation layers requested, but not available!"

namespace DSV {
	extern const bool enableValidationLayers;

	class VulkanApplication {
		public:
			VulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion);
			~VulkanApplication();

			void initVulkan(std::vector<const char *> requiredExtensions);
			
			virtual void run() = 0;

			void SetupDebugCallBack();
			VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags,VkDebugReportObjectTypeEXT objType,uint64_t obj,size_t location,int32_t code,const char* layerPrefix,const char* msg,void* userData);

		protected:
			VkInstance m_pInstance;
 			VkApplicationInfo m_appInfo;
			VkInstanceCreateInfo m_instanceCreateInfo;
			VkDebugReportCallbackEXT callback;
			
	};
}

#endif
