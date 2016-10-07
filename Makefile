# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: palatorr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/26 12:15:50 by palatorr          #+#    #+#              #
#    Updated: 2016/09/26 12:15:53 by palatorr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILENAMES	= main.c dungeon.c monster.c player.c

NAME		= rogue
FLAGS		= -Wall -Wextra -Werror
LIBFTDIR	= ~/libft/

SRC			= $(FILENAMES)
OBJS		= $(addprefix build/, $(FILENAMES:.c=.o))

all: $(NAME)

re: fclean all

clean:
	@rm -rf build/

fclean: clean
	@rm -rf $(NAME)

build:
	@mkdir build/

$(NAME): $(OBJS)
	gcc $(FLAGS) $^ -o $@ -L $(LIBFTDIR) -lft

build/%.o: %.c rogue.h | build
	@gcc $(FLAGS) -I $(LIBFTDIR) -c $< -o $@

f: re
	./$(NAME)
