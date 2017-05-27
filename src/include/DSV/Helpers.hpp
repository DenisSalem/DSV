#ifndef DSV_HELPERS
#define DSV_HELPERS

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

#include "DSV/Core.hpp"

#define DSV_MSG_REQUIRED_LAYERS_UNAVAILABLE "One ore more required layers are unavailable!"
#define DSV_MSG_REQUIRED_EXTENSIONS_UNAVAILABLE "On ore more required extensions are unavailable!"
#define DSV_MSG_REQUIRED_QUEUE_FAMILY_UNSUPPORTED "Required queue family unsuppoted!"


#define DSV_CALLBACK_REPORT_ALL VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT

namespace DSV {
	namespace Helpers {
		typedef enum HelpersErrorCode {
			REQUIRED_LAYERS_UNAVAILABLE,
			REQUIRED_EXTENSIONS_UNAVAILABLE
		} HelpersErrorCode;
		
		VKAPI_ATTR VkBool32 VKAPI_CALL DefaultDebugCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* msg,
			void* userData
		);

		std::vector<VkLayerProperties> GetInstanceLayers();
		std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName);
	
		std::string GetNameFromProperties(VkLayerProperties properties);
		std::string GetNameFromProperties(VkExtensionProperties properties);
		std::string GetNameFromProperties(VkPhysicalDeviceProperties properties);
		std::string GetNameFromProperties(std::string properties);

		template<typename Properties> void PrintNamesFrom(std::vector<Properties> vProperties, const char * header);

		std::vector<std::string> GetPhysicalDeviceFeaturesName(VkPhysicalDevice physicalDevice);
	
		void AssertInstanceLayersAreAvailable(std::vector<const char *> required);
		void AssertInstanceExtensionsAreAvailable(std::vector<const char *> required);

		struct Exception{
			Exception(std::string msg);
			Exception(int code, std::string msg);
			Exception(int code, std::string msg, std::string context);

			int code;
		
			std::string msg;
			std::string context;
		};

		std::vector<VkPhysicalDeviceProperties> GetPhysicalDevicesProperties(std::vector<VkPhysicalDevice> physicalDevices);
		std::vector<VkPhysicalDeviceFeatures> GetPhysicalDevicesFeatures(std::vector<VkPhysicalDevice> physicalDevices);
		std::vector<VkFormatProperties> GetPhysicalDevicesFormatProperties(std::vector<VkPhysicalDevice> physicalDevices, VkFormat format);
		std::vector<VkImageFormatProperties> GetPhysicalDeviceImageFormatProperties(
			std::vector<VkPhysicalDevice> physicalDevices,
			VkFormat format,
			VkImageType type,
			VkImageTiling tiling,
			VkImageUsageFlags usage,
			VkImageCreateFlags flags
		);

		std::vector<VkPhysicalDeviceMemoryProperties> GetPhysicalDeviceMemoryProperties(std::vector<VkPhysicalDevice> physicalDevices);
		std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties(VkPhysicalDevice physicalDevices);
		std::vector< std::vector<VkQueueFamilyProperties> > GetPhysicalDevicesQueueFamilyProperties(std::vector<VkPhysicalDevice> physicalDevices);

		struct QueueCreateInfo {
			std::vector<VkDeviceQueueCreateInfo> createInfo;
			std::vector<float> priorities;
		};

		uint32_t GetQueueFamilyIndex(uint32_t physicalDeviceIndex);
	}
}

#endif