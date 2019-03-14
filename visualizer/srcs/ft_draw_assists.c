/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_assists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:31:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 22:16:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "ft_filler_vis.h"

void		ft_draw_rect(t_filler *fl, t_point size, t_point pos, int color)
{
	int x;
	int y;

	y = pos.y;
	while (y < pos.y + size.y)
	{
		x = pos.x;
		while (x < pos.x + size.x)
		{
			ft_pix_put_img(fl, x, y, color);
			++x;
		}
		++y;
	}
}

void		ft_draw_sq(t_filler *fl, t_point pos, int pl)
{
	static int	side = 0;
	static int	start_x = 0;
	static int	start_y = 0;
	static int	colors[] = {RED, DARK_RED, GREEN, DARK_GREEN, LIGHT_GRAY,
							GRAY_RED, GRAY_GREEN};
	t_point		ps;

	side = (!side) ? (1000 - 6 - MAX(fl->w, fl->h) + 1) / MAX(fl->w, fl->h) :
			side;
	if (!start_x || !start_y)
	{
		start_x = 500 - (fl->w * side + fl->w - 1) / 2;
		start_y = 500 - (fl->h * side + fl->h - 1) / 2;
	}
	ps.x = start_x + pos.x * (side + 1);
	ps.y = start_y + pos.y * (side + 1);
	ft_draw_rect(fl, (t_point){side, side}, (t_point){ps.x, ps.y},
			g_colors[colors[pl]]);
}
