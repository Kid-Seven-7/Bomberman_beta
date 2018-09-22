#         _
#        (_)___  ____ _____  ____ ___  ____ _
#       / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
#      / / / / / /_/ / /_/ / / / / / / /_/ /
#   __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
#  /___/      /____/

NAME = Bomberman

SRCPATH = src/

SRC = $(SRCPATH)main.cpp\
			$(SRCPATH)setVersion.cpp\
			$(SRCPATH)initCheck.cpp\
			$(SRCPATH)sound.class.cpp\
			$(SRCPATH)keys.class.cpp\
			$(SRCPATH)shader.cpp\
			$(SRCPATH)processInput.cpp

COMP = clang++

CPPSTD = -std=c++11

CPPFLAGS = -Wall -Wextra -Werror

LIB = -L ~/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -DGLEW_STATIC

INC = -I ~/.brew/include

GLMINC = -I ~/.brew/Cellar/glm/0.9.9.0/include/

SOUNDLIB = -I includes -I ./SFML/include

SOUNDFLAGS = -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-audio -F SFML/Frameworks

RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m
NC = \033[0m

all:	$(NAME)

$(NAME):
	@sh scripts/setup.sh
	@printf "$(GREEN)compiling source files\n$(NC)"
	@$(COMP) -o $(NAME) $(SRC) $(CPPFLAGS) $(CPPSTD) $(INC) $(LIB) $(TEXTINC) $(GLMINC) $(SOUNDLIB) $(SOUNDFLAGS) -lglfw3 -lGLEW
	clear
	@printf "$(GREEN)please type the following in the terminal on first execution\n$(NC)"
	@printf "$(RED)export DYLD_FRAMEWORK_PATH=\"$(PWD)/SFML/Frameworks\"\n$(NC)"

clean:
	@printf "$(ORANGE)removing object files\n$(NC)"
	@rm -f $(SRCO)

fclean: clean
	@printf "$(ORANGE)removing exectutable\n$(NC)"
	@rm -f $(NAME)

re: fclean all
