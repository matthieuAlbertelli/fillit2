/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 12:44:42 by acoulomb          #+#    #+#             */
/*   Updated: 2018/04/29 16:20:35 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "tetris_board.h"
# include <stdlib.h>
# define ERR_MSG "error\n"

typedef struct			s_clean
{
	t_tetris_board		*tetris;
	t_tetrimino_pattern	**g_patterns;
	char				**solution;
}						t_clean;

extern					t_clean	g_clean;

/*
** g_clean is the global structure that contains all the allocated data of
** the program. At any time, if the program needs to exit, the global is freed.
*/

void					ft_clean(void);
void					ft_exit(void);
void					*ft_safe_alloc(size_t size);

#endif
