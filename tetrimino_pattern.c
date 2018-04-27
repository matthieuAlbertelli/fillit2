/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 20:21:50 by malberte          #+#    #+#             */
/*   Updated: 2018/04/27 18:48:22 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "tetrimino_pattern.h"

static t_tetrimino_pattern **init_patterns_tab(unsigned int nb_patterns)
{
	t_tetrimino_pattern **patterns;
	size_t tab_size;
	
	tab_size = sizeof(t_tetrimino_pattern *) * (nb_patterns + 1);
	patterns = (t_tetrimino_pattern **)ft_memalloc(tab_size);
	if (patterns == NULL)
		
	return (patterns);
}

static t_tetrimino_pattern *init_pattern()
{
	t_tetrimino_pattern *tetri;

	tetri = (t_tetrimino_pattern *)ft_memalloc(sizeof(t_tetrimino_pattern));
	if (tetri == NULL)
		ft_on_error(NULL, NULL);
	return (tetri);
}

static int read_pattern_layout(t_tetrimino_pattern *pat, const char *src)
{
	int h;
	int w;
	int nb_block;
	int src_i;

	nb_block = 0;
	h = -1;
	src_i = 0;
	while (++h < pat->dim[HEIGHT])
	{
		w = -1;
		while (++w < pat->dim[WIDTH])
		{
			if (src[src_i] == '#')
			{
				pat->blocks_pos[nb_block][HEIGHT] = h;
				pat->blocks_pos[nb_block][WIDTH] = w;
				nb_block++;
			}
			src_i++;
		}
		src_i++;
	}
	return (src_i);
}

t_tetrimino_pattern **ft_read_patterns(const char *str)
{
	t_tetrimino_pattern **patterns;
//	char str[BUF_SIZE];
	int k;
	int nb_pat;

	k = 0;
//	file_to_str(str, file);
	nb_pat = ft_atoi(str);
	k += 3;
	patterns = init_patterns_tab(nb_pat);
	while (str[k])
	{
		--nb_pat;
		patterns[nb_pat] = init_pattern();
		ft_strncpy(patterns[nb_pat]->name, str + k, 2);
		k += 3;
		patterns[nb_pat]->dim[HEIGHT] = ft_atoi(str + k);
		k += 2;
		patterns[nb_pat]->dim[WIDTH] = ft_atoi(str + k);
		k += 2;
		k += read_pattern_layout(patterns[nb_pat], str + k);
	}
	return (patterns);
}

void ft_make_layout(int layout[NB_BLOCKS][2], int offset[2])
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

void ft_coords_to_layout(int blocks_coords[NB_BLOCKS][2])
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

t_tetrimino_pattern *ft_pattern_recognition(int pos[NB_BLOCKS][2])
{
	int block;
	int dim;
	int is_equ;
	t_tetrimino_pattern **pat;

	pat = g_patterns;
	if (pat == NULL)
		return (NULL);
	ft_coords_to_layout(pos);
	while ((*pat) != NULL)
	{
		block = 0;
		is_equ = 1;
		while (is_equ && block < NB_BLOCKS)
		{
			dim = 0;
			while (is_equ && dim < 2)
			{
				if (pos[block][dim] != (*pat)->blocks_pos[block][dim])
					is_equ = 0;
				++dim;
			}
			++block;
		}
		if (is_equ)
			return ((t_tetrimino_pattern*) (*pat));
		++pat;
	}
	return (NULL);
}
