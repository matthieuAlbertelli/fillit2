#include "clean.h"
#include "libft/libft.h"

void ft_clean()
{
	clean.ft_free_tetris_board(clean.tetris);
	clean.ft_free_patterns(clean.g_patterns);
}

void ft_exit()
{
	ft_clean();
	ft_putstr(ERR_MSG);
	exit (0);
}

void *ft_safe_alloc(size_t size)
{
	void *data;

	data = ft_memalloc(size);
	if (data == NULL)
	{
		ft_exit();
	}
	return (data);
}