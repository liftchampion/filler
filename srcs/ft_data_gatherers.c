/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 07:03:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 15:17:52 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

#define SCALE 10000
#define DBL_EPS (DBL_EPSILON * SCALE)
#define UPD_VAL(v) ((v * SCALE) + (SCALE / 2.) * (1 - 2 * ((v) < 0)))

#define CRD(c) ((int)((c) / SCALE))

int 		ft_send_ray(t_filler *fl, t_point p1, t_point p2)
{
	double x;
	double y;
	double d;
	int invert;
	double to_go;

	x = UPD_VAL(p1.x);
	y = UPD_VAL(p1.y);
	ft_fdprintf(2, "ray start (%f %f) to (%f %f)\n", x, y, UPD_VAL(p2.x), UPD_VAL(p2.y));
	d = FT_ABS((UPD_VAL(p2.x) - UPD_VAL(p1.x)) ? (((UPD_VAL(p2.y) -
			UPD_VAL(p1.y))) / (UPD_VAL(p2.x) - UPD_VAL(p1.x))) : 1) *
					(1 - 2 * (p2.x < p1.x || p2.y < p1.y));
	invert = (FT_ABS(d) > 1) ? 1 : 0;
	if (invert && ((d = 1 / d) || 1))
		ft_swap(&x, &y, sizeof(x));
	to_go = invert ? UPD_VAL(p2.y) : UPD_VAL(p2.x);
	ft_fdprintf(2, "d = %f inv=%d to_go=%f\n", d, invert, to_go);
	while (FT_ABS(x - to_go) >= DBL_EPS)
	{
		//if ((CRD(x) != p1.x && CRD(y) != p1.y && !ft_strchr(".*", fl->map[CRD(y)][CRD(x)])) // todo only .
		//		|| CRD(x) < 0 || CRD(y) < 0 || CRD(x) >= fl->w || CRD(y) >= fl->h)
		//	return (0);
		fl->map[CRD(invert ? x : y)][CRD(invert ? y : x)] = '*'; // todo ruins map
		x += SCALE * (1 - 2 * (d < 0));
		y += SCALE * d;
		ft_fdprintf(2, "%f %f\n", invert ? y : x, invert ? x : y);
	}




	/*while (FT_ABS(UPD_VAL(p2.x) - x) >= DBL_EPS || FT_ABS(UPD_VAL(p2.y) - y) >= DBL_EPS)
	{

		y = (FT_ABS(k) != 1./0.) ? (k * x + b) : y;
		if ((CRD(x) != p1.x && CRD(y) != p1.y && !ft_strchr(".*", fl->map[CRD(y)][CRD(x)])) // todo only .
			|| CRD(x) < 0 || CRD(y) < 0 || CRD(x) >= fl->w || CRD(y) >= fl->h)
			return (0);
		fl->map[CRD(y)][CRD(x)] = '*'; // todo ruins map
		x += ((FT_ABS(k) != 1./0.) ? FT_ABS((double)(p2.x - p1.x) / (p2.y - p1.y)) : 0) * -1 *
				(p2.x < p1.x || p2.y < p1.y) * SCALE;
		y += ((FT_ABS(k) != 1./0.) ? 0 : SCALE) * -1 * (p2.y < p1.y);
		ft_print_map(fl);
		ft_fdprintf(2, "{Blue}%f %f{eof}\n", x, y);
		ft_fdprintf(2, "{Magenta}%f %f{eof}\n", UPD_VAL(p2.x), UPD_VAL(p2.y));
		ft_fdprintf(2, "{Green}%d %d{eof}\n", CRD(x), CRD(y));
		ft_fdprintf(2, "{Red}%f %f{eof}\n", FT_ABS(UPD_VAL(p2.x) - x) >= DBL_EPS, FT_ABS(UPD_VAL(p2.y) - y));
		//ft_fdprintf(2, "{\\200}%f %f{eof}\n", FT_ABS(UPD_VAL(p2.x) - x) >= DBL_EPS, FT_ABS(UPD_VAL(p2.y) - y));
	}
	fl->map[CRD(y)][CRD(x)] = 'F'; // todo ruins map
	ft_fdprintf(2, "{\\200}FINISHED!{eof}\n");*/
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




















