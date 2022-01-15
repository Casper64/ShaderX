#include "pch.h"
#include "core.h"
#include "RenderWindow.h"
#include "shaders/ShaderLoader.h"

#include <imgui.h>



RenderWindow::RenderWindow()
{
	m_rectangle = Rectangle(-1.0f, -1.0f, 2.0f, 2.0f);
	m_rectangle.init(GL_STATIC_DRAW);
	std::string fragment;
	if (Application::get().getPath()[0] != '\0') {
		const char *path = Application::get().getPath();
		
		fragment = ShaderLoader::load(path);
	}
	else {
		fragment = standardFragment;
	}
	m_rectangle.shader = Shader(standardVertex, fragment);
}

RenderWindow::~RenderWindow()
{
}

void RenderWindow::render(glm::vec2 viewport, float time)
{
	m_rectangle.draw();
}

glm::vec2 RenderWindow::draw(uint32_t textureID, bool fullscreen)
{

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Render window", nullptr, flags);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	ImVec2 pos = ImGui::getWindowBeginPos();
	windowSize = glm::vec2(viewportPanelSize.x, viewportPanelSize.y);
	windowPos = glm::vec2(pos.x, pos.y);


	ImGui::Image((void *)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
	ImGui::PopStyleVar();
	return glm::vec2(viewportPanelSize.x, viewportPanelSize.y);
}

void RenderWindow::setFragmentShader(std::string& fragment)
{
	m_rectangle.shader = Shader(standardVertex, fragment);

}