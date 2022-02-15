//
// Created by Giulio Fratini on 2/10/22.
//

#ifndef SCOP_CPP_WINDOW_HPP
#define SCOP_CPP_WINDOW_HPP

#include <string>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* win;

public:
	Window(int width, int height, const std::string& title);
	~Window();

	bool	should_close() const;
	void	swap_buffers();
	static void	poll_events();
	void set_key_callback(void (*callback)(GLFWwindow *, int, int, int, int)) const;

	void set_mouse_callback(void (*callback)(GLFWwindow *, double, double)) const;
};

#endif //SCOP_CPP_WINDOW_HPP
