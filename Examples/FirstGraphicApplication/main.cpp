#include "DSV/GraphicVulkanApplication.hpp"
#include <GLFW/glfw3.h>

#define EXAMPLE_DEBUG

#ifdef EXAMPLE_DEBUG
std::vector<const char *> requiredInstanceExtensions {"VK_EXT_debug_report"};
const std::vector<const char *> requiredInstanceLayers {"VK_LAYER_LUNARG_standard_validation"};
#else
std::vector<const char *> requiredInstanceExtensions {};
const std::vector<const char *> requiredInstanceLayers {};
#endif

const std::vector<const char *> requiredDeviceExtensions {"VK_KHR_swapchain"};

// Define custom DSV::VulkanApplication
class FirstGraphicVulkanApplication : public DSV::GraphicVulkanApplication {
	public:
		FirstGraphicVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) : GraphicVulkanApplication(applicationName, engineName, applicationVersion, engineVersion) {
			std::cout << "Graphic vulkan application created.\n";
		};
		
		~FirstGraphicVulkanApplication() {
		  	if (m_pSurface != nullptr) {
				vkDestroySurfaceKHR(m_pInstance, m_pSurface, nullptr);
			}
			std::cout << "Graphic Vulkan application destroyed.\n";
		};

		void CreateSurface(GLFWwindow * window) {
			VkResult result = glfwCreateWindowSurface(m_pInstance, window, nullptr, &m_pSurface);
			if (result != VK_SUCCESS) {
				throw DSV::Exception(result, DSV_MSG_FAILED_TO_CREATE_WINDOW_SURFACE);
			}
		}
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
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		auto window = glfwCreateWindow(640, 480, "First graphic vulkan application", nullptr, nullptr);

	  	// Instancing but not initiating yet...
		FirstGraphicVulkanApplication app("FirstVulkanApplication" , "None", VK_MAKE_VERSION(0,0,0), VK_MAKE_VERSION(0,0,0));
		
		// Printing out layers and extensions capabilities...
		DSV::PrintLayers(DSV_MSG_AVAILABLE_INSTANCE_LAYERS, DSV::GetInstanceLayers());
		DSV::PrintExtensions(DSV_MSG_AVAILABLE_INSTANCE_EXTENSIONS, DSV::GetInstanceExtensions(nullptr));

		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (int i=0; i<glfwExtensionCount;i++) {
			requiredInstanceExtensions.push_back(glfwExtensions[i]);
		}

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
			DSV::PrintExtensions(DSV_MSG_AVAILABLE_DEVICE_EXTENSIONS, app.GetDeviceExtensions(physicalDevice, nullptr));
			
			app.GetQueueFamilies(physicalDevice);
			int queueFamily = 0; // 0 is the default for the example. For real application you should choose wisely.
			app.AddQueueFamily(queueFamily,3,std::vector<float>({0.70,0.15,0.15}));
			
			app.CreateLogicalDevice(physicalDevice,requiredDeviceExtensions);

			app.CreateSurface(window);

			VkSurfaceCapabilitiesKHR surfaceCapabilities = app.GetSurfaceCapabilities(physicalDevice);
			std::vector<VkSurfaceFormatKHR> formats = app.GetSurfaceFormats(physicalDevice);
		}
		else {
			std::cout << "Required layers or extensions aren't supported... :(\n";
		}
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
    		glfwDestroyWindow(window);
    		glfwTerminate();
	} catch (const DSV::Exception& e) {
        	std::cerr << e.msg << std::endl;
		return EXIT_FAILURE;
	}
	
	return 0;
}
