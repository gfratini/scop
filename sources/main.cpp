#include "main.hpp"

int main()
{
	glfwInit();
	GLFWwindow* win = glfwCreateWindow(800, 800, "Scop", NULL, NULL);

	glfwMakeContextCurrent(win);
	glewInit();

	std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
}