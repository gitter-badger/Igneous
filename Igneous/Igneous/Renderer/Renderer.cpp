#include "Renderer.h"

#include <iostream>
#include <bgfx/platform.h>

#include "Display\Display.h"

bool Renderer::Init()
{
	width = 800;
	height = 600;

	Display::Init(width, height, "Test");

	bgfx::Init init;

	init.type = bgfx::RendererType::Count;
	init.vendorId = BGFX_PCI_ID_NONE;
	init.deviceId = 0;
	init.debug = true;
	init.profile = true;
	init.resolution.width = width;
	init.resolution.height = height;
	init.resolution.reset = BGFX_RESET_MSAA_X4; //BGFX_RESET_*

	if (bgfx::init(init))
	{
		caps = bgfx::getCaps();
		bgfx::setDebug(BGFX_DEBUG_TEXT);
		bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
		);
		return true;
	}
	else
	{
		std::cerr << "Failed to init bgfx!" << std::endl;
		return false;
	}
}

std::string Renderer::GetGLFWVersion() { return glfwGetVersionString(); }
std::string Renderer::GetGLMVersion() { return std::to_string(GLM_VERSION_MAJOR) + "." + std::to_string(GLM_VERSION_MINOR) + "." + std::to_string(GLM_VERSION_PATCH); }
std::string Renderer::GetbgfxVersion() { return std::to_string(BGFX_API_VERSION); }
std::string Renderer::GetRenderer() { return bgfx::getRendererName(caps->rendererType); }

std::string Renderer::GetSupportedRenderers()
{
	std::string supportedRenderers = "Supported Renderers: ";
	bgfx::RendererType::Enum rendererTypes[bgfx::RendererType::Count];
	uint8_t num = bgfx::getSupportedRenderers(bgfx::RendererType::Count, rendererTypes);

	for (size_t i = 0; i < num; i++)
	{
		supportedRenderers += bgfx::getRendererName(rendererTypes[i]);
		supportedRenderers += i != num - 1 ? ", " : "";
	}

	return supportedRenderers;
}

std::string Renderer::GetVendor(uint16_t vendorId)
{
	std::string vendorName;

	switch (vendorId)
	{
	case BGFX_PCI_ID_NONE:
		vendorName = "Autoselect adapter";
		break;
	case BGFX_PCI_ID_SOFTWARE_RASTERIZER:
		vendorName = "Software rasterizer";
		break;
	case BGFX_PCI_ID_AMD:
		vendorName = "AMD adapter";
		break;
	case BGFX_PCI_ID_INTEL:
		vendorName = "Intel adapter";
		break;
	case BGFX_PCI_ID_NVIDIA:
		vendorName = "nVidia adapter";
		break;
	default:
		vendorName = "Unknown Vendor";
		break;
	}

	return vendorName;
}

std::string Renderer::GetGpuInfo()
{
	std::string gpuInfo = "Num GPUs: " + std::to_string(caps->numGPUs) + " | Selected GPU Device ID: " + std::to_string(caps->deviceId) + "\n";
	std::string isSelected;
	
	for (std::size_t i = 0; i < caps->numGPUs; i++)
	{
		isSelected = caps->deviceId == caps->gpu[i].deviceId ? "(Selected)" : "";
		gpuInfo += "GPU[" + std::to_string(i) + "]" + isSelected + " | Vendor: " + GetVendor(caps->gpu[i].vendorId) + " | Device ID: " + std::to_string(caps->gpu[i].deviceId) + "\n";
	}

	return gpuInfo;
}


void Renderer::BindTexture(unsigned int unit, Texture::Texture texture)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture.id);
}

void Renderer::Render(Model* model)
{
	glBindVertexArray(model->mesh->vao);
	glDrawElements(GL_TRIANGLES, model->mesh->num_verticies, GL_UNSIGNED_INT, 0);
}

void Renderer::Update()
{
	bgfx::touch(0);
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x0f, std::to_string(Display::fps).c_str());
	bgfx::frame();
}

void Renderer::Terminate()
{
	bgfx::shutdown();
	Display::Terminate();
}

int Renderer::width;
int Renderer::height;
const bgfx::Caps* Renderer::caps;