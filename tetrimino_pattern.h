/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino_pattern.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:02:13 by malberte          #+#    #+#             */
/*   Updated: 2018/04/27 01:58:30 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIMINOS_H
# define TETRIMINOS_H

# define HEIGHT 0
# define WIDTH 1
# define HEIGHEST_BLOCK 0
# define LEFTMOST_BLOCK 1
# define NB_BLOCKS 4
# define BLOCK_CHARACTER '#'
# define BUF_SIZE 2000

typedef struct 	s_tetrimino_pattern
{
	int	blocks_pos[NB_BLOCKS][2];
	char			name[3];
	int 			dim[2];
}				t_tetrimino_pattern;

extern t_tetrimino_pattern **g_patterns;

t_tetrimino_pattern **ft_read_patterns(const char *file);
void ft_coords_to_layout(int pos[NB_BLOCKS][2]);
t_tetrimino_pattern *ft_pattern_recognition(int pos[NB_BLOCKS][2]);

#endif