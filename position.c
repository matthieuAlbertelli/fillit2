/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:57:24 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 16:19:16 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "position.h"

/*
** These functions are used in the testing process to put tetriminos.
*/

void	poscpy(t_pos dst, t_cpos src)
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	posinit(t_pos dst, int x, int y)
{
	dst[0] = x;
	dst[1] = y;
}

/*
** On s'en sert des deux suivantes??
*/

int		*pos_add_offset(t_pos dst, t_pos pos, t_pos offset)
{
	dst[0] = pos[0] + offset[0];
	dst[1] = pos[1] + offset[1];
	return ((int*)dst);
}

int		*pos_retrieve_offset(t_pos dst, t_pos pos, t_pos offset)
{
	dst[0] = pos[0] - offset[0];
	dst[1] = pos[1] - offset[1];
	return ((int*)dst);
}
