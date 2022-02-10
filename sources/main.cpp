#include "main.hpp"

void	callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
(void) scancode;
(void) mods;
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

int main(void)
{
	try {
		if (!glfwInit())
			throw std::runtime_error("Could not initialize glfw");

		Window win(640, 480, "Hello World");
		win.set_key_callback(callback);
		
		if (glewInit())
			throw std::runtime_error("Could not initialize GLEW");

		while (!win.should_close())
		{
			glClear(GL_COLOR_BUFFER_BIT);

			win.swap_buffers();
			win.poll_events();
		}
	} catch (std::exception e()) {
		std::cout << e << std::endl;
		return 1;
	}
    return 0;
}