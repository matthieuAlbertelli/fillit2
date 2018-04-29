/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:22:24 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 13:03:57 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetris_board.h"
#include "clean.h"

void calc_offset(int offset[2], const int pos[2], const t_blocks layout)
{
	offset[HEIGHT] = pos[HEIGHT] - layout[HEIGHEST_BLOCK][HEIGHT];
	offset[WIDTH] = pos[WIDTH] - layout[HEIGHEST_BLOCK][WIDTH];
}

int is_pos_inside(const int pos[2], int square_size)
{
	if (pos[HEIGHT] >= 0 && pos[HEIGHT] < square_size
		&& pos[WIDTH] >= 0 && pos[WIDTH] < square_size)
		return (1);
	return (0);
}

int is_square_available(const t_tetris_board *board, int pos[2])
{
	return (board->board[pos[HEIGHT]][pos[WIDTH]]);
}

void lock_square(t_tetris_board *board, const int pos[2], int lock_state)
{
	board->board[pos[HEIGHT]][pos[WIDTH]] = lock_state;
}

void apply_offset(t_blocks result, const t_blocks layout, const int pos[2], const int offset[2])
{
	int block;
	
	result[HEIGHEST_BLOCK][HEIGHT] = pos[HEIGHT];
	result[HEIGHEST_BLOCK][WIDTH] = pos[WIDTH];
	block = 1;
	while (block < NB_BLOCKS)
	{
		result[block][HEIGHT] = layout[block][HEIGHT] + offset[HEIGHT];
		result[block][WIDTH] = layout[block][WIDTH] + offset[WIDTH];
		++block;
	}
}

void poscpy(int dst[2], const int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void posinit(int dst[2], int x, int y)
{
	dst[0] = x;
	dst[1] = y;
}

int *pos_add_offset(int dst[2], int pos[2], int offset[2])
{
	dst[0] = pos[0] + offset[0];
	dst[1] = pos[1] + offset[1];
	return ((int*)dst);
}

int *pos_retrieve_offset(int dst[2], int pos[2], int offset[2])
{
	dst[0] = pos[0] - offset[0];
	dst[1] = pos[1] - offset[1];
	return ((int*)dst);
}

int *get_tetri_pos(const t_tetris_board *board, int tetri_index)
{
	return ((int*)board->tetriminos[tetri_index]->pos);
}

int **get_tetri_pattern(const t_tetris_board *board, int tetri_index)
{
	return ((int **)board->tetriminos[tetri_index]->pattern->blocks_pos);
}

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

void	ft_unblock_tetrimino(t_tetris_board *board,	const int pos[2],
							const int layout[NB_BLOCKS][2])
{
	int block;
	t_blocks unblock_pos;
	int offset[2];

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

static char **init_solution(int size)
{
	int i;
	char **solution;
	
	i = 0;
	solution = (char **)ft_safe_alloc(sizeof(char*) * (size + 1));
	g_clean.solution = solution;
	while (i < size)
	{
		solution[i] = (char *)ft_safe_alloc(sizeof(char) * (size + 1));
		ft_memset(solution[i], '.', size);
		solution[i][size] = '\0';
		++i;
	}
	return (solution);
}

static void put_solution(char **solution, int size)
{
	int i;
	i = 0;
	while (i < size)
	{
		ft_putstr(solution[i]);
		ft_putchar('\n');
		++i;
	}
}

void	ft_print_solution(const t_tetris_board *board)
{
	int					i;
	int					block;
	char				**solution;
	int					offset[2];
	t_tetrimino_pattern	*pattern;

	i = 0;
	solution = NULL;
	solution = init_solution(board->size);
	i = 0;
	while (i < board->nb_tetrimino)
	{
		pattern = board->tetriminos[i]->pattern;
		calc_offset(offset, board->tetriminos[i]->pos, pattern->blocks_pos);
		solution[board->tetriminos[i]->pos[HEIGHT]][board->tetriminos[i]->pos[WIDTH]] = 'A' + i;
		block = 1;
		while (block < NB_BLOCKS)
		{
			pattern = board->tetriminos[i]->pattern;
			solution[pattern->blocks_pos[block][HEIGHT] + offset[HEIGHT]]
					[pattern->blocks_pos[block][WIDTH] + offset[WIDTH]] = 'A' + i;
			++block;
		}
		++i;
	}
	put_solution(solution, board->size);
	ft_free_solution(solution);
}

void	ft_free_solution(char **solution)
{
	int i;

	i = 0;
	if (solution)
	{
		while (solution[i])
		{
			ft_memdel((void**)&solution[i]);
			i++;
		}
		ft_memdel((void**)&solution);
	}
}

int		ft_board_size(int nb_tetrimino)
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
