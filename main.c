/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 21:10:38 by malberte          #+#    #+#             */
/*   Updated: 2018/04/27 03:51:49 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetris_board.h"

t_tetrimino_pattern **g_patterns;

void	ft_usage(int ac)
{
	if (ac == 1)
		ft_putstr("usage:\t./fillit source_file\n\tno input file\n");
	if (ac > 2)
		ft_putstr("usage:\t./fillit source_file\n\ttoo many input files\n");
}

int		main(int argc, char **argv)
{
	t_tetris_board	board;
	int 			i;
	char			*str;

	ft_strjoin(str, "19\nI1 4 1\n#\n#\n#\n#\nI2 1 4\n####\nJ1 2 3\n###\n..#\nJ2 2 3\n#..\n###\nJ3 3 2\n##\n#.\n#.\nJ4 3 2\n.#\n.#\n##\nL1 2 \
3\n###\n#..\nL2 2 3\n..#\n###\nL3 3 2\n#.\n#.\n##\nL4 3 \
2\n##\n.#\n.#\nO1 2 2\n##\n##\nS1 2 3\n.##\n##.\nS2 3 2\n#.\n##\n.#\nZ1 \
2 3\n##.\n.##\nZ2 3 2\n.#\n##\n#.\nT1 2 3\n.#.\n###\nT2 2 3\n###\n.#.\nT3 \
3 2\n#.\n##\n#.\nT4 3 2\n.#\n##\n.#");

	if (argc != 2)
	{
		ft_usage(argc);
		return (0);
	}
	g_patterns = ft_read_patterns(str);
	if (!ft_read_tetriminos(board.tetriminos, &(board.nb_tetrimino), argv[1]))
	{
		ft_putstr("error\n");
		return (0);
	}
	board.board = (char**)ft_memalloc(sizeof(char*) * MAX_TETRIMINOS * NB_BLOCKS * 2);
	if (board.board == NULL)
	{
		ft_putstr("error\n");
		return (0);
	}
	board.size = ft_board_size(board.nb_tetrimino);
	i = 0;
	while (i < MAX_TETRIMINOS * NB_BLOCKS)
	{
		board.board[i] = (char*)ft_memalloc(sizeof(char) * MAX_TETRIMINOS * NB_BLOCKS);
		ft_memset(board.board[i], 1, MAX_TETRIMINOS * NB_BLOCKS);
		++i;
	}
	if (!ft_solve_fillit(&board))
	{
		ft_putstr("error\n");
		return (0);
	}
	ft_print_solution(&board);
	ft_free_tetris_board(&board);
	return (0);
}