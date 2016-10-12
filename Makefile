# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: palatorr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/26 12:15:50 by palatorr          #+#    #+#              #
#    Updated: 2016/10/12 14:46:13 by palatorr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILENAMES	= main.c dungeon.c monster.c player.c

NAME		= rogue
FLAGS		= -Wall -Wextra -Werror

LIBFT		= ./libft/libft.a
LIBFTDIR	= ./libft/

SRC			= $(FILENAMES)
OBJ			= $(addprefix $(OBJDIR),$(SRC:.c=.o))

INCDIR		= ./includes/
SRCDIR		= ./src/
OBJDIR		= ./obj/

all: libft obj $(NAME)

re: fclean all

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

obj:
	@mkdir -p $(OBJDIR)

libft:
	$(LIBFT)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@gcc $(FLAGS) -I $(LIBFTDIR) -I $(INCDIR) -c $< -o $@

$(NAME): $(OBJ)
	gcc $(FLAGS) $^ -o $@ -L $(LIBFTDIR) -lft

f: re
	./$(NAME)
