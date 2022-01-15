#include "pch.h"
#include "LogWindow.h"

#include "imgui.h"
#include <ctime>

std::vector<std::string> LogWindow::error_list = {};
bool LogWindow::success = true;
bool LogWindow::scrollToBottom = false;

LogWindow::LogWindow()
{
}
																									
LogWindow::~LogWindow()
{
}

void LogWindow::draw()
{
	static bool p_open = true;
	ImGuiWindowFlags flags = ImGuiWindowFlags_HorizontalScrollbar;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0, 0, 0, 0));

	ImGui::Begin("Log", &p_open);
	ImGui::BeginChild("scrollRegion", ImVec2(0, 0), false, flags);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

	for (int i = 0; i < error_list.size(); i++) {
		const char *text = error_list[i].c_str();
		if (strstr(text, "error")) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
		}
		else if (strstr(text, "info")) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.53f, 0.81f, 0.92f, 1.0f));
		}
		ImGui::TextUnformatted(text);
		ImGui::PopStyleColor();
	}
	if (scrollToBottom || ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
		ImGui::SetScrollHereY(1.0f);
	}
	scrollToBottom = false;

	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::End();

	ImGui::PopStyleColor(5);
}

void LogWindow::add_error(std::string error)
{
	success = false;
	std::string currentTime;
	time_t t;
	struct tm *localTime;

	time(&t);
	localTime = localtime(&t);

	int hours = localTime->tm_hour;
	int minutes = localTime->tm_min;
	int seconds = localTime->tm_sec;
	std::stringstream ss;
	ss << "[" << hours << ":" << minutes << ":" << seconds << "] error: " << error;
	currentTime = ss.str();
	error_list.push_back(currentTime);
	scrollToBottom = true;
}

void LogWindow::add_info(std::string info)
{
	std::string currentTime;
	time_t t;
	struct tm *localTime;

	time(&t);
	localTime = localtime(&t);

	int hours = localTime->tm_hour;
	int minutes = localTime->tm_min;
	int seconds = localTime->tm_sec;
	std::stringstream ss;
	ss << "[" << hours << ":" << minutes << ":" << seconds << "] info: " << info;
	currentTime = ss.str();
	error_list.push_back(currentTime);
	scrollToBottom = true;
}

void LogWindow::clear()
{
	error_list.clear();
}
