#include "DSV/Core.hpp"

const std::vector<const char *> requiredInstanceExtensions {"VK_EXT_debug_report"};
const std::vector<const char *> requiredInstanceLayers {"VK_LAYER_LUNARG_standard_validation"};

int main(int argc, char ** argv) {
	try {
		// We first check if both required instance extensions and instance layers are available.
		DSV::Core::AssertInstanceExtensionsAreAvailable(requiredInstanceExtensions);
		DSV::Core::AssertInstanceLayersAreAvailable(requiredInstanceLayers);

		DSV::Core::Instance * instance = new DSV::Core::Instance(
			"Hello App",			// Application Name 
			VK_MAKE_VERSION(1, 0, 0),	// Application Version
			"No Engine",			// Engine Name
			VK_MAKE_VERSION(1, 0, 0),	// Engine Version
			requiredInstanceExtensions,	// Required Instance Extensions
			requiredInstanceLayers		// Required Instance Layers
		);

		DSV::Core::Callback * callback = new DSV::Core::Callback(instance->GetHandler(), DSV_CALLBACK_REPORT_ALL, DSV::Core::DefaultDebugCallback);

		delete instance;
		delete callback;

	} catch (const DSV::Core::Exception& e) {
		return EXIT_FAILURE;
	}
	
	return 0;
}
