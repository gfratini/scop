# Makefile """"inspired"""" by Ciro Seraponte (siraponte on github)

NAME =		scop.exe

CXX = 		g++.exe
CXXFLAGS = 	-Wall -Wextra -Werror
LIBS =		

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
	$(CXX) $(CXXFLAGS) $(LIBS) -I $(INCDIR) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: re
	@./$(NAME)

.PHONY: all clean fclean re run