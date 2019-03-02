/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 07:03:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 12:20:21 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

#define SCALE 10000
#define DBL_EPS (DBL_EPSILON * SCALE)

#define CRD(c) ((int)((c) / SCALE))

int 		ft_send_ray(t_filler *fl, t_point p1, t_point p2)
{
	double k;
	double b;
	double x;
	double y;

	k = ((double)(p2.y - p1.y)) / (p2.x - p1.x);
	b = (p1.y - k * p1.x) * SCALE;
	x = p1.x * SCALE + SCALE / 2;
	y = p1.y * SCALE + SCALE / 2;
	ft_fdprintf(2, "ray start %f %f\n", x, y);
	while (FT_ABS(p2.x * SCALE - x + SCALE / 2) >= DBL_EPS || FT_ABS(p2.y * SCALE - y + SCALE / 2) >= DBL_EPS)
	{
		ft_fdprintf(2, "{Blue}%f %f{eof}\n", x, y);
		ft_fdprintf(2, "{Green}%d %d{eof}\n", CRD(x), CRD(y));
		y = (FT_ABS(k) != 1./0.) ? (k * x + b) : y;
		if ((CRD(x) != p1.x && CRD(y) != p1.y && !ft_strchr(".*", fl->map[CRD(y)][CRD(x)])) // todo only .
			|| CRD(x) < 0 || CRD(y) < 0 || CRD(x) >= fl->w || CRD(y) >= fl->h)
			return (0);
		fl->map[CRD(y)][CRD(x)] = '*'; // todo ruins map
		x += ((FT_ABS(k) != 1./0.) ? FT_ABS((double)(p2.x - p1.x) / (p2.y - p1.y)) : 0) * -1 *
				(p2.x < p1.x || p2.y < p1.y);
		y += ((FT_ABS(k) != 1./0.) ? 0 : SCALE) * -1 * (p2.y < p1.y);
		ft_print_map(fl);
	}
	fl->map[CRD(y)][CRD(x)] = 'F'; // todo ruins map
	ft_fdprintf(2, "{\\200}FINISHED!{eof}\n");
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
			res += ft_send_ray(fl,
					*((t_point*)fl->points[player]->data[j]), (t_point){0, i});
	}
	return (res);
}




















