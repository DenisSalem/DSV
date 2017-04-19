#ifndef DSV_GRAPHIC_VULKAN_APPLICATION
#define DSV_GRAPHIC_VULKAN_APPLICATION

#include "DSV/VulkanApplication.hpp"

#define DSV_MSG_FAILED_TO_CREATE_WINDOW_SURFACE "DSV: Failed to create window surface!"
#define DSV_MSG_CANNOT_RETRIEVE_SURFACE_CAPABILITIES "DSV: Cannot retrieve surface capabilities!"

namespace DSV {
	class GraphicVulkanApplication : public VulkanApplication {
		public:
			GraphicVulkanApplication() : GraphicVulkanApplication("Generic DSV Vulkan Application","No Engine",VK_MAKE_VERSION(1,0,0),VK_MAKE_VERSION(1,0,0)) {};
			GraphicVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion);


			VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(int physicalDeviceIndex);
			std::vector<VkSurfaceFormatKHR> GetSurfaceFormats(int physicalDeviceIndex);
			std::vector<VkPresentModeKHR> GetSurfacePresentModes(int physicalDeviceIndex);

		protected:
			VkSurfaceKHR m_pSurface;
	};
}

#endif
