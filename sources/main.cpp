#include "main.hpp"

void	callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
(void) scancode;
(void) mods;
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

int main()
{
	int					exit_status = 0;
	try {
		if (!glfwInit())
			throw std::runtime_error("Could not initialize glfw");

		Window win(640, 480, "Hello World");
		win.set_key_callback(callback);

		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Could not initialize GLEW");
		ShaderProgram		shader("shaders/vertex.glsl", "shaders/fragment.glsl");
		VertexArrayBuffer	array_buffer;

		float vertices[] = {
			// positions       // colors        // texture coords
			 0.5,  0.5, 0.0,   1.0, 0.0, 0.0,   1.0, 1.0,   // top right
			 0.5, -0.5, 0.0,   0.0, 1.0, 0.0,   1.0, 0.0,   // bottom right
			-0.5, -0.5, 0.0,   0.0, 0.0, 1.0,   0.0, 0.0,   // bottom left
			-0.5,  0.5, 0.0,   1.0, 1.0, 0.0,   0.0, 1.0    // top left
		};

		(void) vertices;
		while (!win.should_close()) {
			glClear(GL_COLOR_BUFFER_BIT);

			win.swap_buffers();
			Window::poll_events();
		}

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		exit_status = 1;
	}
	glfwTerminate();
    return exit_status;
}