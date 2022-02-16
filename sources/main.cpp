#include "main.hpp"

mat::Vec3	camera_pos(0.0, 0.0, 10.0);
mat::Vec3	camera_target;
mat::Vec3	up(0.0,1.0,0.0);
mat::Vec3	camera_front;

mat::Mat4	view(mat::look_at(camera_pos, camera_target, up));

int		m_left = 0;
int		m_up = 0;
int		m_right = 0;
int		m_down = 0;

double		last_update = 0;

double	last_x = 800 / 2.0;
double	last_y = 600 / 2.0;
float	yaw = -90.0f;
float	pitch = 0;
bool	first_mouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
(void) window;
	if (first_mouse)
	{
		last_x = xpos;
		last_y = ypos;
		first_mouse = false;
	}

	auto xoffset = (float)(last_x - xpos);
	auto yoffset = (float)(ypos - last_y);
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

	mat::Vec3 direction;
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

	if (key == 'W') m_up = val;
	else if (key == 'S') m_down = val;
	else if (key == 'A') m_left = val;
	else if (key == 'D') m_right = val;
}

void move() {
	double new_time = glfwGetTime();

	float speed = 0.005;
	if (new_time - last_update >= MIN_UPDATE_TIME) {
		last_update = new_time;
		if (m_left && !m_right) {
			mat::Vec3 v = mat::normalize(mat::cross(up, camera_front)) * speed;
			camera_pos -= v;
		} else if (m_right && !m_left) {
			mat::Vec3 v = mat::normalize(mat::cross(up, camera_front)) * speed;
			camera_pos += v;
		}
		if (m_up && !m_down) {
			mat::Vec3 v = camera_front * speed;
			camera_pos += v;
		} else if (m_down && !m_up) {
			mat::Vec3 v = camera_front * speed;
			camera_pos -= v;
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

		unsigned int indices[] = {
			0, 1, 2,
			3, 1, 2
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
		IndexBuffer		ibo(indices, 6, GL_STATIC_DRAW);
		VertexBuffer	vbo(cube, 36, GL_STATIC_DRAW);
		Vertex::set_attrib_pointer();

		mat::Mat4 		perspective = mat::perspective(800, 600, 0.1, 1000, 60);
		mat::Mat4		transform;

		unsigned int i = 0;
		while (!win.should_close()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			move();
			view = mat::look_at(camera_pos, camera_pos + camera_front, up);

			if (glGetError()) exit(1);

			glUniformMatrix4fv(perspective_loc, 1, GL_TRUE, perspective.ptr());
			glUniformMatrix4fv(view_loc, 1, GL_TRUE, view.ptr());
			transform = mat::Mat4();
			transform.scale({200.0f, 0.01f, 200.0f});
			glUniformMatrix4fv(transform_loc, 1, GL_TRUE, transform.ptr());
			glDrawArrays(GL_TRIANGLES, 0, 36);
			transform = mat::Mat4();
			transform.translate({0.0f, 0.5f, 0.0f});
			glUniformMatrix4fv(transform_loc, 1, GL_TRUE, transform.ptr());
			glDrawArrays(GL_TRIANGLES, 0, 36);

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