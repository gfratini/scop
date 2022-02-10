//
// Created by Giulio Fratini on 2/10/22.
//

#include "Window.hpp"

Window::Window(int width, int height, const std::string& title) {
	win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!win) {
		glfwTerminate();
		throw std::runtime_error("Error: Could not create a Window");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	glfwSwapInterval(1);
	glfwMakeContextCurrent(win);
}

Window::~Window() {
	glfwTerminate();
}

bool	Window::should_close() const { return glfwWindowShouldClose(win); }

void	Window::swap_buffers() { glfwSwapBuffers(win); }

void	Window::poll_events() { glfwPollEvents(); }

void	Window::set_key_callback(void (*callback)(GLFWwindow *, int, int, int, int)) const { glfwSetKeyCallback(win, callback); }
