# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 22:08:39 by acoulomb          #+#    #+#              #
#    Updated: 2018/04/28 15:20:35 by acoulomb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:

#BINARIES:
CC          = /usr/bin/clang
RM          = /bin/rm
MAKE        = /usr/bin/make

#FLAGS:
CC = clang
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -L $(LFTPATH) -lft

#EXECUTALE:
NAME = fillit

#SRCS:
SRCS =	\
		main.c \
		tetrimino.c \
		tetrimino_pattern.c \
		tetris_board.c \
		tetri_lib.c \
		clean.c \
		ft_read_patterns.c \
		ft_read_tetriminos.c

#OBJ:
OBJS = $(SRCS:.c=.o)

#HEADERS:
HEADS =	\
		clean.h \
		tetrimino.h \
		tetris_board.h \
		tetri_lib.h \
		tetrimino_pattern.h

#LIB:
LFTPATH     = libft
LIBFT       = $(LFTPATH)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c $(HEADS)
	@$(CC) -c $(FLAGS) -o $@ $<

$(LIBFT):
	@$(MAKE) -C $(LFTPATH)

clean:
	@$(MAKE) -C $(LFTPATH) clean
	@$(RM) -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LFTPATH) fclean
	@$(RM) -rf $(NAME)

cleanlib:
	$(MAKE) clean -C $(LFTPATH)

re: fclean all

g: re $(OBJS)
	$(CC) $(FLAGS) -g $(SRCS) $(LIBFT)

.PHONY = re all clean fclean g