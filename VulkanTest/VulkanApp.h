#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <array>
#include "NicksVulkanAppStructs.h"


#pragma once
class VulkanApp
{
public:
	VulkanApp();
	~VulkanApp();
	void run();

	const int WIDTH = 800;
	const int HEIGHT = 600;

	const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	const std::vector<Vertex> vertices = {
		{ { -0.5f,-0.5f },{ 1.0f,0.0f,0.0f } },
	{ { 0.5f,-0.5f },{ 0.0f,1.0f,0.0f } },
	{ { 0.5f, 0.5f },{ 0.0f,0.0f,1.0f } },
	{ { -0.5f, 0.5f },{ 1.0f,1.0f,1.0f } } };

	const std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};

private:

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	GLFWwindow * window;

	VkInstance instance;
	VkDebugReportCallbackEXT callback;
	VkSurfaceKHR surface;

	VkPhysicalDevice physicalDevice;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkQueue transferQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;
	VkCommandPool transferQueueCommandPool;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	size_t currentFrame;


	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanupSwapChain();
	void cleanup();
	void drawFrame();
	void updateUniformBuffer(uint32_t currentImage);
	void createDescriptorPool();
	void createDescriptorSets();
	void createDescriptorSetLayout();
	void recreateSwapChain();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();
	void createUniformBuffer();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createSyncObjects();
	void createCommandBuffers();
	void createCommandPool();
	void createFramebuffers();
	void createRenderPass();
	void createGraphicsPipeline();
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createImageViews();
	void createSwapChain();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	std::vector<const char*> getRequiredExtensions();
	void createInstance();
	void createSurface();
	void createLogicalDevice();
	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void setupDebugCallback();
	bool checkValidationLayerSupport();
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags, // specifies the type of message
		VkDebugReportObjectTypeEXT objType, // specifies the type of object that the message is talking about
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg, // pointer to the message
		void* userData // this lets us pass our own data to the callback.
	);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	std::vector<char> readFile(const std::string& filename);

	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);

	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
};