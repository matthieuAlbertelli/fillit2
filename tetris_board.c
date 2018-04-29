/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:22:24 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 15:20:27 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetris_board.h"
#include "clean.h"
#include "position.h"

int		ft_fill_tetrimino(t_tetris_board *board, int pos[2], t_blocks layout)
{
	int block;
	int fill_pos[NB_BLOCKS][2];
	int offset[2];

	if (pos[WIDTH] == -1)
		return (0);
	calc_offset(offset, pos, layout);
	poscpy(fill_pos[HEIGHEST_BLOCK], pos);
	block = 1;
	while (block < NB_BLOCKS)
	{
		fill_pos[block][HEIGHT] = layout[block][HEIGHT] + offset[HEIGHT];
		fill_pos[block][WIDTH] = layout[block][WIDTH] + offset[WIDTH];
		if (!(is_pos_inside(fill_pos[block], board->size)
			&& is_square_available(board, fill_pos[block])))
			return (0);
		++block;
	}
	block = 0;
	while (block < NB_BLOCKS)
	{
		lock_square(board, fill_pos[block], UNAVAILABLE_SQUARE);
		++block;
	}
	return (1);
}

void	ft_unblock_tetrimino(t_tetris_board *board, const int pos[2],
								const int layout[NB_BLOCKS][2])
{
	int			block;
	t_blocks	unblock_pos;
	int			offset[2];

	if (pos[WIDTH] != -1)
	{
		calc_offset(offset, pos, layout);
		apply_offset(unblock_pos, layout, pos, offset);
		block = 0;
		while (block < NB_BLOCKS)
		{
			lock_square(board, unblock_pos[block], AVAILABLE_SQUARE);
			++block;
		}
	}
}

int		ft_next_available_square(int next_pos[2],
								t_tetrimino *tetrimino,
								t_tetris_board *board)
{
	int h;
	int w;

	if (next_pos == NULL || tetrimino == NULL || board == NULL)
		return (0);
	posinit(next_pos, 0, -1);
	h = tetrimino->pos[HEIGHT];
	w = tetrimino->pos[WIDTH] + 1;
	while (h < board->size)
	{
		while (w < board->size)
		{
			if (board->board[h][w] == AVAILABLE_SQUARE)
			{
				posinit(next_pos, h, w);
				if (ft_fill_tetrimino(board, next_pos, \
					tetrimino->pattern->blocks_pos))
					return (1);
			}
			++w;
		}
		++h;
		w = 0;
	}
	return (0);
}

int		ft_solve_fillit(t_tetris_board *board)
{
	int n;
	int next_pos[2];

	n = 0;
	while (n > -1)
	{
		if (ft_next_available_square(next_pos, board->tetriminos[n], board))
		{
			poscpy(board->tetriminos[n]->pos, next_pos);
			++n;
		}
		else
		{
			posinit(board->tetriminos[n]->pos, 0, -1);
			--n;
			if (n != -1)
				ft_unblock_tetrimino(board, board->tetriminos[n]->pos, \
							board->tetriminos[n]->pattern->blocks_pos);
		}
		if (n == board->nb_tetrimino)
			return (1);
	}
	board->size++;
	if (ft_solve_fillit(board))
		return (1);
	return (0);
}

void	ft_free_tetris_board(t_tetris_board *tetris)
{
	int i;

	ft_free_tetri(tetris->tetriminos, &(tetris->nb_tetrimino));
	i = 0;
	while (i < tetris->size)
	{
		ft_memdel((void**)&tetris->board[i]);
		++i;
	}
	ft_memdel((void**)&(tetris->board));
}
