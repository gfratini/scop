# Makefile """"inspired"""" by Ciro Seraponte (siraponte on github)

NAME =		scop

CXX = 		clang++
CXXFLAGS = 	-Wall -Wextra -g

MACOS =		-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

LIBS :=		-L. -lglfw3 -lGLEW $(MACOS)

MKDIR =		mkdir -p
RM =		rm -rf

SRCDIR = 	./sources
INCDIR = 	./includes
OBJDIR =  	./.obj

FILES =		main.cpp \
			Window.cpp \
			ShaderProgram.cpp \
			VertexArrayBuffer.cpp \
			VertexBuffer.cpp \
			IndexBuffer.cpp \
			Texture.cpp

SRCS = 		$(foreach FILE, $(FILES), $(shell find $(SRCDIR) -name $(FILE)))
OBJS = 		$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.cpp=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(MKDIR) $(@D)
	@$(CXX) $(CXXFLAGS) -I $(INCDIR) -c -o $@ $<

all: install $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(LIBS) $(OBJS) -o $(NAME)

install:
	$(shell sh tools/install.sh)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: re
	@./$(NAME)

.PHONY: all clean fclean re run