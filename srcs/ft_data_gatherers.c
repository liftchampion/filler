/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 07:03:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 21:02:36 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

#define SCALE 10000
#define DBL_EPS (DBL_EPSILON * SCALE)
#define UPD_VAL(v) ((v * SCALE) + (SCALE / 2.) * (1 - 2 * ((v) < 0)))

#define CRD(c) ((int)((c) / SCALE))

#define CHECK_FIRST(v) (CRD(v) != p1.v)

#include <stdio.h> // todo delete it

int			ft_check_point(t_point c, t_filler *fl, int inv) // todo inline ?
{
	if (!inv && fl->offset)
	{
		if (CRD(c.x) < 0 || CRD(c.y) < 0 || CRD(c.x) >= fl->w || CRD(c.y) >= fl->h ||
			(!ft_strchr(".*", fl->map[CRD(c.y)][CRD(c.x)]))) // todo . only
			return (0);
	}
	else if (fl->offset)
	{
		if (CRD(c.x) < 0 || CRD(c.y) < 0 || CRD(c.y) >= fl->w || CRD(c.x) >= fl->h ||
				(!ft_strchr(".*", fl->map[CRD(c.x)][CRD(c.y)])))  // todo . only
			return (0);
	}
	return (1);
}

int 		ft_send_ray(t_filler *fl, t_point p1, t_point p2)
{
	double x;
	double y;
	double d;
	int invert;
	double to_go;

	x = UPD_VAL(p1.x);
	y = UPD_VAL(p1.y);
	///ft_fdprintf(2, "{Red}%d %d{eof}\n", p2.x, p2.y);
	///ft_fdprintf(2, "ray start (%f %f) to (%f %f)\n", x, y, UPD_VAL(p2.x), UPD_VAL(p2.y));
	/*d = FT_ABS((((UPD_VAL(p2.y) -
			UPD_VAL(p1.y))) / (UPD_VAL(p2.x) - UPD_VAL(p1.x)))) *
					(1 - 2 * (p2.x < p1.x || p2.y < p1.y));*/
	d = FT_ABS(((double)(p2.y - p1.y) / (p2.x - p1.x))) * (1 - 2 * (p2.x < p1.x || p2.y < p1.y));
	///printf("<%f>\n", d);
	invert = (FT_ABS(d) > 1) ? 1 : 0;
	if (invert && ((d = 1 / d) || 1))
		ft_swap(&x, &y, sizeof(x));
	////printf("<%f>[%d][%f]\n", d, SCALE * (1 - 2 * (d < 0)), SCALE * d);
	to_go = invert ? UPD_VAL(p2.y) : UPD_VAL(p2.x);
	///ft_fdprintf(2, "d = %f inv=%d to_go=%f {Cyan}%d{eof}\n", d, invert, to_go, 0. == -0.);
	fl->offset = 0;
	while (FT_ABS(x - to_go) >= DBL_EPS)
	{
		if (!ft_check_point((t_point){(int)x, (int)y}, fl, invert))
			return (0);
		///fl->map[CRD(invert ? x : y)][CRD(invert ? y : x)] = '*'; // todo ruins map
		x += SCALE * (1 - 2 * (d < 0 || (d == 0 && ((!invert ? p2.x - p1.x : p2.y - p1.y) < 0))));
		y += SCALE * (1 - 2 * ((invert ? p2.x - p1.x : p2.y - p1.y) < 0)) * FT_ABS(d);
		fl->offset = 1;
		///ft_fdprintf(2, "%f %f\n", invert ? y : x, invert ? x : y);
		///ft_fdprintf(2, "{Red}%d %d{eof}\n", CRD(invert ? y : x), CRD(invert ? x : y));
	}
	///ft_fdprintf(2, "{Blue}%d %d{eof}\n", p2.x, p2.y);
	return (1);
}

int			ft_get_surround_factor(t_filler *fl, int player)
{
	int i;
	int j;
	int res;

	res = 0;
	i = fl->h + 1;
	while (--i >= -1 && (j = -1))
		while (++j < (int)fl->points[player]->len)
			res += ft_send_ray(fl, POINT(fl->points[player],j), (t_point){-1, i}) +
					ft_send_ray(fl, POINT(fl->points[player],j), (t_point){fl->w, i});
	i = fl->w + 1;
	while (--i >= -1 && (j = -1))
		while (++j < (int)fl->points[player]->len)
			res += ft_send_ray(fl, POINT(fl->points[player],j), (t_point){i, -1}) +
					ft_send_ray(fl, POINT(fl->points[player],j), (t_point){i, fl->h});
	return (res);
}

int 		ft_get_primary_perimiter(t_filler *fl)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (++i < (int)fl->points[0]->len)
	{
		if (POINT(fl->points[0], i).x > 0)
		{
			res += fl->map[POINT(fl->points[0], i).y][POINT(fl->points[0], i).x - 1] == '.';
		}
		if (POINT(fl->points[0], i).x < fl->w - 1)
		{
			res += fl->map[POINT(fl->points[0], i).y][POINT(fl->points[0], i).x + 1] == '.';
		}
		if (POINT(fl->points[0], i).y > 0)
		{
			res += fl->map[POINT(fl->points[0], i).y - 1][POINT(fl->points[0], i).x] == '.';
		}
		if (POINT(fl->points[0], i).y < fl->h - 1)
		{
			res += fl->map[POINT(fl->points[0], i).y + 1][POINT(fl->points[0], i).x] == '.';
		}
	}
	return (res);
}


int 		ft_get_secondary_perimiter(t_filler *fl)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (++i < (int)fl->points[0]->len)
	{
		if (POINT(fl->points[0], i).x > 0 && POINT(fl->points[0], i).y > 0)
		{
			res += fl->map[POINT(fl->points[0], i).y - 1][POINT(fl->points[0], i).x - 1] == '.';
		}
		if (POINT(fl->points[0], i).x < fl->w - 1 && POINT(fl->points[0], i).y > 0)
		{
			res += fl->map[POINT(fl->points[0], i).y - 1][POINT(fl->points[0], i).x + 1] == '.';
		}
		if (POINT(fl->points[0], i).y < fl->h - 1 && POINT(fl->points[0], i).x < fl->w - 1)
		{
			res += fl->map[POINT(fl->points[0], i).y + 1][POINT(fl->points[0], i).x + 1] == '.';
		}
		if (POINT(fl->points[0], i).y < fl->h - 1 && POINT(fl->points[0], i).x > 0)
		{
			res += fl->map[POINT(fl->points[0], i).y + 1][POINT(fl->points[0], i).x - 1] == '.';
		}
	}
	return (res);
}

int 		ft_get_dictance_to_wall(t_filler *fl) // todo use distance to opposite of enemy wall
{
	int res;
	int i;

	i = -1;
	res = 0;
	while (++i < (int)fl->points[0]->len)
	{
		res += fl->w - 1 - POINT(fl->points[0], i).x;
		if (fl->points[0]->len <= 50)
			res += fl->h - 1 - POINT(fl->points[0], i).y;
	}
	return (res);
}















