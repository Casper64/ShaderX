#include "pch.h"
#include "RenderLayer.h"
#include "imgui.h"
#include "shapes/Rectangle.h"
#include "shaders/ShaderLoader.h"

#include <glad/glad.h>

#include <codecvt>

void showOverlay();


RenderLayer::RenderLayer() 
	: Layer("ExampleLayer")
{
}

RenderLayer::~RenderLayer()
{
	delete m_editor;
	delete m_renderWindow;
	delete m_framebuffer;
	delete m_logWindow;
	delete m_uniformController;
}

void RenderLayer::on_attach()
{
	FramebufferSpecification specs;
	specs.Width = 640;
	specs.Height = 360;
	m_framebuffer = new Framebuffer(specs);

	m_editor = new EditorWindow();
	m_renderWindow = new RenderWindow();
	m_logWindow = new LogWindow();
	m_uniformController = new UniformController();

	std::string source = m_renderWindow->getFragmentCode();
	m_editor->setShaderSource(source);

	m_uniformController->set_from_source(source);
	m_uniformController->add_shape(m_renderWindow->get_rectangle());


	m_uniformController->set("iResolution", glm::vec2(specs.Width, specs.Height));
	m_uniformController->set("iTime", 0.0f);
	m_uniformController->set("iMouse", glm::vec2(0, 0));
}

void RenderLayer::on_detach()
{
}

void RenderLayer::on_imgui_render()
{
	static bool fullscreenContext = false;
	fullscreenContext = fullscreen;
	if (fullscreenContext) ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	// ------- Dockspace ------------------------------------------
	static bool dockspace = true;
	if (dockspace) {
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		dockspace_flags |= ImGuiDockNodeFlags_AutoHideTabBar;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		ImGuiViewport *viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		static bool *p_open = (bool *)true;
		ImGui::Begin("DockSpace Demo", p_open, window_flags);
		ImGui::PopStyleVar();

		ImGui::PopStyleVar(2);

		//Dockspace
		ImGuiIO &io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		showMenu();
		ImGui::End();
		ImGui::PopStyleColor(2);
	}
	// ------- Editor stuff --------------------------------------
	if (fullscreenContext) {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	}

	m_editor->draw(fullscreenContext);
	m_logWindow->draw();

	if (fullscreenContext) {
		ImGui::PopStyleColor(4);
	}

	// ------- Render Window -------------------------------------
	if (!fullscreenContext) {
		glm::vec2 viewportPanelSize = m_renderWindow->draw(m_framebuffer->get_color_attachment_renderer_ID(), fullscreenContext);
		if (m_ViewportSize != viewportPanelSize) {
			m_framebuffer->resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		}
	}

	// ------- Uniform Window -------------------------------------
	ImGui::Begin("Uniform Window");
	m_uniformController->imgui_draw();
	ImGui::End();

	showOverlay();
}


void RenderLayer::on_update(float time)
{

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!fullscreen) {
		m_framebuffer->bind();
	}
	else {
		m_ViewportSize = glm::vec2(Application::get().get_window().get_width(), Application::get().get_window().get_height());
		glViewport(0, 0, m_ViewportSize.x, m_ViewportSize.y);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

	}


	m_uniformController->set("iResolution", m_ViewportSize);
	m_uniformController->set("iTime", time);
	double x, y;
	int sx, sy;
	Application::get().get_window().get_cursor_pos(&x, &y);
	Application::get().get_window().get_window_pos(&sx, &sy);

	if (fullscreen) {

		if (x < 0) x = 0;
		else if (x > m_ViewportSize.x) x = m_ViewportSize.x;
		if (y < 0) y = 0;
		else if (y > m_ViewportSize.y) y = m_ViewportSize.y;
	}
	else {
		x += sx;
		y += sy;
		auto pos = m_renderWindow->windowPos;
		auto size = m_renderWindow->windowSize;
		if (x < pos.x) x = 0;
		else if (x > (double)pos.x + size.x) x = size.x;
		else x -= pos.x;
		if (y < pos.y) y = 0;
		else if (y > (double)pos.y + size.y) y = size.y;
		else y -= pos.y;
	}

	m_uniformController->set("iMouse", glm::vec2((float)x, (float)y));
	
	m_uniformController->use();
	m_renderWindow->render(m_ViewportSize, time);

	if (!fullscreen) m_framebuffer->unbind();
}


void RenderLayer::showMenu()
{
	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New", "Ctrl+n")) {
				std::string code = m_renderWindow->standardFragment;
				m_editor->setShaderSource(code);
				m_renderWindow->setFragmentShader(code);
				m_uniformController->set_from_source(code);
				m_logWindow->add_info("New Shader\n");
			}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
				std::wstring path = ShaderLoader::open();
				std::wcout << path << std::endl;

				using convert_type = std::codecvt_utf8<wchar_t>;
				std::wstring_convert<convert_type, wchar_t> converter;

				std::string s_path = converter.to_bytes(path);
				if (!s_path.empty()) {
					m_logWindow->clear();
					m_logWindow->add_info("Cleared Log\n");
					std::string code = ShaderLoader::load(s_path);
					m_editor->setShaderSource(code);
					m_renderWindow->setFragmentShader(code);
					m_uniformController->set_from_source(code);
					m_logWindow->add_info("Loaded Shader " + s_path + "\n");
				}
				else {
					m_logWindow->add_error("Loading Shader failed\n");
				}
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				ShaderLoader::save(m_editor->getShaderSource());
				m_logWindow->add_info("Saved Shader\n");
			}
			if (ImGui::MenuItem("Save As..")) {
				ShaderLoader::save_as(m_editor->getShaderSource());
				using convert_type = std::codecvt_utf8<wchar_t>;
				std::wstring_convert<convert_type, wchar_t> converter;

				std::string s_path = converter.to_bytes(ShaderLoader::current_path);
				m_logWindow->add_info("Saving Shader in " + s_path + "\n");
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {
			auto editor = m_editor->getEditor();
			bool ro =(*editor).IsReadOnly();
			if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
				(*editor).SetReadOnly(ro);
			ImGui::Separator();

			if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && (*editor).CanUndo()))
				(*editor).Undo();
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && (*editor).CanRedo()))
				(*editor).Redo();

			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, (*editor).HasSelection()))
				(*editor).Copy();
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && (*editor).HasSelection()))
				(*editor).Cut();
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && (*editor).HasSelection()))
				(*editor).Delete();
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
				(*editor).Paste();

			ImGui::Separator();

			if (ImGui::MenuItem("Select all", nullptr, nullptr))
				(*editor).SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates((*editor).GetTotalLines(), 0));

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			static bool fullscreenWindow = false;
			if (ImGui::MenuItem("Shader fullscreen", nullptr, &fullscreen)) {
				std::string value = (fullscreen ? "true\n" : "false\n");
				m_logWindow->add_info("Shader fullscreen view = " + value);
			}
			if (ImGui::MenuItem("Fullscreen", "F11", &fullscreenWindow)) {
				std::string value = (fullscreenWindow ? "true\n" : "false\n");
				m_logWindow->add_info("Shader fullscreen view = " + value);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Uniforms")) {
			if (ImGui::MenuItem("Reload uniforms")) {
				m_uniformController->set_from_source(m_editor->getShaderSource());
				m_logWindow->add_info("Updated Shader uniforms");
			}
			ImGui::EndMenu();
		}
		if (ImGui::Button("Compile")) {
			m_logWindow->success = true;
			m_renderWindow->setFragmentShader(m_editor->getShaderSource());
			if (m_logWindow->success) m_logWindow->add_info("Compiled successfully!\n");
		}
		ImGui::EndMenuBar();
	}

}

void showOverlay()
{
	static bool p_open = true;
	const float DISTANCE = 10.0f;
	static int corner = -1;
	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize  | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (corner != -1)
		window_flags |= ImGuiWindowFlags_NoMove;
	if (ImGui::Begin("Metrics", &p_open, window_flags)) {
		ImGui::Text("Application average (%.1f, FPS)", io.Framerate);
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow()) {
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (p_open && ImGui::MenuItem("Close")) p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}