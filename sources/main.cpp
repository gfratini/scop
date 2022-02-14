#include "main.hpp"

mat::Mat4	t;

int		m_left = 0;
int		m_up = 0;
int		r_left = 0;

int		m_right = 0;
int		m_down = 0;
int		r_right = 0;

int s_up = 0;
int s_down = 0;

double		last_update = 0;

void	callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
(void) scancode;
(void) mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (key == 'Q' && action != GLFW_RELEASE) r_left = 1;
	else if (key == 'E' && action != GLFW_RELEASE) r_right = 1;
	else if (key == 'Q') r_left = 0;
	else if (key == 'E') r_right = 0;
	else if (key == 'W' && action != GLFW_RELEASE) m_up = 1;
	else if (key == 'S' && action != GLFW_RELEASE) m_down = 1;
	else if (key == 'W') m_up = 0;
	else if (key == 'S') m_down = 0;
	else if (key == 'A' && action != GLFW_RELEASE) m_left = 1;
	else if (key == 'D' && action != GLFW_RELEASE) m_right = 1;
	else if (key == 'A') m_left = 0;
	else if (key == 'D') m_right = 0;
	else if (key == 'R' && action != GLFW_RELEASE) s_up = 1;
	else if (key == 'F' && action != GLFW_RELEASE) s_down = 1;
	else if (key == 'R') s_up = 0;
	else if (key == 'F') s_down = 0;
}

void move() {
	double new_time = glfwGetTime();

	if (new_time - last_update >= MIN_UPDATE_TIME) {
		last_update = new_time;
		if (m_left && !m_right) {
			float f[] = {-0.01, 0.0, 0.0, 1.0};
			t.translate(f);
		} else if (m_right && !m_left) {
			float f[] = {0.01, 0.0, 0.0, 1.0};
			t.translate(f);
		}
		if (m_up && !m_down) {
			float f[] = {0.0, 0.01, 0.0, 1.0};
			t.translate(f);
		} else if (m_down && !m_up) {
			float f[] = {0.0, -0.01, 0.0, 1.0};
			t.translate(f);
		}
		if (r_left && !r_right) {
			float f[] = {0.0, 1.0, 0.0, 1.0};
			t.rotate(f, 0.01);
		} else if (r_right && !r_left) {
			float f[] = {0.0, 1.0, 0.0, 1.0};
			t.rotate(f, -0.01);
		}
		if (s_up && !s_down) {
			float f[] = {1.01, 1.01, 1.01, 1.0};
			t.scale(f);
		}
		if (s_down && !s_up) {
			float f[] = {0.99, 0.99, 0.99, 1.0};
			t.scale(f);
		}
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

			glUniformMatrix4fv(transform, 1, GL_TRUE, t.ptr());
			texture1.bind();
			texture2.bind();

			move();

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