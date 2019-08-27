# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: judrion <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 13:05:20 by judrion           #+#    #+#              #
#    Updated: 2019/08/27 14:28:44 by judrion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = main mandlebrot render
SRCS = $(addprefix src/, $(addsuffix .c, $(SRC)))
OBJ = $(SRCS:.c=.o)
INCLUDE = -Llibft/ -Lminilibx/
LIB = -lft -lmlx -lpthread -Ilibft/ -Iminilibx -Iincludes/
CFLAG = -Wall -Werror -Wextra -Iincludes/
DCFLAG = -Wall -Werror -Wextra -Iincludes/ -fsanitize=address
FRAMEWORK = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	$(MAKE) -C libft/
	$(MAKE) -C minilibx/
	gcc $(DCFLAG) -o $(NAME) $(INCLUDE) $(LIB) $(SRCS) $(FRAMEWORK) -D_REENTRANT

.PHONY: clean fclean re lclean

lclean:
	@echo "Clean des librairies"
	@$(MAKE) -C libft/ fclean
	@$(MAKE) -C minilibx/ clean
clean:
	@echo "Clean des fichiers .o"
	@$(RM) $(OBJ)

fclean: clean
	@echo "Clean $(NAME)"
	@$(RM) $(NAME)

re: fclean all
