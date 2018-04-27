#ifndef CLEAN_H
# define CLEAN_H

#include "tetris_board.h"
#include <stdlib.h>
#define ERR_MSG "error\n"

typedef struct			s_clean
{
	t_tetris_board 		*tetris;
	void				(*ft_free_tetris_board)(t_tetris_board *tetris);
	t_tetrimino_pattern	**g_patterns;
	void 				(*ft_free_patterns)(t_tetrimino_pattern **g_patterns);
}						t_clean;

extern					t_clean	clean;

void	ft_clean();
void	*ft_safe_alloc(size_t size);
void	ft_exit();

#endif