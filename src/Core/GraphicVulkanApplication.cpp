#include "DSV/GraphicVulkanApplication.hpp"

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
                m_pVertexShader = nullptr;
                m_pFragmentShader = nullptr;
		m_pImageViews = std::vector<VkImageView>(0);
                m_pSwapChainImages = std::vector<VkImage>(0);
		m_vertexShader = std::vector<char>(0);
		m_fragmentShader = std::vector<char>(0);
		m_surfaceFormat = {};
		m_surfacePresentMode = {};
		m_surfaceExtent = {};
		m_swapChainCreateInfo = {};
		m_imageViewsCreateInfo = std::vector<VkImageViewCreateInfo>(0);
	};

	GraphicVulkanApplication::~GraphicVulkanApplication() {
		for (int i = 0; i < m_pImageViews.size(); i++) {
			vkDestroyImageView(m_pDevice, m_pImageViews[i], nullptr);
		}

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

                uint32_t imageCount = 0;
                vkGetSwapchainImagesKHR(m_pDevice, m_pSwapChain, &imageCount, nullptr);
                m_pSwapChainImages.resize(imageCount);
		m_imageViewsCreateInfo.resize(imageCount);
                vkGetSwapchainImagesKHR(m_pDevice, m_pSwapChain, &imageCount, m_pSwapChainImages.data());
                m_pImageViews.resize(m_pSwapChainImages.size(), nullptr);
	}

        void GraphicVulkanApplication::DefaultImageViewsSetup() {
                for(uint32_t i = 0; i < m_pImageViews.size(); i++) {
			m_imageViewsCreateInfo[i] = {};
			m_imageViewsCreateInfo[i].sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			m_imageViewsCreateInfo[i].image = m_pSwapChainImages[i];
			m_imageViewsCreateInfo[i].viewType = VK_IMAGE_VIEW_TYPE_2D;
			m_imageViewsCreateInfo[i].format = m_surfaceFormat.format;
			m_imageViewsCreateInfo[i].components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			m_imageViewsCreateInfo[i].components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			m_imageViewsCreateInfo[i].components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			m_imageViewsCreateInfo[i].components.a = VK_COMPONENT_SWIZZLE_IDENTITY; 
			m_imageViewsCreateInfo[i].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			m_imageViewsCreateInfo[i].subresourceRange.baseMipLevel = 0;
			m_imageViewsCreateInfo[i].subresourceRange.levelCount = 1;
			m_imageViewsCreateInfo[i].subresourceRange.baseArrayLayer = 0;
			m_imageViewsCreateInfo[i].subresourceRange.layerCount = 1;	
                }
        }

	void GraphicVulkanApplication::LoadShaders(const char * vertexShaderFilename, const char * fragmentShaderFilename) {
		std::ifstream vertexShader(vertexShaderFilename, std::ios::ate | std::ios::binary); 
		std::ifstream fragmentShader(fragmentShaderFilename, std::ios::ate | std::ios::binary);

		if(!vertexShader.is_open()) {
			throw(DSV_FAILED_TO_LOAD_VERTEX_SHADER, DSV_MSG_FAILED_TO_LOAD_VERTEX_SHADER);
		}
		if(!fragmentShader.is_open()) {
			throw(DSV_FAILED_TO_LOAD_VERTEX_SHADER, DSV_MSG_FAILED_TO_LOAD_VERTEX_SHADER);
		}

		size_t vertexShaderSize = (size_t) vertexShader.tellg();
		size_t fragmentShaderSize = (size_t) fragmentShader.tellg();

		vertexShader.seekg(0);
		fragmentShader.seekg(0);

		m_vertexShader.resize(vertexShaderSize);
		m_fragmentShader.resize(fragmentShaderSize);

		vertexShader.read(m_vertexShader.data(), vertexShaderSize);
		fragmentShader.read(m_fragmentShader.data(), fragmentShaderSize);
		vertexShader.close();
		fragmentShader.close();
	}
	void GraphicVulkanApplication::CreateVertexShader() {
		CreateShader(m_vertexShader);
	}

	void GraphicVulkanApplication::CreateFragmentShader() {
		CreateShader(m_fragmentShader);
	}

	void GraphicVulkanApplication::CreateShader(std::vector<char> shader) {
		VkShaderModuleCreateInfo shaderCreateInfo = {};
		shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderCreateInfo.codeSize shader.size();
		std::vector<uint32_t> aligned(shader.size() / sizeof(uint32_t) + 1);
		memcpy(aligned.data(), shader.data(), shader.size());
		shaderCreateInfo.pCode = aligned.data();

		VkResult result = vkCreateShaderModule(m_pDevice, &shaderCreateInfo, nullptr, &m_pVertexShader);
		if(result != VK_SUCCESS) {
			throw Exception(result, DSV_MSG_FAILED_TO_CREATE_SHADER);
		}
        }

	void GraphicVulkanApplication::CreateImageViews() {
		VkResult result;
                for(uint32_t i = 0; i < m_pImageViews.size(); i++) {
			result = vkCreateImageView(m_pDevice, &m_imageViewsCreateInfo[i], nullptr, &m_pImageViews[i]);
			if (result != VK_SUCCESS) {
				throw Exception(result, DSV_MSG_FAILED_TO_CREATE_IMAGE_VIEW);
			}
		}
	}

	VkSurfaceKHR GraphicVulkanApplication::GetSurface() {
		return m_pSurface;
	}
}
