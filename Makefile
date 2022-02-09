# Makefile """"inspired"""" by Ciro Seraponte (siraponte on github)

NAME =		scop

CXX = 		clang++
CXXFLAGS = 	-Wall -Wextra -Werror

MACOS =		-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

LIBS :=		-L. -lglfw3 -lGLEW $(MACOS)

MKDIR =		mkdir -p
RM =		rm -rf

SRCDIR = 	./sources
INCDIR = 	./includes
OBJDIR =  	./.obj

FILES =		main.cpp

SRCS = 		$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))
OBJS = 		$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.cpp=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(MKDIR) $(@D)
	$(CXX) $(CXXFLAGS) -I $(INCDIR) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS) -o $(NAME)

install:
	$(shell sh run.sh || 1)
	@cmake -S glfw-repo -B glfw
	@mv -f glfw-repo/include/GLFW includes/GLFW
	@make -C glfw
	@mv glfw/src/libglfw3.a libglfw3.a
	@make -C glew/auto
	@make -C glew
	@mv glew/lib/libGLEW.a libGLEW.a
	@mv -f glew/include/GL includes/GL
	@rm -dir -f glfw-repo glfw glew

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: re
	@./$(NAME)

.PHONY: all clean fclean re run