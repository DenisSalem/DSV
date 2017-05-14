#ifndef DSV_GRAPHIC_VULKAN_APPLICATION
#define DSV_GRAPHIC_VULKAN_APPLICATION

#include <fstream>
#include "DSV/VulkanApplication.hpp"

#define DSV_MSG_FAILED_TO_CREATE_WINDOW_SURFACE "DSV: Failed to create window surface!"
#define DSV_MSG_CANNOT_RETRIEVE_SURFACE_CAPABILITIES "DSV: Cannot retrieve surface capabilities!"
#define DSV_MSG_FAILED_TO_CREATE_SWAPCHAIN "DSV: Failed to create swapchain!"
#define DSV_MSG_FAILED_TO_CREATE_IMAGE_VIEW "DSV: Failed to create image view!"
#define DSV_MSG_UNKNOWN_FORMAT "DSV: Unknown format!"
#define DSV_MSG_UNKNOWN_PRESENT_MODE "DSV: Unknown present mode!"
#define DSV_MSG_FAILED_TO_LOAD_VERTEX_SHADER "DSV: Failed to load vertex shader!"
#define DSV_MSG_FAILED_TO_LOAD_FRAGMENT_SHADER "DSV: Failed to load fragment shader!"
#define DSV_MSG_FAILED_TO_CREATE_SHADER "DSV: Failed to create shader!"
#define DSV_MSG_FAILED_TO_CREATE_PIPELINE_LAYOUT "DSV: Failed to create pipeline layout!"
#define DSV_MSG_FAILED_TO_CREATE_RENDER_PASS "DSV: Failed to create render pass!"
#define DSV_MSG_FAILED_TO_CREATE_PIPELINE "DSV: Failed to create pipeline!"
#define DSV_MSG_FAILED_TO_CREATE_FRAMEBUFFERS "DSV: Failted to create framebuffers!"

#define DSV_UNKNOWN_FORMAT 3
#define DSV_UNKNOWN_PRESENT_MODE 4
#define DSV_FAILED_TO_LOAD_VERTEX_SHADER 5
#define DSV_FAILED_TO_LOAD_FRAGMENT_SHADER 6

namespace DSV {
	VkSurfaceFormatKHR GetSurfaceFormat(std::vector<VkSurfaceFormatKHR> formats, VkFormat requiredFormat);
	VkPresentModeKHR GetSurfacePresentMode(std::vector<VkPresentModeKHR>, VkPresentModeKHR requiredPresentMode);
	class GraphicVulkanApplication : public VulkanApplication {
		public:
			GraphicVulkanApplication() : GraphicVulkanApplication("Generic DSV Vulkan Application","No Engine",VK_MAKE_VERSION(1,0,0),VK_MAKE_VERSION(1,0,0)) {};
			GraphicVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion); 
			~GraphicVulkanApplication();


			VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(int physicalDeviceIndex);
			std::vector<VkSurfaceFormatKHR> GetSurfaceFormats(int physicalDeviceIndex);
			std::vector<VkPresentModeKHR> GetSurfacePresentModes(int physicalDeviceIndex);
			VkSurfaceKHR GetSurface();

			void SwapChainDefaultSetup(VkSurfaceCapabilitiesKHR capabilities, VkSurfaceFormatKHR format, VkPresentModeKHR presentMode, VkExtent2D extent);
			void ImageViewsDefaultSetup();
                        void CreateSwapChain();
			void CreateImageViews();
                        void LoadShaders(const char * vertexShaderFilename, const char * fragmentShaderFilename);
			void CreateVertexShader();
			void CreateFragmentShader();
			void CreatePipeline();
			void CreateVertexShaderStage();
			void CreateFragmentShaderStage();
			void CreateDefaultShaderStage(VkPipelineShaderStageCreateInfo * stageInfo, VkShaderStageFlagBits flag, VkShaderModule shaderModule);
			void DefaultFixedFunctions(VkPrimitiveTopology topology, VkPolygonMode polygonMode);
			void CreateDefaultPipelineLayout();
			void CreateDefaultRenderPass();
			void CreateDefaultPipeline();
			void DefaultFramebuffersSetup();
			void CreateFramebuffers();

		protected:
			void CreateShader(std::vector<char> shader, VkShaderModule * shaderModule);
			
			std::vector<VkPipelineShaderStageCreateInfo> m_stagesCreateInfos;
			
			VkGraphicsPipelineCreateInfo m_pipelineCreateInfo;
			VkPipelineShaderStageCreateInfo m_vertShaderStageInfo;
			VkPipelineShaderStageCreateInfo m_fragShaderStageInfo;
			VkPipelineVertexInputStateCreateInfo m_vertexInputInfo;
			VkPipelineInputAssemblyStateCreateInfo m_inputAssembly;
			VkPipelineViewportStateCreateInfo m_viewportState;
			VkPipelineRasterizationStateCreateInfo m_rasterizerState;
			VkPipelineMultisampleStateCreateInfo m_multisamplingState;
			VkPipelineDepthStencilStateCreateInfo m_depthStencil;
			VkPipelineColorBlendAttachmentState m_colorBlendAttachment;
			VkPipelineColorBlendStateCreateInfo m_colorBlendingState;
			VkPipelineLayoutCreateInfo m_pipelineLayoutCreateInfo;
			VkAttachmentDescription m_colorAttachment;
			VkAttachmentReference m_colorAttachmentRef;
			VkSubpassDescription m_subpass;
			VkRenderPass m_pRenderPass;
			VkRenderPassCreateInfo m_renderPassCreateInfo;

			VkPipelineLayout m_pPipelineLayout;

			VkViewport m_viewport;
			VkRect2D m_scissor;


			VkSwapchainCreateInfoKHR m_swapChainCreateInfo;
			VkSurfaceKHR m_pSurface;
			VkSurfaceFormatKHR m_surfaceFormat;
			VkPresentModeKHR m_surfacePresentMode;
			VkExtent2D m_surfaceExtent;
			VkSwapchainKHR m_pSwapChain;
                        VkShaderModule m_pVertexShader;
                        VkShaderModule m_pFragmentShader;
			VkPipeline m_pPipeline;
			std::vector<VkImage> m_pSwapChainImages;
			std::vector<VkFramebufferCreateInfo> m_framebufferCreateInfos;
                        std::vector<VkImageView> m_pImageViews;
			std::vector<VkImageViewCreateInfo> m_imageViewsCreateInfo;
			std::vector<char> m_vertexShader;
			std::vector<char> m_fragmentShader;
			std::vector<VkFramebuffer> m_pSwapChainFramebuffers;
	};
}

#endif
