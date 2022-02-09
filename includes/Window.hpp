#pragma once

#include "GLFW/glfw3.h"
#include <string>

class Window {
private:
    GLFWwindow* win;
	
public:
	Window(int width, int height, const std::string& title);
	~Window();
	
	bool	should_close() const;
	void	swap_buffers();
	void	poll_events() const;
};

Window::Window(int width, int height, const std::string& title) {
	win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!win) {
    	glfwTerminate();
		throw std::runtime_error("Error: Could not create a Window");
	}
	glfwMakeContextCurrent(win);
}

Window::~Window() {
	glfwTerminate();
}

bool	Window::should_close() const { return glfwWindowShouldClose(win); }

void	Window::swap_buffers() { glfwSwapBuffers(win); }

void	Window::poll_events() const { glfwPollEvents(); }
