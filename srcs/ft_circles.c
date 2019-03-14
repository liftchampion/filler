/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:27:18 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 20:27:18 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <math.h>

void 	ft_draw_circle_y(register t_filler *fl, int val, int r, t_point c)
{
	double y_fr;
	double y_to;
	int x1;

	y_fr = c.y - r / 2.;
	y_to = c.y + r / 2.;
	while (y_fr <= y_to)
	{
		x1 = (int)(sqrt(SQ(r) - SQ(y_fr - c.y)) + 0.);
		if ((int)(y_fr + 0.) >= 0 && (int)(y_fr + 0.) <= fl->h - 1)
		{
			if (x1 + c.x >= 0 && x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.)][x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.)][x1 + c.x] = val;
			}
			if (-x1 + c.x >= 0 && -x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.)][-x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.)][-x1 + c.x] = val;
			}
		}
		x1 = (int)(sqrt(SQ(r) - SQ(y_fr - c.y)) + 0.5);
		if ((int)(y_fr + 0.5) >= 0 && (int)(y_fr + 0.5) <= fl->h - 1)
		{
			if (x1 + c.x >= 0 && x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.5)][x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.5)][x1 + c.x] = val;
			}
			if (-x1 + c.x >= 0 && -x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.5)][-x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.5)][-x1 + c.x] = val;
			}
		}
		++y_fr;
	}
}

void 	ft_draw_circle_x(register t_filler *fl, int val, int r, t_point c)
{
	double x_fr;
	double x_to;
	int y1;

	ft_draw_circle_y(fl, val, r, c);
	x_fr = c.x - r / 2.;
	x_to = c.x + r / 2.;
	while (x_fr <= x_to)
	{
		y1 = (int)(sqrt(SQ(r) - SQ(x_fr - c.x)) + 0.);
		if ((int)(x_fr + 0.) >= 0 && (int)(x_fr + 0.) <= fl->w - 1)
		{
			if (y1 + c.y >= 0 && y1 + c.y <= fl->h - 1)
				if (fl->heat_map[1][y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][y1 + c.y][(int)(x_fr + 0.)] = val;
			if (-y1 + c.y >= 0 && -y1 + c.y <= fl->h - 1)
				if (fl->heat_map[1][-y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][-y1 + c.y][(int)(x_fr + 0.)] = val;
		}
		y1 = (int)(sqrt(SQ(r) - SQ(x_fr - c.x)) + 0.5);
		if ((int)(x_fr + 0.5) >= 0 && (int)(x_fr + 0.5) <= fl->w - 1)
		{
			if (y1 + c.y >= 0 && y1 + c.y <= fl->h - 1)
			{
				if (fl->heat_map[1][y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][y1 + c.y][(int)(x_fr + 0.5)] = val;
			}
			if (-y1 + c.y >= 0 && -y1 + c.y <= fl->h - 1)
			{
				if (fl->heat_map[1][-y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][-y1 + c.y][(int)(x_fr + 0.5)] = val;
			}
		}
		++x_fr;
	}
}
