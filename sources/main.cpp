#include "main.hpp"

Camera	camera({0.0, -5, 20});

int		m_left = 0;
int		m_up = 0;
int		m_right = 0;
int		m_down = 0;

int		run = 0;

double		last_update = 0;

GLenum render = GL_FILL;

static unsigned int shader_id;

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

	if (key == 'T' && action == GLFW_PRESS) {
		render = render == GL_FILL ? GL_LINE : GL_FILL;
		int loc = glGetUniformLocation(shader_id, "isWireframe");
		glUniform1i(loc, render == GL_FILL ? 0 : 1);
		glPolygonMode(GL_FRONT_AND_BACK, render);
	}

	if (key == 'W') m_up = val;
	else if (key == 'S') m_down = val;
	else if (key == 'A') m_left = val;
	else if (key == 'D') m_right = val;
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) run = 1;
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) run = 0;
}

void move(int view_loc) {
	double new_time = glfwGetTime();

	if (new_time - last_update >= MIN_UPDATE_TIME) {
		last_update = new_time;
		camera.move(m_up, m_down, m_right, m_left, run);
		glUniformMatrix4fv(view_loc, 1, GL_TRUE, camera.view().ptr());
	}
}


#ifdef TEST_PARSE

int main() {
	Parser p;

	p.parse("assets/objects/untitled.obj");
}

#else

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
		ShaderProgram		shader("shaders/vertex.glsl", "shaders/fragment.glsl");
		shader.use(shader_id);

		int perspective_loc = glGetUniformLocation(shader.id(), "perspective");
		int view_loc = glGetUniformLocation(shader.id(), "view");

		VertexArrayBuffer	array_buffer;

		Mat4 		p = perspective(WIDTH, HEIGHT, 0.1, 1000, 60);
		glUniformMatrix4fv(perspective_loc, 1, GL_TRUE, p.ptr());
		glUniformMatrix4fv(view_loc, 1, GL_TRUE, camera.view().ptr());

		Scene scene("assets/resources/chess_board.obj");

		float i = 0;
		float j = 0;
		while (!win.should_close()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			GL_CHECK(move(view_loc););

			if (glGetError()) exit(1);

			array_buffer.bind();
			shader.use(shader_id);
			scene.render(shader);

			win.swap_buffers();
			Window::poll_events();
			i += 0.1;
			if (i >= 360) i = 0;
			j += 0.002;
			if (j >=360) j = 0;
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		exit_status = 1;
	}
	glfwTerminate();
    return exit_status;
}

#endif