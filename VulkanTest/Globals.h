#pragma once


const int MAX_FRAMES_IN_FLIGHT = 2;

const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<Vertex> vertices = {
	{ { -0.5f,-0.5f },{ 1.0f,0.0f,0.0f } },
{ { 0.5f,-0.5f },{ 0.0f,1.0f,0.0f } },
{ { 0.5f, 0.5f },{ 0.0f,0.0f,1.0f } },
{ { -0.5f, 0.5f },{ 1.0f,1.0f,1.0f } } };

const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};