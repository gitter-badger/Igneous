#include "Renderer.h"

#include <iostream>
#include <bgfx/bgfx.h>
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
		bgfx::setDebug(BGFX_DEBUG_TEXT);
		bgfx::setViewRect(0, 0, 0, uint16_t(width), uint16_t(height));
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
		);
		std::clog << bgfx::getRendererName(bgfx::getRendererType()) << std::endl;
		return true;
	}
	else
	{
		std::cerr << "Failed to init bgfx!" << std::endl;
		return false;
	}
}

std::string Renderer::GetGLADVersion() {return "0.1.16a0"; }
std::string Renderer::GetGLFWVersion() { return glfwGetVersionString(); }
std::string Renderer::GetGLMVersion() { return std::to_string(GLM_VERSION_MAJOR) + "." + std::to_string(GLM_VERSION_MINOR) + "." + std::to_string(GLM_VERSION_PATCH); }

std::string Renderer::GetExtensions()
{
	std::string extensions;
	GLint n;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	if (n > 0)
	{
		GLint i;
		for (i = 0; i < n; i++)
		{
			extensions += " ";
			extensions += (char*)glGetStringi(GL_EXTENSIONS, i);
		}
	}
	return extensions;
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