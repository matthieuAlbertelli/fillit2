# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malberte <malberte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 22:08:39 by acoulomb          #+#    #+#              #
#    Updated: 2018/04/28 02:39:41 by malberte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY = re all clean fclean
.SUFFIXES:

NAME = fillit

SRC =	\
		main.c \
		tetrimino.c \
		tetrimino_pattern.c \
		tetris_board.c \
		tetri_lib.c \
		clean.c

OBJS = $(SRC:.c=.o)
LIB = ./libft/libft.a

CC = clang
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB)

%.o : %.c
	$(CC) $(FLAGS) -c $^

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

g: re $(OBJS)
	$(CC) $(FLAGS) -g $(SRC) $(LIB)