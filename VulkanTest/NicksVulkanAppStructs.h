#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <array>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

////////////////////////////////
// HELPER STRUCTS:
////////////////////////////////

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;
	int transferFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0 && transferFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

//we're just dealing with simple, 2D math for now
struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	// this tells Vulkan how our vertex data is formatted
	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;


		return bindingDescription;
	}

	// tell vulkan how to handle our vertex struct as input
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; // gpu uses same format for vector2 vert pos - vec2.xy as rg color 32 - vec2.xy
		attributeDescriptions[0].offset = offsetof(Vertex, pos); // how far along the struct it is in bits or bytes.

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1; // colour is [ [vert at 0,color at 1] at 0, [vert at 0 color at 1] at 1 ]
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT; // vec3.xyz using float32 is same as vec3.rgb using float32 according to the gpu's memory.
		attributeDescriptions[1].offset = offsetof(Vertex, color); // how far along the struct it is in bits or bytes...

		return attributeDescriptions;
	}
};

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};