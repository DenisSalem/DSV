#include "DSV/GraphicVulkanApplication.hpp"

namespace DSV {
	VkSurfaceFormatKHR GetSurfaceFormat(std::vector<VkSurfaceFormatKHR> formats, VkFormat requiredFormat) {
		for (const auto current : formats) {
			if (current.format == requiredFormat) {
				return current;
			}
		}
		throw Exception(DSV_UNKNOWN_FORMAT, DSV_MSG_UNKNOWN_FORMAT);
	}

	VkPresentModeKHR GetSurfacePresentMode(std::vector<VkPresentModeKHR> presentModes, VkPresentModeKHR requiredPresentMode) {
		for (const auto current : presentModes) {
			if (current == requiredPresentMode) {
				return current;
			}
		}
		throw Exception(DSV_UNKNOWN_PRESENT_MODE, DSV_MSG_UNKNOWN_PRESENT_MODE);
	}

	GraphicVulkanApplication::GraphicVulkanApplication(const char * applicationName, const char * engineName, uint32_t applicationVersion, uint32_t engineVersion) : VulkanApplication(applicationName,engineName,applicationVersion,engineVersion) {
		m_pSwapChain = nullptr;
		m_pSurface = nullptr;
                m_pVertexShader = nullptr;
                m_pFragmentShader = nullptr;
		m_pPipelineLayout = nullptr;
		m_pRenderPass = nullptr;
		m_pPipeline = nullptr;
		m_pImageViews = std::vector<VkImageView>(0);
                m_pSwapChainImages = std::vector<VkImage>(0);
		m_vertexShader = std::vector<char>(0);
		m_fragmentShader = std::vector<char>(0);
		m_stagesCreateInfos = std::vector<VkPipelineShaderStageCreateInfo>(0);
		m_pSwapChainFramebuffers = std::vector<VkFramebuffer>(0);
		m_framebufferCreateInfos = std::vector<VkFramebufferCreateInfo>(0);
		
		m_surfaceFormat = {};
		m_surfacePresentMode = {};
		m_surfaceExtent = {};
		m_swapChainCreateInfo = {};
		m_vertShaderStageInfo = {};
		m_fragShaderStageInfo = {};
		m_vertexInputInfo = {};
		m_inputAssembly = {};
		m_viewportState = {};
		m_viewport = {};
		m_scissor = {};
		m_rasterizerState= {};
		m_multisamplingState = {};
		m_depthStencil = {};
		m_colorBlendAttachment = {};
		m_colorBlendingState = {};
		m_pipelineLayoutCreateInfo = {};
		m_colorAttachment = {};
		m_colorAttachmentRef = {};
		m_subpass = {};
		m_renderPassCreateInfo = {};
	  	m_pipelineCreateInfo = {};

		m_imageViewsCreateInfo = std::vector<VkImageViewCreateInfo>(0);
	};

	GraphicVulkanApplication::~GraphicVulkanApplication() {
	  	for (size_t i = 0; i < m_pSwapChainFramebuffers.size(); i++) {
			if (m_pSwapChainFramebuffers[i] != nullptr) {
				vkDestroyFramebuffer(m_pDevice, m_pSwapChainFramebuffers[i], nullptr);
			}
		}

	  	if(m_pPipeline != nullptr) {
			vkDestroyPipeline(m_pDevice, m_pPipeline, nullptr);
		}
		
		if(m_pRenderPass != nullptr) {
			vkDestroyRenderPass(m_pDevice, m_pRenderPass, nullptr);
		}

		if(m_pPipelineLayout != nullptr) {
			vkDestroyPipelineLayout(m_pDevice,m_pPipelineLayout, nullptr);
		}

		if(m_pFragmentShader != nullptr) {
			vkDestroyShaderModule(m_pDevice, m_pFragmentShader, nullptr);
		}
		if(m_pVertexShader != nullptr) {
			vkDestroyShaderModule(m_pDevice, m_pVertexShader, nullptr);
		}

		for (size_t i = 0; i < m_pImageViews.size(); i++) {
			vkDestroyImageView(m_pDevice, m_pImageViews[i], nullptr);
		}

		if (m_pSwapChain != nullptr) {
			vkDestroySwapchainKHR(m_pDevice, m_pSwapChain,nullptr);
		}
		if (m_pSurface != nullptr) {
			vkDestroySurfaceKHR(m_pInstance, m_pSurface, nullptr);
		}
	}

	VkSurfaceCapabilitiesKHR GraphicVulkanApplication::GetSurfaceCapabilities(int physicalDeviceIndex) {
		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &surfaceCapabilities);
		if (result != VK_SUCCESS) {
			throw Exception(result, DSV_MSG_CANNOT_RETRIEVE_SURFACE_CAPABILITIES);
		}
		return surfaceCapabilities;
	}

	std::vector<VkSurfaceFormatKHR> GraphicVulkanApplication::GetSurfaceFormats(int physicalDeviceIndex) {
		uint32_t formatCount;
		std::vector<VkSurfaceFormatKHR> surfaceFormats(0);
		vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &formatCount, nullptr);
		if (formatCount != 0) {
			surfaceFormats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &formatCount, surfaceFormats.data());
			return surfaceFormats;
		}
		return std::vector<VkSurfaceFormatKHR>(0);
	}

	std::vector<VkPresentModeKHR> GraphicVulkanApplication::GetSurfacePresentModes(int physicalDeviceIndex) {
		uint32_t presentModeCount;
		std::vector<VkPresentModeKHR> surfacePresentModes(0);
		vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
    			surfacePresentModes.resize(presentModeCount);
    			vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevices.at(physicalDeviceIndex), m_pSurface, &presentModeCount, surfacePresentModes.data());
			return surfacePresentModes;
		}
		return std::vector<VkPresentModeKHR>(0);
	}

	void GraphicVulkanApplication::SwapChainDefaultSetup(VkSurfaceCapabilitiesKHR capabilities, VkSurfaceFormatKHR format, VkPresentModeKHR presentMode, VkExtent2D extent) {
		m_surfaceFormat = format;
		m_surfacePresentMode = presentMode;
		m_surfaceExtent = extent;

		uint32_t imageCount = capabilities.minImageCount + 1;
		
		if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
			imageCount = capabilities.maxImageCount;
		}

		m_swapChainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		m_swapChainCreateInfo.surface = m_pSurface;
		m_swapChainCreateInfo.minImageCount = imageCount;
		m_swapChainCreateInfo.imageFormat = m_surfaceFormat.format;
		m_swapChainCreateInfo.imageColorSpace = m_surfaceFormat.colorSpace;
		m_swapChainCreateInfo.imageExtent = m_surfaceExtent;

		m_swapChainCreateInfo.imageArrayLayers = 1;
		m_swapChainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		m_swapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		m_swapChainCreateInfo.queueFamilyIndexCount = 0;
		m_swapChainCreateInfo.pQueueFamilyIndices = nullptr;
		m_swapChainCreateInfo.preTransform = capabilities.currentTransform;
		m_swapChainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		m_swapChainCreateInfo.presentMode = m_surfacePresentMode;
		m_swapChainCreateInfo.clipped = VK_TRUE;
		m_swapChainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	}

	void GraphicVulkanApplication::CreateSwapChain() {
		VkResult result = vkCreateSwapchainKHR(m_pDevice, &m_swapChainCreateInfo, nullptr, &m_pSwapChain);

		if (result != VK_SUCCESS) {
			throw(result, DSV_MSG_FAILED_TO_CREATE_SWAPCHAIN);
		}

                uint32_t imageCount = 0;
                vkGetSwapchainImagesKHR(m_pDevice, m_pSwapChain, &imageCount, nullptr);
                m_pSwapChainImages.resize(imageCount);
		m_imageViewsCreateInfo.resize(imageCount);
                vkGetSwapchainImagesKHR(m_pDevice, m_pSwapChain, &imageCount, m_pSwapChainImages.data());
                m_pImageViews.resize(m_pSwapChainImages.size(), nullptr);
	}

        void GraphicVulkanApplication::ImageViewsDefaultSetup() {
                for(uint32_t i = 0; i < m_pImageViews.size(); i++) {
			m_imageViewsCreateInfo[i] = {};
			m_imageViewsCreateInfo[i].sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			m_imageViewsCreateInfo[i].image = m_pSwapChainImages[i];
			m_imageViewsCreateInfo[i].viewType = VK_IMAGE_VIEW_TYPE_2D;
			m_imageViewsCreateInfo[i].format = m_surfaceFormat.format;
			m_imageViewsCreateInfo[i].components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			m_imageViewsCreateInfo[i].components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			m_imageViewsCreateInfo[i].components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			m_imageViewsCreateInfo[i].components.a = VK_COMPONENT_SWIZZLE_IDENTITY; 
			m_imageViewsCreateInfo[i].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			m_imageViewsCreateInfo[i].subresourceRange.baseMipLevel = 0;
			m_imageViewsCreateInfo[i].subresourceRange.levelCount = 1;
			m_imageViewsCreateInfo[i].subresourceRange.baseArrayLayer = 0;
			m_imageViewsCreateInfo[i].subresourceRange.layerCount = 1;
                }
        }

	void GraphicVulkanApplication::LoadShaders(const char * vertexShaderFilename, const char * fragmentShaderFilename) {
		std::ifstream vertexShader(vertexShaderFilename, std::ios::ate | std::ios::binary); 
		std::ifstream fragmentShader(fragmentShaderFilename, std::ios::ate | std::ios::binary);

		if(!vertexShader.is_open()) {
			throw(DSV_FAILED_TO_LOAD_VERTEX_SHADER, DSV_MSG_FAILED_TO_LOAD_VERTEX_SHADER);
		}
		if(!fragmentShader.is_open()) {
			throw(DSV_FAILED_TO_LOAD_VERTEX_SHADER, DSV_MSG_FAILED_TO_LOAD_VERTEX_SHADER);
		}

		size_t vertexShaderSize = (size_t) vertexShader.tellg();
		size_t fragmentShaderSize = (size_t) fragmentShader.tellg();

		vertexShader.seekg(0);
		fragmentShader.seekg(0);

		m_vertexShader.resize(vertexShaderSize);
		m_fragmentShader.resize(fragmentShaderSize);

		vertexShader.read(m_vertexShader.data(), vertexShaderSize);
		fragmentShader.read(m_fragmentShader.data(), fragmentShaderSize);
		vertexShader.close();
		fragmentShader.close();
	}

	void GraphicVulkanApplication::CreateVertexShader() {
		CreateShader(m_vertexShader, &m_pVertexShader);
	}

	void GraphicVulkanApplication::CreateFragmentShader() {
		CreateShader(m_fragmentShader, &m_pFragmentShader);
	}

	void GraphicVulkanApplication::CreateVertexShaderStage() {
		CreateDefaultShaderStage(&m_vertShaderStageInfo, VK_SHADER_STAGE_VERTEX_BIT, m_pVertexShader);
	}

	void GraphicVulkanApplication::CreateFragmentShaderStage() {
		CreateDefaultShaderStage(&m_fragShaderStageInfo, VK_SHADER_STAGE_FRAGMENT_BIT, m_pFragmentShader);
	}

	void GraphicVulkanApplication::CreateShader(std::vector<char> shader, VkShaderModule * shaderModule) {
		VkShaderModuleCreateInfo shaderCreateInfo = {};
		shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderCreateInfo.codeSize = shader.size();
		std::vector<uint32_t> aligned(shader.size() / sizeof(uint32_t) + 1);
		memcpy(aligned.data(), shader.data(), shader.size());
		shaderCreateInfo.pCode = aligned.data();

		VkResult result = vkCreateShaderModule(m_pDevice, &shaderCreateInfo, nullptr, shaderModule);
		if(result != VK_SUCCESS) {
			throw Exception(result, DSV_MSG_FAILED_TO_CREATE_SHADER);
		}
        }

	void GraphicVulkanApplication::CreateDefaultShaderStage(VkPipelineShaderStageCreateInfo * stageInfo, VkShaderStageFlagBits flag, VkShaderModule shaderModule) {
		stageInfo->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stageInfo->pName = "main";
		stageInfo->stage = flag;
		stageInfo->module = shaderModule;
	}

	void GraphicVulkanApplication::DefaultFixedFunctions(VkPrimitiveTopology topology, VkPolygonMode polygonMode) {
		m_vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		
		m_inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		m_inputAssembly.topology = topology;
		m_inputAssembly.primitiveRestartEnable = VK_FALSE;

		m_viewport.x = 0.0f;
		m_viewport.y = 0.0f;

		m_viewport.width = (float) m_surfaceExtent.width;
		m_viewport.height = (float) m_surfaceExtent.height;
		m_viewport.minDepth = 0.0f;
		m_viewport.maxDepth = 1.0f;

		m_scissor.offset = {0,0};
		m_scissor.extent = m_surfaceExtent;

		m_viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		m_viewportState.viewportCount = 1;
		m_viewportState.pViewports = &m_viewport;
		m_viewportState.scissorCount = 1;
		m_viewportState.pScissors = &m_scissor;

		m_rasterizerState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		m_rasterizerState.depthClampEnable = VK_FALSE;
		m_rasterizerState.rasterizerDiscardEnable = VK_FALSE;
		m_rasterizerState.polygonMode = polygonMode;
		m_rasterizerState.lineWidth = 1.0f;
		m_rasterizerState.cullMode = VK_CULL_MODE_BACK_BIT;
		m_rasterizerState.frontFace = VK_FRONT_FACE_CLOCKWISE;
		m_rasterizerState.depthBiasEnable = VK_FALSE;
		m_rasterizerState.depthBiasConstantFactor = 0.0f;
		m_rasterizerState.depthBiasClamp = 0.0f;
		m_rasterizerState.depthBiasSlopeFactor = 0.0f;

		m_multisamplingState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		m_multisamplingState.sampleShadingEnable = VK_FALSE;
		m_multisamplingState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		m_multisamplingState.minSampleShading = 1.0f;
		m_multisamplingState.pSampleMask = nullptr;
		m_multisamplingState.alphaToCoverageEnable = VK_FALSE;
		m_multisamplingState.alphaToOneEnable = VK_FALSE;

		m_colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		m_colorBlendAttachment.blendEnable = VK_TRUE;
		m_colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		m_colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		m_colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		m_colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		m_colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		m_colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

		m_colorBlendingState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		m_colorBlendingState.logicOpEnable = VK_FALSE;
		m_colorBlendingState.logicOp = VK_LOGIC_OP_COPY;
		m_colorBlendingState.attachmentCount = 1;
		m_colorBlendingState.pAttachments = &m_colorBlendAttachment;
		m_colorBlendingState.blendConstants[0] = 0.0f;
		m_colorBlendingState.blendConstants[1] = 0.0f;
		m_colorBlendingState.blendConstants[2] = 0.0f;
		m_colorBlendingState.blendConstants[3] = 0.0f;
	}

	void GraphicVulkanApplication::CreateDefaultPipelineLayout() {
		m_pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		m_pipelineLayoutCreateInfo.setLayoutCount = 0;
		m_pipelineLayoutCreateInfo.pSetLayouts = nullptr;
		m_pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
		m_pipelineLayoutCreateInfo.pPushConstantRanges = 0;

		VkResult result = vkCreatePipelineLayout(m_pDevice, &m_pipelineLayoutCreateInfo, nullptr, &m_pPipelineLayout);
		if( result!= VK_SUCCESS) {
    			throw Exception(result, DSV_MSG_FAILED_TO_CREATE_PIPELINE_LAYOUT);
		}	
	}

	void GraphicVulkanApplication::CreateDefaultRenderPass() {
		m_colorAttachment.format = m_surfaceFormat.format;
    		m_colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    		m_colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		m_colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		m_colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		m_colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		m_colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		m_colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		m_colorAttachmentRef.attachment = 0;
		m_colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		
		m_subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		m_subpass.colorAttachmentCount = 1;
		m_subpass.pColorAttachments = &m_colorAttachmentRef;
		
		
		m_renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		m_renderPassCreateInfo.attachmentCount = 1;
		m_renderPassCreateInfo.pAttachments = &m_colorAttachment;
		m_renderPassCreateInfo.subpassCount = 1;
		m_renderPassCreateInfo.pSubpasses = &m_subpass;

		VkResult result = vkCreateRenderPass(m_pDevice, &m_renderPassCreateInfo, nullptr, &m_pRenderPass);
		if(result != VK_SUCCESS) {
			throw Exception(result, DSV_MSG_FAILED_TO_CREATE_RENDER_PASS);
		}
	}

	void GraphicVulkanApplication::CreateDefaultPipeline() {
	  	m_stagesCreateInfos.push_back(m_vertShaderStageInfo);
	  	m_stagesCreateInfos.push_back(m_fragShaderStageInfo);
		
		m_pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		m_pipelineCreateInfo.stageCount = m_stagesCreateInfos.size();
		m_pipelineCreateInfo.pStages = m_stagesCreateInfos.data();

		m_pipelineCreateInfo.pVertexInputState = &m_vertexInputInfo;
		m_pipelineCreateInfo.pInputAssemblyState = &m_inputAssembly;
		m_pipelineCreateInfo.pViewportState = &m_viewportState;
		m_pipelineCreateInfo.pRasterizationState = &m_rasterizerState;
		m_pipelineCreateInfo.pMultisampleState = &m_multisamplingState;
		m_pipelineCreateInfo.pDepthStencilState = nullptr; 
		m_pipelineCreateInfo.pColorBlendState = &m_colorBlendingState;
		m_pipelineCreateInfo.pDynamicState = nullptr;

		m_pipelineCreateInfo.layout = m_pPipelineLayout;

		m_pipelineCreateInfo.renderPass = m_pRenderPass;
		m_pipelineCreateInfo.subpass = 0;

		m_pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
		m_pipelineCreateInfo.basePipelineIndex = -1;

		VkResult result = vkCreateGraphicsPipelines(m_pDevice, VK_NULL_HANDLE, 1, &m_pipelineCreateInfo, nullptr, &m_pPipeline);
		if (result != VK_SUCCESS) {
			throw Exception(result, DSV_MSG_FAILED_TO_CREATE_PIPELINE);
		}
	}

	void GraphicVulkanApplication::DefaultFramebuffersSetup() {
		m_pSwapChainFramebuffers.resize(m_pImageViews.size());
		m_framebufferCreateInfos.resize(m_pImageViews.size());

		for (size_t i = 0; i < m_pImageViews.size(); i++) {
			m_framebufferCreateInfos[i] = {};
			m_framebufferCreateInfos[i].sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			m_framebufferCreateInfos[i].renderPass = m_pRenderPass;
			m_framebufferCreateInfos[i].attachmentCount = 1;
			m_framebufferCreateInfos[i].pAttachments = &m_pImageViews[i];
			m_framebufferCreateInfos[i].width = m_surfaceExtent.width;
			m_framebufferCreateInfos[i].height = m_surfaceExtent.height;
			m_framebufferCreateInfos[i].layers = 1;
		}
	}

	void GraphicVulkanApplication::CreateFramebuffers() {
		for(size_t i = 0; i < m_framebufferCreateInfos.size(); i++) {
			VkResult result = vkCreateFramebuffer(m_pDevice, &m_framebufferCreateInfos[i], nullptr, &m_pSwapChainFramebuffers[i]);
			if (result != VK_SUCCESS) {
				throw Exception(result, DSV_MSG_FAILED_TO_CREATE_FRAMEBUFFERS);
			}
		}
	}

	void GraphicVulkanApplication::CreateImageViews() {
		VkResult result;
                for(uint32_t i = 0; i < m_pImageViews.size(); i++) {
			result = vkCreateImageView(m_pDevice, &m_imageViewsCreateInfo[i], nullptr, &m_pImageViews[i]);
			if (result != VK_SUCCESS) {
				throw Exception(result, DSV_MSG_FAILED_TO_CREATE_IMAGE_VIEW);
			}
		}
	}

	VkSurfaceKHR GraphicVulkanApplication::GetSurface() {
		return m_pSurface;
	}
}
