/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris_board.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoulomb <acoulomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:14:46 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 13:53:37 by acoulomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_BOARD_H
# define TETRIS_BOARD_H

# include "tetrimino.h"

# define UNAVAILABLE_SQUARE 0
# define AVAILABLE_SQUARE 1

typedef struct	s_tetris_board
{
	char		**board;
	int			size;
	t_tetrimino	*tetriminos[MAX_TETRIMINOS];
	int			nb_tetrimino;
}				t_tetris_board;

/*
** The t_tetris_board structure stores the board in which the program solves
** the tetris, the size of the square the program is trying to put the 
** tetriminos in, the tetriminos given by the file and their number.
*/

int				ft_fill_tetrimino(t_tetris_board *board,
						int pos[2],
						int tetrimino_layout[NB_BLOCKS][2]);

void			ft_unblock_tetrimino(t_tetris_board *board,
							const int pos[2],
							const int tetrimino_layout[NB_BLOCKS][2]);

int				ft_next_available_square(int next_pos[2],
								t_tetrimino *tetrimino,
								t_tetris_board *board);

int				ft_solve_fillit(t_tetris_board *board);
void			ft_print_solution(const t_tetris_board *board);
int				ft_board_size(int nb_tetrimino);
void			ft_free_tetris_board(t_tetris_board *tetris);
static char 	**init_solution(int size);

#endif
