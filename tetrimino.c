/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:51:06 by malberte          #+#    #+#             */
/*   Updated: 2018/04/28 14:43:39 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetrimino.h"

void	ft_free_tetri(t_tetrimino **tetri, int *nb_tetri)
{
	int i;

	i = 0;
	while (i < *nb_tetri)
	{
		ft_memdel((void**)&(tetri[i]));
		i++;
	}
	*nb_tetri = 0;
}
