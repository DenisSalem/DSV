#ifndef DSV_GRAPHIC_VULKAN_APPLICATION
#define DSV_GRAPHIC_VULKAN_APPLICATION

#include "DSV/VulkanApplication.hpp"

#define DSV_MSG_FAILED_TO_CREATE_WINDOW_SURFACE "DSV: Failed to create window surface!"
#define DSV_MSG_CANNOT_RETRIEVE_SURFACE_CAPABILITIES "DSV: Cannot retrieve surface capabilities!"
#define DSV_MSG_FAILED_TO_CREATE_SWAPCHAIN "DSV: Failed to create swapchain!"
#define DSV_MSG_UNKNOWN_FORMAT "DSV: Unknown format!"
#define DSV_MSG_UNKNOWN_PRESENT_MODE "DSV: Unknown present mode!"

#define DSV_UNKNOWN_FORMAT 3
#define DSV_UNKNOWN_PRESENT_MODE 4

namespace DSV {
	VkSurfaceFormatKHR GetSurfaceFormat(std::vector<VkSurfaceFormatKHR> formats, VkFormat requiredFormat);
	VkPresentModeKHR GetSurfacePresentMode(std::vector<VkPresentModeKHR>, VkPresentModeKHR requiredPresentMode);
	class GraphicVulkanApplication : public VulkanApplication {
		public:
			GraphicVulkanApplication() : GraphicVulkanApplication("Generic DSV Vulkan Application","No Engine",VK_MAKE_VERSION(1,0,0),VK_MAKE_VERSION(1,0,0)) {};
			GraphicVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion); 
			~GraphicVulkanApplication();


			VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(int physicalDeviceIndex);
			std::vector<VkSurfaceFormatKHR> GetSurfaceFormats(int physicalDeviceIndex);
			std::vector<VkPresentModeKHR> GetSurfacePresentModes(int physicalDeviceIndex);
			VkSurfaceKHR GetSurface();

			void DefaultSwapChainSetup(VkSurfaceCapabilitiesKHR capabilities, VkSurfaceFormatKHR format, VkPresentModeKHR presentMode, VkExtent2D extent);
			void DefaultImageViewsSetup();
                        void CreateSwapChain();

		protected:
			VkSwapchainCreateInfoKHR m_swapChainCreateInfo;
			VkSurfaceKHR m_pSurface;
			VkSurfaceFormatKHR m_surfaceFormat;
			VkPresentModeKHR m_surfacePresentMode;
			VkExtent2D m_surfaceExtent;
			VkSwapchainKHR m_pSwapChain;
                        std::vector<VkImage> m_swapChaineImages;
                        std::vector<VkImageView> m_imageViews;
	};
}

#endif
