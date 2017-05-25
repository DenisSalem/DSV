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
		// We first check if both required instance extensions and instance layers are available.
		DSV::Core::AssertInstanceExtensionsAreAvailable(requiredInstanceExtensions);
		DSV::Core::AssertInstanceLayersAreAvailable(requiredInstanceLayers);

		DSV::Core::Instance instance(
			"Hello App",			// Application Name 
			VK_MAKE_VERSION(1, 0, 0),	// Application Version
			"No Engine",			// Engine Name
			VK_MAKE_VERSION(1, 0, 0),	// Engine Version
			requiredInstanceExtensions,	// Required Instance Extensions
			requiredInstanceLayers		// Required Instance Layers
		);

	} catch (const DSV::Core::Exception& e) {
		return EXIT_FAILURE;
	}
	
	return 0;
}
