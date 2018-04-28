/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:51:06 by malberte          #+#    #+#             */
/*   Updated: 2018/04/28 04:06:17 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include "tetrimino.h"
#include "clean.h"

static char		*read_line(int pos[NB_BLOCKS][2], int *nb_blocks, const char *buf, int height)
{
	int w;

	w = 0;
	while (w < NB_BLOCKS && buf[w])
	{
		if (buf[w] == '#')
		{
			if(*nb_blocks < NB_BLOCKS)
			{
				pos[*nb_blocks][HEIGHT] = height;
				pos[*nb_blocks][WIDTH] = w;
			}
			else 
			{
				return (NULL);
			}
			++*nb_blocks;
		}
		else if (buf[w] != '.')
			return(NULL);
		++w;
	}
	// if (w < NB_BLOCKS || buf[w] != '\n')
	// 	return(NULL);
	if (w < NB_BLOCKS)
		return (NULL);
	// if (buf[w] == '\n')
	// {
	// 	++w;
	// 	if (buf[w] == '\0')
	// 		ft_clean();
	// }
	return ((char *)(buf + w));
}

static char		*read_tetrimino(t_tetrimino **new, int *nb_tetri, const char *buf)
{
	int h;
	int nb_blocks;
	int pos[NB_BLOCKS][2];
	t_tetrimino_pattern *pat;

	nb_blocks = 0;
	h = 0;
	while (*buf && h < 3)
	{
		buf = read_line(pos, &nb_blocks, buf, h);
		if (buf == NULL)
		{
			*nb_tetri = 0;
			return (0);
		}
		if (*buf != '\n')
			ft_exit();
		++buf;
		h++;
	}
	buf = read_line(pos, &nb_blocks, buf, h);
	++h;
	if (*buf == '\n')
		++buf;
	else if (*buf != '\0')
		ft_exit();
	if (h != NB_BLOCKS)
	{
		return (NULL);
	}
	// if (*buf == '\n')
	// 	buf++;
	// else if (*buf != '\0')
	// 	return (NULL);
	pat = ft_pattern_recognition(pos);
	if (pat == NULL)
		return (NULL);
	*new = (t_tetrimino*)ft_memalloc(sizeof(t_tetrimino));
	if (*new == NULL)
	{
		return (NULL);
	}
	(*new)->pattern = pat;
	(*new)->pos[HEIGHT] = 0;
	(*new)->pos[WIDTH] = 0;
	return ((char*)buf);
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

int	ft_read_tetriminos(t_tetrimino **tetri, int *nb_tetri, const char *filename)
{
	int fd;
	char buf[BUF_SIZE];
	char *pbuf;
	ssize_t bytes;
	
	if (nb_tetri == NULL)
	{
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	ft_bzero(buf, BUF_SIZE);
	bytes = read(fd, buf, BUF_SIZE - 1);
	if (bytes == -1 || bytes == 0)
		return (0);
	close(fd);
	pbuf = buf;
	*nb_tetri = 0;
	while (*pbuf)
	{
		if (*nb_tetri == MAX_TETRIMINOS)
		{
			ft_free_tetri(tetri, nb_tetri);
			return (0);
		}
		pbuf = read_tetrimino(&(tetri[*nb_tetri]), nb_tetri, pbuf);
		if (pbuf == 0)
		{
			ft_free_tetri(tetri, nb_tetri);
			return (0);
		}
		tetri[*nb_tetri]->pos[HEIGHT] = 0;
		tetri[*nb_tetri]->pos[WIDTH] = -1;
		++*nb_tetri;
		if (*pbuf == '\n')
		{
			++pbuf;
			if (*pbuf == '\0')
				ft_exit();
		}
	}
	return (1);
}
