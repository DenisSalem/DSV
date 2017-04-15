#include "DSV/VulkanApplication.hpp"

const std::vector<const char *> requiredInstanceExtensions {"VK_EXT_debug_report"};
const std::vector<const char *> requiredInstanceLayers {"VK_LAYER_LUNARG_standard_validation"};

// Define custom DSV::VulkanApplication
class FirstVulkanApplication : public DSV::VulkanApplication {
	public:
		FirstVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) : VulkanApplication(applicationName, engineName, applicationVersion, engineVersion) {
			std::cout << "Vulkan application created.\n";
		};
		
		~FirstVulkanApplication() {
			std::cout << "Vulkan applicaion destroyed.\n";
		};
		
		void Run() {};
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
			app.InitVulkan(requiredInstanceExtensions,requiredInstanceLayers);
			app.SetupCallback(VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, debugCallback);
			app.PrintPhysicalDevices();
			app.CreateLogicalDevice(500,1);
		}
		else {
			std::cout << "Required layers or extensions aren't supported... :(\n";
		}
	} catch (const DSV::Exception& e) {
        	std::cerr << "VK_RESULT: " << e.code << std::endl;
		return EXIT_FAILURE;
	}
	
	return 0;
}
