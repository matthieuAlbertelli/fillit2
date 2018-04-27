/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:22:24 by malberte          #+#    #+#             */
/*   Updated: 2018/04/25 19:51:30 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetris_board.h"

//Ces deux fonctions peuvent etre regroupees en une au prix d'operations supplementaires
//en stockant les positions de remplissage depuis une fonction dediee.

//precondition: pos est libre
int ft_fill_tetrimino(	t_tetris_board *board,
						int pos[2],
						int tetrimino_layout[NB_BLOCKS][2])
{
	int block;
	int fill_pos[NB_BLOCKS][2];
	int offset[2];

	if (pos[WIDTH] == -1)
		return (0);
	offset[HEIGHT] = pos[HEIGHT] - tetrimino_layout[HEIGHEST_BLOCK][HEIGHT];
	offset[WIDTH] = pos[WIDTH] - tetrimino_layout[HEIGHEST_BLOCK][WIDTH];
	// if (offset[HEIGHT] < 0 || offset[WIDTH] < 0)
	// 	return (0);
	fill_pos[HEIGHEST_BLOCK][HEIGHT] = pos[HEIGHT];
	fill_pos[HEIGHEST_BLOCK][WIDTH] = pos[WIDTH];
	block = 1;
	while (block < NB_BLOCKS)
	{
		fill_pos[block][HEIGHT] = tetrimino_layout[block][HEIGHT] + offset[HEIGHT];
		fill_pos[block][WIDTH] = tetrimino_layout[block][WIDTH] + offset[WIDTH];
		if (fill_pos[block][HEIGHT] < 0 || fill_pos[block][HEIGHT] >= board->size
			|| fill_pos[block][WIDTH] < 0 || fill_pos[block][WIDTH] >= board->size
			|| board->board[fill_pos[block][HEIGHT]][fill_pos[block][WIDTH]] == UNAVAILABLE_SQUARE)
			{
				return (0);
			}
		++block;
	}
	block = 0;
	while (block < NB_BLOCKS)
	{
		board->board[fill_pos[block][HEIGHT]][fill_pos[block][WIDTH]] = UNAVAILABLE_SQUARE;
		++block;
	}
	return (1);
}

void ft_unblock_tetrimino(	t_tetris_board *board,
							const int pos[2],
							const int tetrimino_layout[NB_BLOCKS][2])
{
	int block;
	int unblock_pos[NB_BLOCKS][2];
	int offset[2];

	if (pos[WIDTH] != -1)
	{
		offset[HEIGHT] = pos[HEIGHT] - tetrimino_layout[HEIGHEST_BLOCK][HEIGHT];
		offset[WIDTH] = pos[WIDTH] - tetrimino_layout[HEIGHEST_BLOCK][WIDTH];
		unblock_pos[HEIGHEST_BLOCK][HEIGHT] = pos[HEIGHT];
		unblock_pos[HEIGHEST_BLOCK][WIDTH] = pos[WIDTH];
		block = 1;
		while (block < NB_BLOCKS)
		{
			unblock_pos[block][HEIGHT] = tetrimino_layout[block][HEIGHT] + offset[HEIGHT];
			unblock_pos[block][WIDTH] = tetrimino_layout[block][WIDTH] + offset[WIDTH];
			++block;
		}
		block = 0;
		while (block < NB_BLOCKS)
		{
			board->board[unblock_pos[block][HEIGHT]][unblock_pos[block][WIDTH]] = AVAILABLE_SQUARE;
			++block;
		}
	}
}

int	ft_next_available_square(	int next_pos[2],
								t_tetrimino *tetrimino,
								t_tetris_board *board)
{	
	int h;
	int w;
	
	if (next_pos == NULL || tetrimino == NULL || board == NULL)
		return (0);
	next_pos[HEIGHT] = 0;
	next_pos[WIDTH] = -1;
	h = tetrimino->pos[HEIGHT];
	w = tetrimino->pos[WIDTH] + 1;
//	if (w == -1)
//		w = 0;
	while (h < board->size)
	{
		while (w < board->size)
		{
			if (board->board[h][w] == AVAILABLE_SQUARE)
			{
				next_pos[HEIGHT] = h;
				next_pos[WIDTH] = w;
				if (ft_fill_tetrimino(board, next_pos, tetrimino->pattern->blocks_pos))
					return (1);
			}
			++w;
		}
		++h;
		w = 0;
	}
	return (0);
}

int ft_solve_fillit(t_tetris_board *board)
{
	int n;
	int next_pos[2];

	n = 0;
	while (n > -1)
	{
		if (ft_next_available_square(next_pos, board->tetriminos[n], board))
		{
			board->tetriminos[n]->pos[HEIGHT] = next_pos[HEIGHT];
			board->tetriminos[n]->pos[WIDTH] = next_pos[WIDTH];
			++n;
		}
		else
		{
			board->tetriminos[n]->pos[HEIGHT] = 0;
			board->tetriminos[n]->pos[WIDTH] = -1;
			--n;
			if (n != -1)
			{
				ft_unblock_tetrimino(board, board->tetriminos[n]->pos, board->tetriminos[n]->pattern->blocks_pos);
			}
		}
		if (n == board->nb_tetrimino)
			return (1);
	}
	board->size++;
	if(ft_solve_fillit(board))
		return (1);
	return (0);
}

void ft_print_solution(const t_tetris_board *board)
{
	int i;
	int block;
	char solution[board->size + 1][board->size + 1];
	int offset[2];
	t_tetrimino_pattern *pattern;

	i = 0;
	while (i < board->size)
	{
		ft_memset(solution[i], '.', board->size);
		solution[i][board->size] = '\0';
		++i;
	}
	i = 0;
	while (i < board->nb_tetrimino)
	{
		offset[HEIGHT] = board->tetriminos[i]->pos[HEIGHT] - board->tetriminos[i]->pattern->blocks_pos[HEIGHEST_BLOCK][HEIGHT];
		offset[WIDTH] = board->tetriminos[i]->pos[WIDTH] - board->tetriminos[i]->pattern->blocks_pos[HEIGHEST_BLOCK][WIDTH];
		solution[board->tetriminos[i]->pos[HEIGHT]][board->tetriminos[i]->pos[WIDTH]] = 'A' + i;
		block = 1;
		while (block < NB_BLOCKS)
		{
			pattern = board->tetriminos[i]->pattern;
			solution[pattern->blocks_pos[block][HEIGHT] + offset[HEIGHT]][pattern->blocks_pos[block][WIDTH] + offset[WIDTH]] = 'A' + i;
			++block;
		}
		++i;
	}
	i = 0;
	while (i < board->size)
	{
		ft_putstr(solution[i]);
		ft_putchar('\n');
		++i;
	}
}

int ft_board_size(int nb_tetrimino)
{
	int board_size;
	int i;

	board_size = nb_tetrimino * NB_BLOCKS;
	if (board_size <= 0)
		return (0);
	i = 1;
	while (board_size >= (i * i))
	{
		if (board_size == (i * i))
			return (i);
		i++;
	}
	return (i);
}

void ft_free_tetris_board(t_tetris_board *tetris)
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
