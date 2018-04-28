/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_tetriminos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:39:31 by malberte          #+#    #+#             */
/*   Updated: 2018/04/28 14:57:42 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include "tetrimino.h"
#include "clean.h"

static char     *read_line(t_blocks pos, int *nb_blk, const char *buf, int h)
{
	int w;

	w = 0;
	while (w < NB_BLOCKS && buf[w])
	{
		if (buf[w] == '#')
		{
			if (*nb_blk < NB_BLOCKS)
			{
				pos[*nb_blk][HEIGHT] = h;
				pos[*nb_blk][WIDTH] = w;
			}
			else
				ft_exit();
			++*nb_blk;
		}
		else if (buf[w] != '.')
			ft_exit();
		++w;
	}
	if (w < NB_BLOCKS)
		ft_exit();
	return ((char *)(buf + w));
}

static char		*read_4lines(const char *buf, t_blocks pos)
{
	int					nb_blocks;
	int					h;

	nb_blocks = 0;
	h = 0;
	while (*buf && h < 3)
	{
		buf = read_line(pos, &nb_blocks, buf, h);
		if (buf == NULL)
			ft_exit();
		if (*buf != '\n')
			ft_exit();
		++buf;
		h++;
	}
	buf = read_line(pos, &nb_blocks, buf, h);
	++h;
	if (h != NB_BLOCKS)
		ft_exit();
	return ((char *)buf);
}

static char     *check_tetrimino_end(const char *buf)
{
	if (*buf == '\n')
		++buf;
	else if (*buf != '\0')
		ft_exit();
	return ((char *)buf);
}

static char		*read_tetrimino(t_tetrimino **new, const char *buf)
{
	t_blocks			pos;
	t_tetrimino_pattern	*pat;

	buf = read_4lines(buf, pos);
	buf = check_tetrimino_end(buf);
	
	pat = ft_pattern_recognition(pos);
	if (pat == NULL)
		ft_exit();
	*new = (t_tetrimino*)ft_memalloc(sizeof(t_tetrimino));
	if (*new == NULL)
		ft_exit();
	(*new)->pattern = pat;
	(*new)->pos[HEIGHT] = 0;
	(*new)->pos[WIDTH] = 0;
	return ((char*)buf);
}

int		ft_read_tetriminos(t_tetrimino **tetri, int *nb_tetri, \
							const char *filename)
{
	int		fd;
	char	buf[BUF_SIZE];
	char	*pbuf;
	ssize_t	bytes;

	if (nb_tetri == NULL)
		return (0);
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
			ft_exit();
		pbuf = read_tetrimino(&(tetri[*nb_tetri]), pbuf);
		if (pbuf == 0)
			ft_exit();
		tetri[*nb_tetri]->pos[HEIGHT] = 0;
		tetri[*nb_tetri]->pos[WIDTH] = -1;
		++*nb_tetri;
		if (*pbuf == '\n')
		{
			++pbuf;
			if (*pbuf == '\0')
				ft_exit();
		}
		else if (*pbuf != '\0')
			ft_exit();
	}
	return (1);
}
