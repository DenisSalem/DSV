#include "DSV/Core.hpp"

#define EXAMPLE_DEBUG

#ifdef EXAMPLE_DEBUG
const std::vector<const char *> requiredInstanceExtensions {"VK_EXT_debug_report"};
const std::vector<const char *> requiredInstanceLayers {"VK_LAYER_LUNARG_standard_validation"};
#else
const std::vector<const char *> requiredInstanceExtensions {};
const std::vector<const char *> requiredInstanceLayers {};
#endif

int main(int argc, char ** argv) {
	try {
		// Printing out layers and extensions capabilities...
		DSV::Helpers::PrintNamesFrom(DSV::Helpers::GetInstanceLayers(), "Available instance layers:");
		DSV::Helpers::PrintNamesFrom(DSV::Helpers::GetInstanceExtensions(nullptr), "Available instance extensions:");
		
		// Before serious business begin we must check if both
		// required instance extensions and instance layers are available.
		DSV::Helpers::AssertInstanceExtensionsAreAvailable(requiredInstanceExtensions);
		DSV::Helpers::AssertInstanceLayersAreAvailable(requiredInstanceLayers);

		// We then create a Vulkan Instance
		DSV::Core::Instance instance(
			"Hello App",			// Application Name 
			VK_MAKE_VERSION(1, 0, 0),	// Application Version
			"No Engine",			// Engine Name
			VK_MAKE_VERSION(1, 0, 0),	// Engine Version
			requiredInstanceExtensions,	// Required Instance Extensions
			requiredInstanceLayers		// Required Instance Layers
		);

		#ifdef EXAMPLE_DEBUG
		// Binding debug report callback to the instance
		DSV::Core::Callback callback(instance.GetHandler(), VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, DSV::Helpers::DefaultDebugCallback);
		#endif

		// Because it's fancy we can print out what are the available GPUs
		DSV::Helpers::PrintNamesFrom(instance.GetPhysicalDevicesProperties(), "Available GPUs:");
		
		// Most of the time only one GPU is available, but we need to decide which one to use in case
		// there would be more. For this example we don't really care so we just pick the first available GPU.
		uint32_t physicalDeviceIndex = instance.PickPhysicalDevice(
			[](std::vector<VkPhysicalDeviceProperties> properties) -> uint32_t { return 0; }
		);

		// DSV provides an helper to get the names of availables device features.
		// Why don't use it to print out an overview of the GPU capabilities? :)
		std::vector<std::string> physicalDeviceFeaturesName = DSV::Helpers::GetPhysicalDeviceFeaturesName( instance.GetPhysicalDevice(physicalDeviceIndex));
		DSV::Helpers::PrintNamesFrom(physicalDeviceFeaturesName, "Available physical device features:");

		// For this examples we don't need any particular device features so we left the below empty.
		VkPhysicalDeviceFeatures physicalDeviceFeatures = {};

		//DSV::Core::LogicalDevice(instance.GetPhysicalDevice(physicalDeviceIndex), physicalDeviceFeatures);
	} catch (const DSV::Helpers::Exception& e) {
		return EXIT_FAILURE;
	}
	
	return 0;
}
