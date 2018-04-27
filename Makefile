# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 22:08:39 by acoulomb          #+#    #+#              #
#    Updated: 2018/04/27 21:38:12 by acoulomb         ###   ########.fr        #
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

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIB)

%.o : %.c
	gcc $(FLAGS) -c $^

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

g: re $(OBJS)
	gcc $(FLAGS) -g $(SRC) $(LIB)