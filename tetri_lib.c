/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 21:07:34 by acoulomb          #+#    #+#             */
/*   Updated: 2018/04/29 14:44:39 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetri_lib.h"

/*
** This function creates a string containing information on the 19 tetriminos
** that exist : their name, height, width and pattern. It is used to generate
** the global g_patterns who contains 19 structures t_tetrimino_pattern.
*/

char	*ft_tetri_lib(void)
{
	char *str;

	str = ft_strnew(300);
	ft_strlcat(str, NB_TETRI_LIB, 300);
	ft_strlcat(str, TETRI_I, 300);
	ft_strlcat(str, TETRI_J, 300);
	ft_strlcat(str, TETRI_J2, 300);
	ft_strlcat(str, TETRI_L, 300);
	ft_strlcat(str, TETRI_L2, 300);
	ft_strlcat(str, TETRI_O, 300);
	ft_strlcat(str, TETRI_S, 300);
	ft_strlcat(str, TETRI_Z, 300);
	ft_strlcat(str, TETRI_T, 300);
	ft_strlcat(str, TETRI_T2, 300);
	return (str);
}
