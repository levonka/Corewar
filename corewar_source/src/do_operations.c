/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnikia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:05:50 by cnikia            #+#    #+#             */
/*   Updated: 2020/01/09 14:05:50 by cnikia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vis.h"
#include "corewar.h"

void		move_cursor(t_gstate *gstate, t_cursor *cursor)
{
	if (gstate->f_v)
		gstate->vis->map[cursor->pos].is_cursor = 0;
	cursor->pos = get_map_ind(cursor->pos, cursor->steps);
	cursor->steps = 0;
	if (gstate->f_v)
		gstate->vis->map[cursor->pos].is_cursor = 1;
	ft_bzero(cursor->args, sizeof(unsigned char) * 3);
}

void		do_operation(t_gstate *gstate, t_cursor *cursor)
{
	t_op	curr_op;

	curr_op = g_op_tab[(int)cursor->current_op];
	if (cursor->current_op >= 0x01 && cursor->current_op <= 0x10)
	{
		if (argument_code_type_check(cursor, gstate->arena, curr_op) == 0)
		{
			cursor->steps = 0;
			g_op_tab[cursor->current_op].func(gstate, cursor);
		}
	}
	else
		cursor->steps = 1;
	move_cursor(gstate, cursor);
}
