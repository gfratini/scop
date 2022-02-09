test -f "libglfw3.a" || {
	git clone https://github.com/glfw/glfw.git glfw-repo;
	cmake -S glfw-repo -B glfw;
	make -C glfw;
	mv -f glfw-repo/include/GLFW includes/GLFW;
	mv glfw/src/libglfw3.a libglfw3.a;
	rm -dir -f glfw-repo glfw
}

test -f "libGLEW.a" || {
	git clone https://github.com/nigels-com/glew.git glew;
	make -C glew/auto;
	make -C glew;
	mv glew/lib/libGLEW.a libGLEW.a;
	mv -f glew/include/GL includes/GL;
	rm -dir -f glew;
}