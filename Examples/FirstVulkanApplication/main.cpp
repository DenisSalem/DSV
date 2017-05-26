#include "DSV/Core.hpp"

const std::vector<const char *> requiredInstanceExtensions {"VK_EXT_debug_report"};
const std::vector<const char *> requiredInstanceLayers {"VK_LAYER_LUNARG_standard_validation"};

int main(int argc, char ** argv) {
	try {
		// Printing out layers and extensions capabilities...
		DSV::Core::PrintNamesFrom(DSV::Core::GetInstanceLayers(), "Available instance layers:");
		DSV::Core::PrintNamesFrom(DSV::Core::GetInstanceExtensions(nullptr), "Available instance extensions:");
		
		// We first check if both required instance extensions and instance layers are available.
		DSV::Core::AssertInstanceExtensionsAreAvailable(requiredInstanceExtensions);
		DSV::Core::AssertInstanceLayersAreAvailable(requiredInstanceLayers);

		// We then create a Vulkan Instance
		DSV::Core::Instance instance(
			"Hello App",			// Application Name 
			VK_MAKE_VERSION(1, 0, 0),	// Application Version
			"No Engine",			// Engine Name
			VK_MAKE_VERSION(1, 0, 0),	// Engine Version
			requiredInstanceExtensions,	// Required Instance Extensions
			requiredInstanceLayers		// Required Instance Layers
		);

		// Binding debug report callback to the instance
		DSV::Core::Callback callback(instance.GetHandler(), VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, DSV::Core::DefaultDebugCallback);

		// Because it's fancy we can print out what are the available GPUs
		DSV::Core::PrintNamesFrom(instance.GetPhysicalDevicesProperties(), "Available GPUs:");
		
		// Most of the time only one GPU is available, but we need to decide which one to use in case
		// there would be more.
		uint32_t physicalDeviceIndex = instance.PickPhysicalDevice([](std::vector<VkPhysicalDeviceProperties> properties) -> uint32_t { return 0; });



	} catch (const DSV::Core::Exception& e) {
		return EXIT_FAILURE;
	}
	
	return 0;
}
