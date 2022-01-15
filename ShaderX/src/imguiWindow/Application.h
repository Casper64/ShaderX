#pragma once

#include "Window.h"
#include "LayerStack.h"
#include "ImguiLayer.h"


int main(int argc, char **argv);

class Application
{
public:
	Application();
	virtual ~Application();

	void push_layer(Layer *layer);
	void push_overlay(Layer *overlay);

	Window &get_window() { return *m_window; };
	void close();

	static Application &get() { return *s_instance; };
	char *getPath() { return path; };
	void setPath(char *p) { strcpy_s(path, p); };

private:
	void run();
private:
	std::unique_ptr<Window> m_window;
	ImguiLayer *m_imguiLayer;
	bool m_running = true;
	LayerStack m_layerStack;
	char path[512] = "";
private:
	static Application *s_instance;
	friend int ::main(int argc, char **argv);
};

Application *create_application(int argc, char **argv);
