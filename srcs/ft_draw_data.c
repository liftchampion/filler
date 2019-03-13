/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 05:46:25 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 07:09:42 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "ft_filler_vis.h"

void 	ft_draw_rect(t_filler *fl, t_point size, t_point pos, int color)
{
	int x;
	int y;
	int line_count = 0;

	y = pos.y;
	while (y < pos.y + size.y)
	{
		x = pos.x;
		while (x < pos.x + size.x)
		{
			mlx_pixel_put(fl->mlx_ptr, fl->win_ptr, x, y, color);
			++x;
		}
		++y;
		++line_count;
		if (line_count && !(line_count % 100))
			mlx_do_sync(fl->mlx_ptr);
	}
}


void	ft_draw_base(t_filler *fl)
{
	char *names;

	fl->p1 = ft_toupper_str(fl->p1);
	fl->p2 = ft_toupper_str(fl->p2);

}

/*
int 	ft_find_sq_size(t_filler *fl)
{
	double tmp;

	tmp = (1000. - fl->w) / fl->w;
}

void	ft_main_drawer(t_filler *fl)
{
	static int sq_size = 0;

	sq_size = (!sq_size) ? fl->w
}*/