²#include "DSV/GraphicVulkanApplication.hpp"

namespace DSV {
	VkSurfaceFormatKHR GetSurfaceFormat(std::vector<VkSurfaceFormatKHR> formats, VkFormat requiredFormat) {
		for (const auto current : formats) {
			if (current.format == requiredFormat) {
				return current;
			}
		}
		throw Exception(DSV_UNKNOWN_FORMAT, DSV_MSG_UNKNOWN_FORMAT);
	}

	VkPresentModeKHR GetSurfacePresentMode(std::vector<VkPresentModeKHR> presentModes, VkPresentModeKHR requiredPresentMode) {
		for (const auto current : presentModes) {
			if (current == requiredPresentMode) {
				return current;
			}
		}
		throw Exception(DSV_UNKNOWN_PRESENT_MODE, DSV_MSG_UNKNOWN_PRESENT_MODE);
	}

	GraphicVulkanApplication::GraphicVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) : VulkanApplication(applicationName,engineName,applicationVersion,engineVersion) {
		m_pSwapChain = nullptr;
		m_pSurface = nullptr;
                m_pImageViews = std::vector<VkImage>(0);
                m_swapChainImages = std::vector<VkImageView>(0);
		m_surfaceFormat = {};
		m_surfacePresentMode = {};
		m_surfaceExtent = {};
		m_swapChainCreateInfo = {};
	};

	GraphicVulkanApplication::~GraphicVulkanApplication() {
		if (m_pSwapChain != nullptr) {
			vkDestroySwapchainKHR(m_pDevice, m_pSwapChain,nullptr);
		}
		if (m_pSurface != nullptr) {
			vkDestroySurfaceKHR(m_pInstance, m_pSurface, nullptr);
		}
	}

	VkSurfaceCapabilitiesKHR GraphicVulkanApplication::GetSurfaceCapabilities(int physicalDeviceIndex) {
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &surfaceCapabilities);
		if (result != VK_SUCCESS) {
			throw Exception(result, DSV_MSG_CANNOT_RETRIEVE_SURFACE_CAPABILITIES);
		}
		return surfaceCapabilities;
	}

	std::vector<VkSurfaceFormatKHR> GraphicVulkanApplication::GetSurfaceFormats(int physicalDeviceIndex) {
		uint32_t formatCount;
		std::vector<VkSurfaceFormatKHR> surfaceFormats(0);
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &formatCount, nullptr);
		if (formatCount != 0) {
			surfaceFormats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &formatCount, surfaceFormats.data());
			return surfaceFormats;
		}
		return std::vector<VkSurfaceFormatKHR>(0);
	}

	std::vector<VkPresentModeKHR> GraphicVulkanApplication::GetSurfacePresentModes(int physicalDeviceIndex) {
		uint32_t presentModeCount;
		std::vector<VkPresentModeKHR> surfacePresentModes(0);
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
    			surfacePresentModes.resize(presentModeCount);
    			vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &presentModeCount, surfacePresentModes.data());
			return surfacePresentModes;
		}
		return std::vector<VkPresentModeKHR>(0);
	}

	void GraphicVulkanApplication::DefaultSwapChainSetup(VkSurfaceCapabilitiesKHR capabilities, VkSurfaceFormatKHR format, VkPresentModeKHR presentMode, VkExtent2D extent) {
		m_surfaceFormat = format;
		m_surfacePresentMode = presentMode;
		m_surfaceExtent = extent;

		uint32_t imageCount = capabilities.minImageCount + 1;
		
		if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
			imageCount = capabilities.maxImageCount;
		}

		m_swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		m_swapChainCreateInfo.surface = m_pSurface;
		m_swapChainCreateInfo.minImageCount = imageCount;
		m_swapChainCreateInfo.imageFormat = m_surfaceFormat.format;
		m_swapChainCreateInfo.imageColorSpace = m_surfaceFormat.colorSpace;
		m_swapChainCreateInfo.imageExtent = m_surfaceExtent;

		m_swapChainCreateInfo.imageArrayLayers = 1;
		m_swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		m_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		m_swapChainCreateInfo.queueFamilyIndexCount = 0;
		m_swapChainCreateInfo.pQueueFamilyIndices = nullptr;
		m_swapChainCreateInfo.preTransform = capabilities.currentTransform;
		m_swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		m_swapChainCreateInfo.presentMode = m_surfacePresentMode;
		m_swapChainCreateInfo.clipped = VK_TRUE;
		m_swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	}

	void GraphicVulkanApplication::CreateSwapChain() {
		VkResult result = vkCreateSwapchainKHR(m_pDevice, &m_swapChainCreateInfo, nullptr, &m_pSwapChain);

		if (result != VK_SUCCESS) {
			throw(result, DSV_MSG_FAILED_TO_CREATE_SWAPCHAIN);
		}

                int imageCount = 0;
                vkGetSwapchainImagesKHR(m_pDevice, m_pSwapChain, &imageCount, nullptr);
                m_swapChainImages.resize(imageCount);
                vkGetSwapchainImagesKHR(m_pDevice, m_pSwapChain, &imageCount, m_swapChainImages.data());
                m_imageViews.resize(m_swapChainImages.size, nulltr);
	}

        void GraphicVulkanApplication::DefaultImageViewsSetup() {
                for(uint32_t i = 0; i < m_){
                }
        }

	VkSurfaceKHR GraphicVulkanApplication::GetSurface() {
		return m_pSurface;
	}
}