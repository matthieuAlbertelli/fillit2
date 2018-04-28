/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 20:21:50 by malberte          #+#    #+#             */
/*   Updated: 2018/04/28 18:54:18 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "tetrimino_pattern.h"
#include "clean.h"

/*
** This function 
*/

void					ft_make_layout(t_blocks layout, int offset[2])
{
	int block;
	int dimension;

	block = 0;
	while (block < NB_BLOCKS)
	{
		dimension = 0;
		while (dimension < 2)
		{
			layout[block][dimension] -= offset[dimension];
			++dimension;
		}
		++block;
	}
}

/*
** This function 
*/

void					ft_coords_to_layout(t_blocks blocks_coords)
{
	int block;
	int dimension;
	int offset[2];

	offset[HEIGHT] = blocks_coords[0][HEIGHT];
	offset[WIDTH] = blocks_coords[0][WIDTH];
	block = 1;
	while (block < NB_BLOCKS)
	{
		dimension = 0;
		while (dimension < 2)
		{
			if (offset[HEIGHT] > blocks_coords[block][HEIGHT])
				offset[HEIGHT] = blocks_coords[block][HEIGHT];
			if (offset[WIDTH] > blocks_coords[block][WIDTH])
				offset[WIDTH] = blocks_coords[block][WIDTH];
			++dimension;
		}
		++block;
	}
	ft_make_layout(blocks_coords, offset);
}

/*
** This function compares a read tetrimino with an existing patterns in order
** to see if they are equal.
*/

static int				layout_cmp(t_blocks lay1, t_blocks lay2)
{
	int	is_equ;
	int	block;
	int	dim;

	block = 0;
	is_equ = 1;
	while (is_equ && block < NB_BLOCKS)
	{
		dim = 0;
		while (is_equ && dim < 2)
		{
			if (lay1[block][dim] != lay2[block][dim])
				is_equ = 0;
			++dim;
		}
		++block;
	}
	return (is_equ);
}

/*
** This function launches comparision between a read tetrimino and
** each tetrimino of the 'library' in order to find its pattern.
*/

t_tetrimino_pattern		*ft_pattern_recognition(int pos[NB_BLOCKS][2])
{
	t_tetrimino_pattern	**pat;

	pat = g_patterns;
	if (pat == NULL)
		ft_exit();
	ft_coords_to_layout(pos);
	while ((*pat) != NULL)
	{
		if (layout_cmp(pos, (*pat)->blocks_pos))
			return ((t_tetrimino_pattern*)(*pat));
		++pat;
	}
	return (NULL);
}

void					ft_free_patterns(void)
{
	t_tetrimino_pattern **pat;

	if (g_patterns != NULL)
	{
		pat = g_patterns;
		while (*pat)
		{
			ft_memdel((void**)pat);
			pat++;
		}
		ft_memdel((void**)&g_patterns);
	}
}
