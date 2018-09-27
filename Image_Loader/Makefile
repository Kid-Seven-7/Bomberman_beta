# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/20 09:55:11 by amatshiy          #+#    #+#              #
#    Updated: 2018/08/20 10:00:01 by amatshiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = loader.o

CMP = clang++ -c

SRC = image_loader.cpp

RED = \033[0;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[0;34m
CYAN = \033[0;36m
NC = \033[0m


all:
	@printf "$(GREEN)compiling source files\n$(NC)"
	@$(CMP) $(SRC) -o $(NAME)

clean:
	@printf "$(ORANGE)removing executable\n$(NC)"
	@rm -rf $(NAME)

fclean: clean

re: fclean all
