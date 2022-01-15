#pragma once
#include "pch.h"

class LogWindow
{
public:
	LogWindow();
	~LogWindow();

	void draw();
	void clear();
public:
	static void add_error(std::string error);
	static void add_info(std::string info);
	static bool success;
private:
	static std::vector<std::string> error_list;
	static bool scrollToBottom;
};

