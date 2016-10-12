# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: palatorr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/23 16:30:41 by palatorr          #+#    #+#              #
#    Updated: 2016/09/23 16:30:42 by palatorr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILENAMES	= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c
FILENAMES	+= ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c
FILENAMES	+= ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_get_next_line.c
FILENAMES	+= ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c
FILENAMES	+= ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c
FILENAMES	+= ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c
FILENAMES	+= ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c
FILENAMES	+= ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c
FILENAMES	+= ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c
FILENAMES	+= ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c
FILENAMES	+= ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c
FILENAMES	+= ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c
FILENAMES	+= ft_dlstnew.c ft_tabtodlst.c ft_tabtolst.c ft_makereadable.c
FILENAMES	+= ft_strrev.c ft_memsort.c ft_puttab.c ft_bsearch.c ft_nl.c
FILENAMES	+= ft_putlst.c ft_tabdup.c ft_strcmplex.c ft_tabsort.c ft_lstnew.c

NAME		= libft.a

FLAGS		= -Wall -Wextra -Werror

SRCS		= $(FILENAMES)
OBJS		= $(addprefix build/, $(FILENAMES:.c=.o))

.PHONY: all re clean fclean

all: $(NAME)

re: fclean all

clean:
	rm -rf build/

fclean: clean
	rm -f $(NAME)

build:
	@mkdir build/

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)

build/%.o: %.c libft.h | build
	@gcc $(FLAGS) -c $< -o $@
