/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:22:24 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 16:38:58 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetris_board.h"
#include "clean.h"
#include "position.h"

void	ft_init_board(t_tetris_board *board)
{
	unsigned int i;
	unsigned int size;

	size = MAX_TETRIMINOS * NB_BLOCKS;
	i = 0;
	board->board = (char**)ft_safe_alloc(sizeof(char*) * size * 2);
	board->size = ft_board_size(board->nb_tetrimino);
	while (i < size)
	{
		board->board[i] = (char*)ft_safe_alloc(sizeof(char) * size);
		ft_memset(board->board[i], 1, size);
		++i;
	}
}

void	ft_free_tetris_board(t_tetris_board *tetris)
{
	int i;

	i = 0;
	ft_free_tetri(tetris->tetriminos, &(tetris->nb_tetrimino));
	while (i < tetris->size)
	{
		ft_memdel((void**)&tetris->board[i]);
		++i;
	}
	ft_memdel((void**)&(tetris->board));
}
