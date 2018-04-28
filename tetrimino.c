/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:51:06 by malberte          #+#    #+#             */
/*   Updated: 2018/04/28 15:08:55 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include "tetrimino.h"

int		ft_tetri_to_str(char *buf, size_t buf_size, char *filename)
{
	int		fd;
	ssize_t	bytes;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	ft_bzero(buf, buf_size);
	bytes = read(fd, buf, buf_size - 1);
	if (bytes == -1 || bytes == 0)
		return (0);
	close(fd);
	return (1);
}

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
