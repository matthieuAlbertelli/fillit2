/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 21:10:38 by malberte          #+#    #+#             */
/*   Updated: 2018/04/27 23:10:53 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetris_board.h"
#include "tetri_lib.h"
#include <stdlib.h>
#include "clean.h"

t_tetrimino_pattern **g_patterns;

void	ft_usage(int ac)
{
	if (ac == 1)
		ft_putstr("usage:\t./fillit source_file\n\tno input file\n");
	if (ac > 2)
		ft_putstr("usage:\t./fillit source_file\n\ttoo many input files\n");
	exit(0);
}

int		main(int argc, char **argv)
{
	t_tetris_board	board;
	int 			i;
	char			*str;

	if (argc != 2)
		ft_usage(argc);
	clean.tetris = &board;
    clean.ft_free_tetris_board = &ft_free_tetris_board;
    clean.g_patterns = g_patterns;
    clean.ft_free_patterns = &ft_free_patterns;   
	str = NULL;
	str = ft_tetri_lib();
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

// int main(int argc, char **argv)
// {
//     t_tetris_board board;
//     int i;
//     if (argc != 2)
//         ft_usage(argc);
//     clean.tetris = &board;
//     clean.ft_free_tetris_board = &ft_free_tetris_board;
//     clean.g_patterns = g_patterns;
//     clean.ft_free_patterns = &ft_free_patterns;     
//     g_patterns = ft_read_patterns("tetriminos.txt");
//     ft_read_tetriminos(board.tetriminos, &(board.nb_tetrimino), argv[1]);
// //  board.board = (char**)ft_memalloc(sizeof(char*) * MAX_TETRIMINOS * NB_BLOCKS * 2);
//     board.board = (char**)ft_safe_alloc(sizeof(char*) * MAX_TETRIMINOS * NB_BLOCKS * 2);
//     board.size = ft_board_size(board.nb_tetrimino);
//     i = 0;
//     while (i < MAX_TETRIMINOS * NB_BLOCKS)
//     {
// //      board.board[i] = (char*)ft_memalloc(sizeof(char) * MAX_TETRIMINOS * NB_BLOCKS);
//         board.board[i] = (char*)ft_safe_alloc(sizeof(char) * MAX_TETRIMINOS * NB_BLOCKS);
//         ft_memset(board.board[i], 1, MAX_TETRIMINOS * NB_BLOCKS);
//         ++i;
//     }
//     if (!ft_solve_fillit(&board))
//         ft_exit();
//     ft_print_solution(&board);
//     ft_clean();
//     return (0);
// }