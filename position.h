/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malberte <malberte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 14:12:05 by malberte          #+#    #+#             */
/*   Updated: 2018/04/29 14:18:49 by malberte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSITION_H
# define POSITION_H

typedef int t_pos[2];
typedef const int t_cpos[2];

void poscpy(t_pos dst, t_cpos src);
void posinit(t_pos dst, int x, int y);
int *pos_add_offset(t_pos dst, t_pos pos, t_pos offset);
int *pos_retrieve_offset(t_pos dst, t_pos pos, t_pos offset);

#endif