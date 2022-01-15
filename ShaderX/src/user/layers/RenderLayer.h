#pragma once
#include "core.h"
#include <glm/vec2.hpp>
#include "imguiWindows/EditorWindow.h"
#include "imguiWindows/RenderWindow.h"
#include "imguiWindows/LogWindow.h"
#include "shaders/UniformController.h"

class RenderLayer : public Layer
{
public:
	RenderLayer();
	~RenderLayer();

	void on_attach() override;
	void on_detach() override;

	void on_update(float time) override;
	void on_imgui_render() override;
	glm::vec2 m_ViewportSize = { 100.0f, 100.0f };
	bool fullscreen = false;


private:
	Framebuffer *m_framebuffer;
	EditorWindow *m_editor;
	RenderWindow *m_renderWindow;
	LogWindow *m_logWindow;
	UniformController *m_uniformController;

private:
	void showMenu();
	
	
};

