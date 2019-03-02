/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 07:03:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 09:31:27 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

int 		ft_send_ray(t_filler *fl, int player, t_point p1, t_point p2)
{
	double k;
	double b;
	double x;
	double y;

	k = ((double)(p2.y - p1.y)) / (p2.x - p1.x);
	b = p1.y - k * p1.x;
	x = p1.x;
	y = p2.y;
	while (FT_ABS(p2.x - x) < DBL_EPSILON || FT_ABS(p2.y - y) < DBL_EPSILON)
	{
		y = (FT_ABS(k) != 1./0.) ? (k * x + b) : y;
		if (FT_ABS(y - (int)y) < DBL_EPSILON)
			y = (int)y;
		else
			y = (int)(y + (p2.y < p1.y));
		if ((x != p1.x && fl->map[(int)y][(int)x] != '.') ||
			FT_ABS(x - 0) < DBL_EPSILON || FT_ABS(y - 0) < DBL_EPSILON ||
			FT_ABS(x - fl->w + 1) < DBL_EPSILON || FT_ABS(y - fl->h + 1) < DBL_EPSILON )
			return (0);
		x += (FT_ABS(k) != 1./0.) ? 1 : 0;
		y += (FT_ABS(k) != 1./0.) ? 0 : 1;
	}
	return (1);
}

int			ft_get_surround_factor(t_filler *fl, int player, t_point pos)
{
	int i;
	int j;
	int res;

	i = fl->h;
	res = 0;
	while (--i >= 0)
	{
		j = -1;
		while (++j < (int)fl->points[player]->len)
		{
			res += ft_send_ray(fl, player, *((t_point*)fl->points[player]->data[j]), (t_point){0, i});
		}
	}
}