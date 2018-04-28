/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 21:07:34 by acoulomb          #+#    #+#             */
/*   Updated: 2018/04/28 12:51:45 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tetri_lib.h"

char	*ft_tetri_lib()
{
	char *str;

	str = ft_strnew(400);
	ft_strlcat(str, NB_TETRI_LIB, 400);
	ft_strlcat(str, TETRI_I, 400);
	ft_strlcat(str, TETRI_J, 400);
	ft_strlcat(str, TETRI_J2, 400);
	ft_strlcat(str, TETRI_L, 400);
	ft_strlcat(str, TETRI_L2, 400);
	ft_strlcat(str, TETRI_O, 400);
	ft_strlcat(str, TETRI_S, 400);
	ft_strlcat(str, TETRI_Z, 400);
	ft_strlcat(str, TETRI_T, 400);
	ft_strlcat(str, TETRI_T2, 400);
	return (str);
}
