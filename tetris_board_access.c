/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris_board_access.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:25:34 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 15:23:43 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris_board.h"

int		*get_tetri_pos(const t_tetris_board *board, int tetri_index)
{
	return ((int*)board->tetriminos[tetri_index]->pos);
}

int		**get_tetri_pattern(const t_tetris_board *board, int tetri_index)
{
	return ((int **)board->tetriminos[tetri_index]->pattern->blocks_pos);
}

int		is_pos_inside(const int pos[2], int square_size)
{
	if (pos[HEIGHT] >= 0 && pos[HEIGHT] < square_size
		&& pos[WIDTH] >= 0 && pos[WIDTH] < square_size)
		return (1);
	return (0);
}

int		is_square_available(const t_tetris_board *board, int pos[2])
{
	return (board->board[pos[HEIGHT]][pos[WIDTH]]);
}

void	lock_square(t_tetris_board *board, const int pos[2], int lock_state)
{
	board->board[pos[HEIGHT]][pos[WIDTH]] = lock_state;
}
