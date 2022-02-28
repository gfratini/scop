#include "main.hpp"

Camera	camera({0.0, -5, 20});

int		m_left = 0;
int		m_up = 0;
int		m_right = 0;
int		m_down = 0;

int		run = 0;

int		light = 0;
float	solid = 1.0f;
int		transition = 0;
float 	lightLevel = 5;

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

	if (key == 'X' && action == GLFW_PRESS) {
		render = render == GL_FILL ? GL_LINE : GL_FILL;
		int loc = glGetUniformLocation(shader_id, "isWireframe");
		int loc2 = glGetUniformLocation(shader_id, "isSolid");
		if (render == GL_LINE) {
			glUniform1i(loc, 1);
			glUniform1f(loc2, 1);
		}
		else {
			glUniform1i(loc, light);
			glUniform1f(loc2, solid);
		}
		glPolygonMode(GL_FRONT_AND_BACK, render);
	}

	if (key == 'L' && action == GLFW_PRESS && render == GL_FILL) {
		light = !light;
		int loc = glGetUniformLocation(shader_id, "isWireframe");
		glUniform1i(loc, light);
	}

	if (key == 'T' && action == GLFW_PRESS && render == GL_FILL) {
		transition = solid > 0.1f ? -1 : 1;
		int loc = glGetUniformLocation(shader_id, "isSolid");
		glUniform1f(loc, solid);
	}

	if (key == GLFW_KEY_KP_ADD) {
		lightLevel += 0.5;
		int loc = glGetUniformLocation(shader_id, "lightLevel");
		glUniform1f(loc, lightLevel);
	}
	if (key == GLFW_KEY_KP_SUBTRACT) {
		lightLevel -= 0.5;
		int loc = glGetUniformLocation(shader_id, "lightLevel");
		glUniform1f(loc, lightLevel);
	}

	if (key == 'W') m_up = val;
	else if (key == 'S') m_down = val;
	else if (key == 'A') m_left = val;
	else if (key == 'D') m_right = val;
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) run = 1;
	else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) run = 0;
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) run = -1;
	else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) run = 0;
}

void move(int view_loc) {
	double new_time = glfwGetTime();

	if (new_time - last_update >= MIN_UPDATE_TIME) {
		last_update = new_time;
		if (transition) {
			solid += transition > 0 ? 0.01f : -0.01f;
			if (solid >= 1.0f || solid <= 0.0f)
				transition = 0;
			int loc = glGetUniformLocation(shader_id, "isSolid");
			glUniform1f(loc, solid);
		}
		camera.move(m_up, m_down, m_right, m_left, run);
		glUniformMatrix4fv(view_loc, 1, GL_TRUE, camera.view().ptr());
	}
}

int main(int argc, const char ** argv)
{
	if (argc == 1 || argc > 3) {
		std::cout << "Usage:\n  scop file_to_render.obj [texture_file]" << std::endl;
		exit(1);
	}
	std::string tex;
	if (argc == 3)
		tex = argv[2];
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
		int loc = glGetUniformLocation(shader.id(), "lightLevel");
		glUniform1f(loc, lightLevel);

		VertexArrayBuffer	array_buffer;

		Mat4 		p = perspective(WIDTH, HEIGHT, 0.1, 1000, 60);
		glUniformMatrix4fv(perspective_loc, 1, GL_TRUE, p.ptr());
		camera.move(m_up, m_down, m_right, m_left, run);
		glUniformMatrix4fv(view_loc, 1, GL_TRUE, camera.view().ptr());

		Scene scene(argv[1], tex);

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
