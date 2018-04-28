/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 21:06:17 by malberte          #+#    #+#             */
/*   Updated: 2018/04/28 12:47:00 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"
#include "libft/libft.h"

t_clean	g_clean;

void	ft_clean()
{
	g_clean.ft_free_tetris_board(g_clean.tetris);
	g_clean.ft_free_patterns(g_clean.g_patterns);
}

void	ft_exit()
{
	ft_clean();
	ft_putstr(ERR_MSG);
	exit(0);
}

void	*ft_safe_alloc(size_t size)
{
	void *data;

	data = ft_memalloc(size);
	if (data == NULL)
	{
		ft_exit();
	}
	return (data);
}
