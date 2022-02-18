#include "main.hpp"

Camera	camera({0.0, -0.5, 3});

int		m_left = 0;
int		m_up = 0;
int		m_right = 0;
int		m_down = 0;

double		last_update = 0;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
(void) window;
	camera.look(xpos, ypos);
}

void	callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
(void) scancode;
(void) mods;

	int val = action;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	if (key == 'W') m_up = val;
	else if (key == 'S') m_down = val;
	else if (key == 'A') m_left = val;
	else if (key == 'D') m_right = val;
}

void move(int view_loc) {
	double new_time = glfwGetTime();

	if (new_time - last_update >= MIN_UPDATE_TIME) {
		last_update = new_time;
		camera.move(m_up, m_down, m_right, m_left);
		glUniformMatrix4fv(view_loc, 1, GL_TRUE, camera.view().ptr());
	}
}

int main()
{
	const unsigned int WIDTH = 1920;
	const unsigned int HEIGHT = 1080;
	int	exit_status = 0;
	try {
		if (!glfwInit())
			throw std::runtime_error("Could not initialize glfw");

		Window win(WIDTH, HEIGHT, "Scop");
		win.set_key_callback(callback);
		win.set_mouse_callback(mouse_callback);
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Could not initialize GLEW");

		glEnable(GL_DEPTH_TEST);
		float cube[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		float vertices[] = {
				0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
				0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
				-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left
		};
		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		ShaderProgram		shader("shaders/vertex.glsl", "shaders/fragment.glsl");
		shader.use();

		int perspective_loc = glGetUniformLocation(shader.id(), "perspective");
		int view_loc = glGetUniformLocation(shader.id(), "view");

		VertexArrayBuffer	array_buffer;
		IndexBuffer		ibo(indices, 6, GL_STATIC_DRAW);

		Mat4 		p = perspective(WIDTH, HEIGHT, 0.1, 1000, 60);
		glUniformMatrix4fv(perspective_loc, 1, GL_TRUE, p.ptr());
		glUniformMatrix4fv(view_loc, 1, GL_TRUE, camera.view().ptr());

		VertexBuffer	aaa(vertices, 4, GL_STATIC_DRAW);
		Object	cube_obj(shader, aaa, ibo, "assets/textures/container.jpg", GL_TEXTURE0);
		cube_obj.translate({0.0f, 0.5f, 0.0f});

		VertexBuffer	vbo(cube, 36, GL_STATIC_DRAW);
		Object	plane_obj(shader, vbo, "assets/textures/obama2.png", GL_TEXTURE0);
		plane_obj.scale({10.0f, 0.01f, 10.0f});

		while (!win.should_close()) {
			cube_obj.rotate({0.0f, 1.0f, 0.0f}, 0.02);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			GL_CHECK(move(view_loc););

			if (glGetError()) exit(1);

			array_buffer.bind();
			cube_obj.draw();
			plane_obj.draw();

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
