/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:43:38 by malberte          #+#    #+#             */
/*   Updated: 2018/04/28 12:16:32 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIMINO_H
# define TETRIMINO_H

# include "tetrimino_pattern.h"
# define MAX_TETRIMINOS 26
# define TETRIMINO_MAP_SIZE 20
# define TETRIMINO_INPUT_SIZE 20

typedef struct 	s_tetrimino
{
	t_tetrimino_pattern *pattern;
	int 				pos[2];
}				t_tetrimino;

int	ft_read_tetriminos(t_tetrimino **tetri, int *nb_tetri, const char *filename);
void	ft_free_tetri(t_tetrimino **tetri, int *nb_tetri);

#endif