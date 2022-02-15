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

	if (new_time - last_update >= MIN_UPDATE_TIME) {
		last_update = new_time;
		if (m_left && !m_right) {
			float f[] = {0.01, 0.0, 0.0, 1.0};
			t.translate(f);
		} else if (m_right && !m_left) {
			float f[] = {-0.01, 0.0, 0.0, 1.0};
			t.translate(f);
		}
		if (m_up && !m_down) {
			float f[] = {0.0, 0.0, -0.01, 1.0};
			t.translate(f);
		} else if (m_down && !m_up) {
			float f[] = {0.0, 0.0, 0.01, 1.0};
			t.translate(f);
		}
		if (r_left && !r_right) {
			float f[] = {0.0, 0.0, 1.0, 1.0};
			t.rotate(f, mat::rad(1));
		} else if (r_right && !r_left) {
			float f[] = {0.0, 0.0, 1.0, 1.0};
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


#define _DEBUG
#ifndef CHECK_ERR
#define CHECK_ERR
void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		abort();
	}
}
#endif
#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif


int main()
{
	int	exit_status = 0;
	try {
		if (!glfwInit())
			throw std::runtime_error("Could not initialize glfw");

		Window win(800, 600, "Scop");
		win.set_key_callback(callback);
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
//		mat::Mat4		perspective;
		mat::Mat4		transform;
		mat::Mat4		view;
//		transform.scale(mat::Vec4(1.2, 1.2, 1.2, 1.0));
		transform.rotate(mat::Vec4(1.0, 0.0, 0.0, 1.0), mat::rad(55.0));
		transform.rotate(mat::Vec4(0.0, 1.0, 0.0, 1.0), mat::rad(30.0));
		t.translate(mat::Vec4(0.0, 0.0, 5, 1.0));

		std::cout << perspective * view << std::endl;

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