#include "pch.h"
#include "Window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "dependencies/stb_image.h"

static void glfwErrorCallback(int error, const char *description)
{
	printf("GLFW error (%d): %s\n", error, description);
}

Window::Window(const WindowData &props)
{
	init(props);
}


Window::~Window()
{
}


Scope<Window> Window::Create(const WindowData &props)
{
	return CreateScope<Window>(props);
}

void Window::init(const WindowData &data)
{
	m_data.width = data.width;
	m_data.height = data.height;
	m_data.title = data.title;

	int success = glfwInit();
	if (!success) {
		printf("Failed to initialize GLFW!\n");
	}
	glfwSetErrorCallback(glfwErrorCallback);

	m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
	m_monitor = glfwGetPrimaryMonitor();

	// create context?
	m_context = OpenGLContext::create(m_window);
	m_context->init();

	glfwSetWindowUserPointer(m_window, &m_data);
	setVSync(true);

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
		WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;
		// do callbacks
	});
	glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
		static bool fullscreen = false;
		static int x, y, w, h = 0;
		if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
			GLFWmonitor *monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode *mode = glfwGetVideoMode(monitor);
			if (!fullscreen) {
				glfwGetWindowPos(window, &x, &y);
				glfwGetWindowSize(window, &w, &h);
				glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
				fullscreen = true;
			}
			else {
				glfwSetWindowMonitor(window, NULL, x, y, w, h, GLFW_DONT_CARE);
				fullscreen = false;
			}
		}
	});


	GLFWimage *icon = new GLFWimage();
	int width, height, channels;
	//stbi_set_flip_vertically_on_load(true);
	icon->pixels = stbi_load("icon.png",  &icon->width,  &icon->height, 0, 4);
	glfwSetWindowIcon(m_window, 1, icon);
	stbi_image_free(icon->pixels);
	delete icon;
}

void Window::shutdown()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::on_update()
{
	glfwPollEvents();
	m_context->swap_buffers();
}

void Window::setVSync(bool enabled)
{
	if (enabled) {
		glfwSwapInterval(1);
	}
	else {
		glfwSwapInterval(0);
	}
	m_data.vsync = enabled;
}

bool Window::isVSync()
{
	return m_data.vsync;
}

