#include "main.hpp"

static mat::Mat4*		t = new mat::Mat4();

void	callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
(void) scancode;
(void) mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (key == GLFW_KEY_Q) {
		float f[] = {0.0, 0.0, 1.0, 0.0};
		(*t).rotate(f, 1.0);
	}
	else if (key == GLFW_KEY_E) {
		float f[] = {0.0, 0.0, 1.0, 0.0};
		(*t).rotate(f, -1.0);
	}
	if (key == GLFW_KEY_W) {
		float f[] = {0.01, 0.0, 0.0, 0.0};
		(*t).translate(f);
	}
	else if (key == GLFW_KEY_S) {
		float f[] = {-0.01, 0.0, 0.0, 0.0};
		(*t).translate(f);
	}
	if (key == GLFW_KEY_A) {
		float f[] = {0.0, 0.01, 0.0, 0.0};
		(*t).translate(f);
	}
	else if (key == GLFW_KEY_D) {
		float f[] = {0.0, -0.01, 0.0, 0.0};
		(*t).translate(f);
	}
}

int main()
{
	int	exit_status = 0;
	try {
		if (!glfwInit())
			throw std::runtime_error("Could not initialize glfw");

		Window win(640, 480, "Hello World");
		win.set_key_callback(callback);
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Could not initialize GLEW");

		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		Texture				texture1("assets/textures/container.jpg", GL_TEXTURE0);
		Texture				texture2("assets/textures/wall.jpg", GL_TEXTURE1);

		ShaderProgram		shader("shaders/vertex.glsl", "shaders/fragment.glsl");
		shader.use();
		glUniform1i(glGetUniformLocation(shader.id(), "texture1"), 0);
		glUniform1i(glGetUniformLocation(shader.id(), "texture2"), 1);

		int transform = glGetUniformLocation(shader.id(), "transform");

		VertexArrayBuffer	array_buffer;
		VertexBuffer	vbo(vertices, 4, GL_STATIC_DRAW);
		Vertex::set_attrib_pointer();
		IndexBuffer		ibo(indices, 6, GL_STATIC_DRAW);

		unsigned int i = 0;
		while (!win.should_close()) {
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

			if (glGetError()) exit(1);

			glUniformMatrix4fv(transform, 1, GL_TRUE, (*t).ptr());
			texture1.bind();
			texture2.bind();

			win.swap_buffers();
			Window::poll_events();
			i++;
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		exit_status = 1;
	}
	glfwTerminate();
    return exit_status;
}