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

mat::Vec4	camera_front;
mat::Vec4	camera;
mat::Vec4	up(0.0, 1.0, 0.0, 1.0);

double	last_x = 0;
double	last_y = 0;
float	yaw = 0;
float	pitch = 0;
bool	first_mouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (first_mouse)
	{
		last_x = xpos;
		last_y = ypos;
		first_mouse = false;
	}

	float xoffset = (float)(xpos - last_x);
	float yoffset = (float)(last_y - ypos);
	last_x = xpos;
	last_y = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	mat::Vec4 direction;
	direction.x() = cos(mat::rad(yaw)) * cos(mat::rad(pitch));
	direction.y() = sin(mat::rad(pitch));
	direction.z() = sin(mat::rad(yaw)) * cos(mat::rad(pitch));
	camera_front = mat::normalize(direction);
}

void	callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
(void) scancode;
(void) mods;

	int val = action;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	if (key == 'Q') r_left = val;
	else if (key == 'E') r_right = val;
	else if (key == 'W') m_up = val;
	else if (key == 'S') m_down = val;
	else if (key == 'A') m_left = val;
	else if (key == 'D') m_right = val;
	else if (key == 'R') s_up = val;
	else if (key == 'F') s_down = val;
}

void move() {
	double new_time = glfwGetTime();

	float speed = 0.05;
	if (new_time - last_update >= MIN_UPDATE_TIME) {
		last_update = new_time;
		if (m_left && !m_right) {
			mat::Vec4 v = mat::normalize(mat::cross(camera_front, up));
			camera += v;
		} else if (m_right && !m_left) {
			mat::Vec4 v = camera_front * speed;
			camera -= v;
		}
		if (m_up && !m_down) {
			mat::Vec4 v = camera_front * speed;
			camera += v;
		} else if (m_down && !m_up) {
			mat::Vec4 v = camera_front * speed;
			camera -= v;
		}
		if (r_left && !r_right) {
			float f[] = {0.0, 1.0, 0.0, 1.0};
			t.rotate(f, mat::rad(1));
		} else if (r_right && !r_left) {
			float f[] = {0.0, 1.0, 0.0, 1.0};
			t.rotate(f, mat::rad(-1));
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

		Window win(800, 600, "Scop");
		win.set_key_callback(callback);
		win.set_mouse_callback(mouse_callback);
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Could not initialize GLEW");

		glEnable(GL_DEPTH_TEST);
		float vertices[] = {
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

		int transform_loc = glGetUniformLocation(shader.id(), "transform");
		int perspective_loc = glGetUniformLocation(shader.id(), "perspective");
		int view_loc = glGetUniformLocation(shader.id(), "view");

		VertexArrayBuffer	array_buffer;
		VertexBuffer	vbo(vertices, 36, GL_STATIC_DRAW);
		Vertex::set_attrib_pointer();
//		IndexBuffer		ibo(indices, 6, GL_STATIC_DRAW);

		mat::Mat4 		perspective = mat::perspective(800, 600, 0.0, 100, 60);
		mat::Mat4		transform;
//		mat::Mat4		view;
//		transform.scale(mat::Vec4(1.2, 1.2, 1.2, 1.0));
		transform.rotate(mat::Vec4(1.0, 0.0, 0.0, 1.0), mat::rad(55.0));
		transform.rotate(mat::Vec4(0.0, 1.0, 0.0, 1.0), mat::rad(30.0));
		t.translate(mat::Vec4(0.0, 0.0, 5, 1.0));

		unsigned int i = 0;
		while (!win.should_close()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			if (glGetError()) exit(1);

			glUniformMatrix4fv(perspective_loc, 1, GL_TRUE, perspective.ptr());
			glUniformMatrix4fv(view_loc, 1, GL_TRUE, t.ptr());
			glUniformMatrix4fv(transform_loc, 1, GL_TRUE, transform.ptr());
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