#include "DSV/VulkanApplication.hpp"

class FirstVulkanApplication : public DSV::VulkanApplication {
	public:
		FirstVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) : VulkanApplication(applicationName, engineName, applicationVersion, engineVersion) {
			std::cout << "Vulkan Application Created...\n";
		};
		
		~FirstVulkanApplication() {
			std::cout << "Then destroyed.\n";
		};
		
		void Run() {};
};
	
int main(int argc, char ** argv) {
	try {
		FirstVulkanApplication app("moo" , "foo", VK_MAKE_VERSION(0,0,0), VK_MAKE_VERSION(0,0,0));
		DSV::PrintInstanceLayers(DSV::GetInstanceLayers());
		app.InitVulkan(std::vector<const char *>(0));
	} catch (const std::runtime_error& e) {
        	std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return 0;
}
