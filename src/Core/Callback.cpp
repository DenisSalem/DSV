#include "DSV/Core/Callback.hpp"

namespace DSV {
	namespace Core {
	  	Callback::Callback(VkInstance pInstance, VkDebugReportFlagsEXT flags, PFN_vkDebugReportCallbackEXT pfnCallback) : Callback(pInstance, flags, pfnCallback, nullptr) {}

		Callback::Callback(VkInstance pInstance, VkDebugReportFlagsEXT flags, PFN_vkDebugReportCallbackEXT pfnCallback, VkAllocationCallbacks * pAllocationCallbacks) : RessourceManager(
			(PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(pInstance, "vkCreateDebugReportCallbackEXT"),
			(PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(pInstance, "vkDestroyDebugReportCallbackEXT")
		){
		  	m_pInstance = pInstance;
		  	m_msgFailedToCreate = DSV_MSG_FAILED_TO_CREATE_CALLBACK;

			m_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			m_createInfo.flags = flags;
			m_createInfo.pfnCallback = pfnCallback;

			Create();
		}
	}
}
