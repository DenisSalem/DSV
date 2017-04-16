#include "DSV/VulkanApplication.hpp"

#define EXAMPLE_DEBUG

#ifdef EXAMPLE_DEBUG
const std::vector<const char *> requiredInstanceExtensions {"VK_EXT_debug_report"};
const std::vector<const char *> requiredInstanceLayers {"VK_LAYER_LUNARG_standard_validation"};
#else
const std::vector<const char *> requiredInstanceExtensions {};
const std::vector<const char *> requiredInstanceLayers {};
#endif

// Define custom DSV::VulkanApplication
class FirstVulkanApplication : public DSV::VulkanApplication {
	public:
		FirstVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) : VulkanApplication(applicationName, engineName, applicationVersion, engineVersion) {
			std::cout << "Vulkan application created.\n";
		};
		
		~FirstVulkanApplication() {
			std::cout << "Vulkan application destroyed.\n";
		};
		
		void Run() {};

	private:
};

// Define custom debug callback 
VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objType,
    uint64_t obj,
    size_t location,
    int32_t code,
    const char* layerPrefix,
    const char* msg,
    void* userData) {

    std::cerr << "validation layer: " << msg << std::endl;

    return VK_FALSE;
}

int main(int argc, char ** argv) {
	try {
	  	// Instancing but not initiating yet...
		FirstVulkanApplication app("FirstVulkanApplication" , "None", VK_MAKE_VERSION(0,0,0), VK_MAKE_VERSION(0,0,0));
		
		// Printing out layers and extensions capabilities...
		DSV::PrintInstanceLayers(DSV::GetInstanceLayers());
		DSV::PrintInstanceExtensions(DSV::GetInstanceExtensions(nullptr));

		// Initiating...
		if ( DSV::IsInstanceLayersAvailable(requiredInstanceLayers) && DSV::IsInstanceExtensionsAvailable(requiredInstanceExtensions)) {
			#ifdef EXAMPLE_DEBUG
				app.InitVulkan(requiredInstanceExtensions,requiredInstanceLayers);
				app.SetupCallback(VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, debugCallback);
			#else
				app.InitVulkan();
			#endif
			app.PrintPhysicalDevices();

			// This is where you should do something with...
			
			app.GetPhysicalDevices();
			int physicalDevice = 0;	// 0 is the default for the example. For real application you should choose wisely.
			
			app.GetQueueFamilies(physicalDevice);
			int queueFamily = 0; // 0 is the default for the example. For real application you should choose wisely.

			app.CreateLogicalDevice(physicalDevice,queueFamily,1,1.0);
		}
		else {
			std::cout << "Required layers or extensions aren't supported... :(\n";
		}
	} catch (const DSV::Exception& e) {
        	std::cerr << "VK_RESULT: " << e.code << std::endl;
        	std::cerr << e.msg << std::endl;
		return EXIT_FAILURE;
	}
	
	return 0;
}
