/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 21:07:34 by acoulomb          #+#    #+#             */
/*   Updated: 2018/04/27 21:11:27 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char *ft_tetri_lib(char *str);
{
	char str[1];
	
	str[0] = '/0';
	ft_strjoin(str, NB_TETRI_LIB);
	ft_strjoin(str, TETRI_I);
	ft_strjoin(str, TETRI_J);
	ft_strjoin(str, TETRI_L);
	ft_strjoin(str, TETRI_O);
	ft_strjoin(str, TETRI_S);
	ft_strjoin(str, TETRI_Z);
	ft_strjoin(str, TETRI_T);
	return (str);
}