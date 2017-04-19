#include "DSV/GraphicVulkanApplication.hpp"

namespace DSV {
	GraphicVulkanApplication::GraphicVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) : VulkanApplication(applicationName,engineName,applicationVersion,engineVersion) {
		m_pSurface = nullptr;
	};

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
}
