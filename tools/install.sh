if [[ $(uname -s) == "MSYS"* ]]; then
  test -f "libglfw3.a" || {
    curl -L "https://github.com/glfw/glfw/releases/download/3.3.6/glfw-3.3.6.bin.WIN64.zip" -o glfw.zip
    tar -xzvf glfw.zip && mv glfw-* glfw
    mv glfw/lib-mingw-w64/libglfw3.a .
    mv -f glfw/include/GLFW includes/GLFW;
    rm -rf glfw.zip glfw
  }
#  test -f "libGLEW.a" || {
#      git clone https://github.com/nigels-com/glew.git glew;
#      powershell make -C glew/auto;
#      make -C glew;
#      mv glew/lib/libGLEW.a libGLEW.a;
#      mv -f glew/include/GL includes/GL;
#      rm -dir -f glew;
#    }
else
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
fi