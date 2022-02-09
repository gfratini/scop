#include "main.hpp"

int main(void)
{
	try {
		if (!glfwInit())
			return -1;

		Window win(640, 480, "Hello World");

		/* Loop until the user closes the window */
		while (!win.should_close())
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			win.swap_buffers();

			win.poll_events();
		}
	} catch (std::exception e()) {
		std::cout << e << std::endl;
	}
    return 0;
}