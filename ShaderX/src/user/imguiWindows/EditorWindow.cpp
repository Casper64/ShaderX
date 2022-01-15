#include "pch.h"
#include "EditorWindow.h"
#include "imguiWindows/LogWindow.h"


#include <imgui.h>

EditorWindow::EditorWindow()
{
	auto lang = TextEditor::LanguageDefinition::GLSL();
	m_editor.SetLanguageDefinition(lang);
	//m_editor.SetPalette(TextEditor::Get());
	m_editor.SetShowWhitespaces(false);
}

EditorWindow::~EditorWindow()
{
}

void EditorWindow::draw(bool fullscreen)
{
	ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Shader editor", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

	m_editor.Render("Shader Editor", fullscreen);

	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(2);

	/*
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
	ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	if (!LogWindow::success) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	ImGui::Begin("Shader m_editor", NULL, window_flags);
	static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
	ImGui::InputTextMultiline("##source", m_shaderSource, IM_ARRAYSIZE(m_shaderSource), ImVec2(-FLT_MIN, ImGui::GetWindowHeight() ), flags);
	ImGui::End();

	if (!LogWindow::success) ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(2);
	*/
}

void EditorWindow::setShaderSource(std::string &source)
{
	//const char *str = source.c_str();
	//strcpy_s(m_shaderSource, str);
	sourceCode = source;
	m_editor.SetText(sourceCode);
}