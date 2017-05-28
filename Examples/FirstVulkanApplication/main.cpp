#include "DSV/Core.hpp"
#include "DSV/Helpers.hpp"

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
			"Hello App",			// Application name 
			VK_MAKE_VERSION(1, 0, 0),	// Application version
			"No Engine",			// Engine name
			VK_MAKE_VERSION(1, 0, 0),	// Engine version
			VK_API_VERSION_1_0,		// Vulkan API version
			requiredInstanceExtensions,	// Required instance extensions
			requiredInstanceLayers		// Required instance layers
		);

		#ifdef EXAMPLE_DEBUG
		// Binding debug report callback to the instance
		DSV::Core::Callback callback(instance.GetHandler(), VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, DSV::Helpers::DefaultDebugCallback);
		#endif



	} catch (const DSV::Helpers::Exception& e) {
		return EXIT_FAILURE;
	}
	
	return 0;
}
