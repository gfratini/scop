test -f "libglfw3.a" || {
	git clone https://github.com/glfw/glfw.git glfw-src;
	cmake -S glfw-src -B glfw;
	make -C glfw;
	mv glfw/src/libglfw3.a libglfw3.a;
	mv -f glfw-src/include/GLFW includes/GLFW;
	rm -dir -f glfw-src glfw
}

test -f "libGLEW.a" || {
	git clone https://github.com/nigels-com/glew.git glew;
	make -C glew/auto;
	make -C glew;
	mv glew/lib/libGLEW.a libGLEW.a;
	mv -f glew/include/GL includes/GL;
	rm -dir -f glew;
}