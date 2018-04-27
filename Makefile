# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malberte <malberte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 22:08:39 by acoulomb          #+#    #+#              #
#    Updated: 2018/04/26 09:59:29 by malberte         ###   ########.fr        #
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
		safe_exit.c

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