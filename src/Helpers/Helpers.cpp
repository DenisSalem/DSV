#include "DSV/Helpers.hpp"

namespace DSV {
	namespace Helpers {
		VKAPI_ATTR VkBool32 VKAPI_CALL DefaultDebugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData) {
			throw Exception(code, std::string("Validation layer: ") + std::string(msg), std::string(layerPrefix));
		}

		std::vector<VkLayerProperties> GetInstanceLayers() {
		  	uint32_t propertiesCount = 0;
			std::vector<VkLayerProperties> pProperties;
			vkEnumerateInstanceLayerProperties(&propertiesCount, nullptr);
			if (propertiesCount != 0) {
			  	pProperties.resize(propertiesCount);
				vkEnumerateInstanceLayerProperties(&propertiesCount, pProperties.data());
			}
			return pProperties;
		}

		std::vector<VkExtensionProperties> GetInstanceExtensions(const char * pLayerName) {
	  		uint32_t propertiesCount = 0;
			std::vector<VkExtensionProperties> pProperties;
			vkEnumerateInstanceExtensionProperties(pLayerName, &propertiesCount, nullptr);
			if (propertiesCount != 0) {
			  	pProperties.resize(propertiesCount);
				vkEnumerateInstanceExtensionProperties(pLayerName, &propertiesCount, pProperties.data());

			}
			return pProperties;
		}

		std::string GetNameFromProperties(VkLayerProperties properties) {
			return std::string(properties.layerName);
		}

		std::string GetNameFromProperties(VkExtensionProperties properties) {
			return std::string(properties.extensionName);
		}

		std::string GetNameFromProperties(VkPhysicalDeviceProperties properties) {
			return std::string(properties.deviceName);
		}

		std::string GetNameFromProperties(std::string properties) {
			return std::string(properties);
		}

		template<typename Properties>
		void PrintNamesFrom(std::vector<Properties> vProperties, const char * header) {
			std::cout << header << "\n";
			for (Properties properties : vProperties) {
				std::cout << "\t" << GetNameFromProperties(properties) << "\n";
			}
		}

		template void PrintNamesFrom(std::vector<VkLayerProperties> vProperties, const char * header);
		template void PrintNamesFrom(std::vector<VkExtensionProperties> vProperties, const char * header);
		template void PrintNamesFrom(std::vector<VkPhysicalDeviceProperties> vProperties, const char * header);
		template void PrintNamesFrom(std::vector<std::string> vProperties, const char * header);

		std::vector<std::string> GetPhysicalDeviceFeaturesName(VkPhysicalDevice physicalDevice) {
			std::vector<std::string> names = std::vector<std::string>();
			VkPhysicalDeviceFeatures features = {};

			vkGetPhysicalDeviceFeatures(physicalDevice, &features);

			if (features.robustBufferAccess) names.push_back(std::string("robustBufferAccess"));
			if (features.fullDrawIndexUint32) names.push_back(std::string("fullDrawIndexUint32"));
			if (features.imageCubeArray) names.push_back(std::string("imageCubeArray"));
			if (features.independentBlend) names.push_back(std::string("independentBlend"));
			if (features.geometryShader) names.push_back(std::string("geometryShader"));
			if (features.tessellationShader) names.push_back(std::string("tessellationShader"));
			if (features.sampleRateShading) names.push_back(std::string("sampleRateShading"));
			if (features.dualSrcBlend) names.push_back(std::string("dualSrcBlend"));
			if (features.logicOp) names.push_back(std::string("logicOp"));
			if (features.multiDrawIndirect) names.push_back(std::string("multiDrawIndirect"));
			if (features.drawIndirectFirstInstance) names.push_back(std::string("drawIndirectFirstInstance"));
			if (features.depthClamp) names.push_back(std::string("depthClamp"));
			if (features.depthBiasClamp) names.push_back(std::string("depthBiasClamp"));
			if (features.fillModeNonSolid) names.push_back(std::string("fillModeNonSolid"));
			if (features.depthBounds) names.push_back(std::string("depthBounds"));
			if (features.wideLines) names.push_back(std::string("wideLines"));
			if (features.largePoints) names.push_back(std::string("largePoints"));
			if (features.alphaToOne) names.push_back(std::string("alphaToOne"));
			if (features.multiViewport) names.push_back(std::string("multiViewport"));
			if (features.samplerAnisotropy) names.push_back(std::string("samplerAnisotropy"));
			if (features.textureCompressionETC2) names.push_back(std::string("textureCompressionETC2"));
			if (features.textureCompressionASTC_LDR) names.push_back(std::string("textureCompressionASTC_LDR"));
			if (features.textureCompressionBC) names.push_back(std::string("textureCompressionBC"));
			if (features.occlusionQueryPrecise) names.push_back(std::string("occlusionQueryPrecise"));
			if (features.pipelineStatisticsQuery) names.push_back(std::string("pipelineStatisticsQuery"));
			if (features.vertexPipelineStoresAndAtomics) names.push_back(std::string("vertexPipelineStoresAndAtomics"));
			if (features.fragmentStoresAndAtomics) names.push_back(std::string("fragmentStoresAndAtomics"));
			if (features.shaderTessellationAndGeometryPointSize) names.push_back(std::string("shaderTessellationAndGeometryPointSize"));
			if (features.shaderImageGatherExtended) names.push_back(std::string("shaderImageGatherExtended"));
			if (features.shaderStorageImageExtendedFormats) names.push_back(std::string("shaderStorageImageExtendedFormats"));
			if (features.shaderStorageImageMultisample) names.push_back(std::string("shaderStorageImageMultisample"));
			if (features.shaderStorageImageReadWithoutFormat) names.push_back(std::string("shaderStorageImageReadWithoutFormat"));
			if (features.shaderStorageImageWriteWithoutFormat) names.push_back(std::string("shaderStorageImageWriteWithoutFormat"));
			if (features.shaderUniformBufferArrayDynamicIndexing) names.push_back(std::string("shaderUniformBufferArrayDynamicIndexing"));
			if (features.shaderSampledImageArrayDynamicIndexing) names.push_back(std::string("shaderSampledImageArrayDynamicIndexing"));
			if (features.shaderStorageBufferArrayDynamicIndexing) names.push_back(std::string("shaderStorageBufferArrayDynamicIndexing"));
			if (features.shaderStorageImageArrayDynamicIndexing) names.push_back(std::string("shaderStorageImageArrayDynamicIndexing"));
			if (features.shaderClipDistance) names.push_back(std::string("shaderClipDistance"));
			if (features.shaderCullDistance) names.push_back(std::string("shaderCullDistance"));
			if (features.shaderFloat64) names.push_back(std::string("shaderFloat64"));
			if (features.shaderInt64) names.push_back(std::string("shaderInt64"));
			if (features.shaderInt16) names.push_back(std::string("shaderInt16"));
			if (features.shaderResourceResidency) names.push_back(std::string("shaderResourceResidency"));
			if (features.shaderResourceMinLod) names.push_back(std::string("shaderResourceMinLod"));
			if (features.sparseBinding) names.push_back(std::string("sparseBinding"));
			if (features.sparseResidencyBuffer) names.push_back(std::string("sparseResidencyBuffer"));
			if (features.sparseResidencyImage2D) names.push_back(std::string("sparseResidencyImage2D"));
			if (features.sparseResidencyImage3D) names.push_back(std::string("sparseResidencyImage3D"));
			if (features.sparseResidency2Samples) names.push_back(std::string("sparseResidency2Samples"));
			if (features.sparseResidency4Samples) names.push_back(std::string("sparseResidency4Samples"));
			if (features.sparseResidency8Samples) names.push_back(std::string("sparseResidency8Samples"));
			if (features.sparseResidency16Samples) names.push_back(std::string("sparseResidency16Samples"));
			if (features.sparseResidencyAliased) names.push_back(std::string("sparseResidencyAliased"));
			if (features.variableMultisampleRate) names.push_back(std::string("variableMultisampleRate"));
			if (features.inheritedQueries) names.push_back(std::string("inheritedQueries"));

			return names;

		}

		void AssertInstanceLayersAreAvailable(std::vector<const char *> required) {
			std::vector<VkLayerProperties> supported = GetInstanceLayers();
			for (const auto& r : required) {
				bool layerFound = false;
				for (const auto& s : supported) {
					if (strcmp(s.layerName, r) == 0) {
						layerFound = true;
						break;
					}
				}
				if (!layerFound) {
					throw Exception(REQUIRED_LAYERS_UNAVAILABLE, DSV_MSG_REQUIRED_LAYERS_UNAVAILABLE);
				}
			}
		}

		void AssertInstanceExtensionsAreAvailable(std::vector<const char *> required) {
			std::vector<VkExtensionProperties> supported = GetInstanceExtensions(nullptr);
			for (const auto& r : required) {
    				bool layerFound = false;
				for (const auto& s : supported) {
					if (strcmp(s.extensionName, r) == 0) {
						layerFound = true;
						break;
					}
				}
				if (!layerFound) {
					throw Exception(REQUIRED_EXTENSIONS_UNAVAILABLE,DSV_MSG_REQUIRED_EXTENSIONS_UNAVAILABLE);
				}
			}
		}
	
		Exception::Exception(std::string msg) : Exception(-1, msg, std::string()) {}

		Exception::Exception(int code, std::string msg) : Exception(code, msg, std::string()) {}
	
		Exception::Exception(int code, std::string msg, std::string context) {
			this->code = code;
			this->msg = msg;
			if (!context.empty()) {
				this->context = context;
				std::cerr << "DSV: " << this->context << "\n";
			}
			std::cerr << "DSV: " << this->msg << "\n";
		}


		std::vector<VkPhysicalDeviceProperties> GetPhysicalDevicesProperties(std::vector<VkPhysicalDevice> physicalDevices) {
			std::vector<VkPhysicalDeviceProperties> physicalDevicesProperties = std::vector<VkPhysicalDeviceProperties>();
			for (const auto& physicalDevice : physicalDevices) {
			  	VkPhysicalDeviceProperties physicalDeviceProperties;
				vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
				physicalDevicesProperties.push_back( physicalDeviceProperties );
			}
			return physicalDevicesProperties;
		}

		std::vector<VkPhysicalDeviceFeatures> GetPhysicalDevicesFeatures(std::vector<VkPhysicalDevice> physicalDevices) {
			std::vector<VkPhysicalDeviceFeatures> physicalDevicesFeatures = std::vector<VkPhysicalDeviceFeatures>();
			for(const auto& physicalDevice : physicalDevices) {
				VkPhysicalDeviceFeatures features = {};
				vkGetPhysicalDeviceFeatures(physicalDevice, &features);
				physicalDevicesFeatures.push_back(features);
			}
			return physicalDevicesFeatures;
		}

		std::vector<VkFormatProperties> GetPhysicalDevicesFormatProperties(std::vector<VkPhysicalDevice> physicalDevices, VkFormat format) {
			std::vector<VkFormatProperties> physicalDevicesFormatProperties = std::vector<VkFormatProperties>();
			for(const auto& physicalDevice : physicalDevices) {
				VkFormatProperties physicalDeviceFormatProperties = {};
				vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &physicalDeviceFormatProperties);
				physicalDevicesFormatProperties.push_back(physicalDeviceFormatProperties);
			}
			return physicalDevicesFormatProperties;
		}

		std::vector<VkImageFormatProperties> GetPhysicalDeviceImageFormatProperties(
			std::vector<VkPhysicalDevice> physicalDevices,
			VkFormat format,
			VkImageType type,
			VkImageTiling tiling,
			VkImageUsageFlags usage,
			VkImageCreateFlags flags
		) {
			std::vector<VkImageFormatProperties> physicalDevicesImageFormatProperties = std::vector<VkImageFormatProperties>();
			for(const auto& physicalDevice : physicalDevices) {
				VkImageFormatProperties physicalDeviceImageFormatProperties = {};
				vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, &physicalDeviceImageFormatProperties);
				physicalDevicesImageFormatProperties.push_back(physicalDeviceImageFormatProperties);
			}
			return physicalDevicesImageFormatProperties;
		}

		std::vector<VkPhysicalDeviceMemoryProperties> GetPhysicalDeviceMemoryProperties(std::vector<VkPhysicalDevice> physicalDevices) {
			std::vector<VkPhysicalDeviceMemoryProperties> physicalDevicesMemoryProperties = std::vector<VkPhysicalDeviceMemoryProperties>();
			for (const auto& physicalDevice : physicalDevices) {
			  	VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties = {};
				vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);
				physicalDevicesMemoryProperties.push_back( physicalDeviceMemoryProperties );
			}
			return physicalDevicesMemoryProperties;
		}

		std::vector<VkQueueFamilyProperties> GetQueueFamilyProperties(VkPhysicalDevice physicalDevice) {
			std::vector<VkQueueFamilyProperties> queueFamilyProperties = std::vector<VkQueueFamilyProperties>();
			uint32_t count = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
			queueFamilyProperties.resize(count);
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, queueFamilyProperties.data());
			return queueFamilyProperties;
		}

		std::vector< std::vector<VkQueueFamilyProperties> > GetPhysicalDevicesQueueFamilyProperties(std::vector<VkPhysicalDevice> physicalDevices) {
			std::vector< std::vector<VkQueueFamilyProperties> > physicalDevicesQueueFamilyProperties = std::vector< std::vector<VkQueueFamilyProperties> >();
			for (const auto& physicalDevice : physicalDevices) {
				physicalDevicesQueueFamilyProperties.push_back(GetQueueFamilyProperties(physicalDevice));
			}
		}

		uint32_t GetQueueFamilyIndex(VkPhysicalDevice physicalDevice, VkQueueFlags requiredQueueFlags, uint32_t minimumRequiredQueues) {
			std::vector<VkQueueFamilyProperties> physicalDeviceQueueFamilyProperties = GetQueueFamilyProperties(physicalDevice);
			uint32_t index = 0;
			for (const auto& properties : physicalDeviceQueueFamilyProperties) {
				if ( (properties.queueFlags & requiredQueueFlags) == requiredQueueFlags && properties.queueCount >= minimumRequiredQueues) {
					return index;
				}
				index++;
			}
			throw Exception(std::string(DSV_MSG_REQUIRED_QUEUE_FAMILY_UNSUPPORTED));
		}
	}
}
