# Makefile """"inspired"""" by Ciro Seraponte (siraponte on github)

NAME =		scop

CXX = 		clang++
CXXFLAGS = 	-Wall -Wextra -Werror
LIBS =		-lglfw3 -lGLEW

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
	@$(CXX) $(CXXFLAGS) $(LIBS) -I $(INCDIR) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

install:
	$(shell sh run.sh || 1)
	cmake -S glfw-repo -B glfw
	make -C glfw
	mv glfw/src/libglfw3.a libglfw3.a
	make -C glew/auto
	make -C glew
	mv glew/lib/libGLEW.a libGLEW.a
	rm -dir -f glfw-repo glfw glew

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: re
	@./$(NAME)

.PHONY: all clean fclean re run