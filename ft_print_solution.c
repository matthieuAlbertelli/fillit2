/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_solution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:21:40 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 15:27:56 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "clean.h"
#include "tetris_board.h"
#include "position.h"

static char	**init_solution(int size)
{
	int		i;
	char	**solution;

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

static void	put_solution(char **solution, int size)
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

static void set_sol(char **solution, t_cpos pos, t_cpos offset, char c)
{
	solution[pos[HEIGHT] + offset[HEIGHT]][pos[WIDTH] + offset[WIDTH]] = c;
}

void	ft_print_solution(const t_tetris_board *board)
{
	int					i;
	int					block;
	char				**solution;
	int					offset[2];
	t_tetrimino			*tet;

	solution = init_solution(board->size);
	i = 0;
	while (i < board->nb_tetrimino)
	{
		tet = board->tetriminos[i];
		calc_offset(offset, tet->pos, tet->pattern->blocks_pos);
		solution[tet->pos[HEIGHT]][tet->pos[WIDTH]] = 'A' + i;
		block = 1;
		while (block < NB_BLOCKS)
		{
			tet = board->tetriminos[i];
			set_sol(solution, tet->pattern->blocks_pos[block], offset, 'A' + i);
			++block;
		}
		++i;
	}
	put_solution(solution, board->size);
	ft_free_solution(solution);
}

void		ft_free_solution(char **solution)
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
