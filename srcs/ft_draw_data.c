/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 05:46:25 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 08:02:56 by ggerardy         ###   ########.fr       */
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

void	ft_draw_sq(t_filler *fl, t_point pos, int pl)
{
	static int side = 0;
	t_point ps;

	side = (!side) ? (1000 - 6 - fl->w + 1) / fl->w : side;
	ps.x = 3 + pos.x * (side + 1);
	ps.y = 3 + pos.y * (side + 1);
	ft_draw_rect(fl, (t_point){side, side}, (t_point){ps.x, ps.y}, )
}

void	ft_draw_base(t_filler *fl)
{
	fl->p1 = ft_toupper_str(fl->p1);
	fl->p2 = ft_toupper_str(fl->p2);


	int i = 0;
	while (i <= 1000)
	{
		mlx_pixel_put(fl->mlx_ptr, fl->win_ptr, 1300, i, 0x00ff00ff);
		++i;
	}
	mlx_string_put(fl->mlx_ptr, fl->win_ptr, 1300 - 30 - (int)ft_strlen(fl->p1) * 10, 80, 0x0000b289, fl->p1);
	mlx_string_put(fl->mlx_ptr, fl->win_ptr, 1300 - 30, 80, 0x00909090, "  VS  ");
	mlx_string_put(fl->mlx_ptr, fl->win_ptr, 1300 + 30, 80, 0x00be3f43, fl->p2);

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