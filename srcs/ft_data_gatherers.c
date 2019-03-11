/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 07:03:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/09 17:10:45 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

#include <pthread.h>

#define PL fl->points[pl]

#define CHECK_FIRST(v) (CRD(v) != p1.v)

#include <stdio.h> // todo delete it

int			ft_check_point(t_point c, t_filler *fl, int inv, int check_inner) // todo inline ?
{
	if (!inv && fl->offset)
	{
		if (CRD(c.x) < 0 || CRD(c.y) < 0 || CRD(c.x) >= fl->w || CRD(c.y) >= fl->h)
			return (0);
		if (fl->map[CRD(c.y)][CRD(c.x)] != '.')
		{
			if (check_inner && ft_tolower(fl->map[CRD(c.y)][CRD(c.x)]) == PLAYERS[!fl->player])
				fl->ray_to_opp++;
			return (0);
		}
	}
	else if (fl->offset)
	{
		if (CRD(c.x) < 0 || CRD(c.y) < 0 || CRD(c.y) >= fl->w || CRD(c.x) >= fl->h)
			return (0);
		if (fl->map[CRD(c.x)][CRD(c.y)] != '.')
		{
			if (check_inner && ft_tolower(fl->map[CRD(c.x)][CRD(c.y)]) == PLAYERS[!fl->player])
				fl->ray_to_opp++;
			return (0);
		}
	}
	return (1);
}

int 		ft_send_ray(t_filler *fl, t_point p1, t_point p2, int check_inner)
{
	double x;
	double y;
	double d;
	int invert;
	double to_go;

	x = UPD_VAL(p1.x);
	y = UPD_VAL(p1.y);
	d = FT_ABS(((double)(p2.y - p1.y) / (p2.x - p1.x))) * (1 - 2 * (p2.x < p1.x || p2.y < p1.y));
	invert = (FT_ABS(d) > 1) ? 1 : 0;
	if (invert && ((d = 1 / d) || 1))
		ft_swap(&x, &y, sizeof(x));
	to_go = invert ? UPD_VAL(p2.y) : UPD_VAL(p2.x);
	fl->offset = 0;
	while (FT_ABS(x - to_go) >= DBL_EPS)
	{
		if (!ft_check_point((t_point){(int)x, (int)y}, fl, invert, check_inner))
			return (0);
		x += SCALE * (1 - 2 * (d < 0 || (d == 0 && ((!invert ? p2.x - p1.x : p2.y - p1.y) < 0))));
		y += SCALE * (1 - 2 * ((invert ? p2.x - p1.x : p2.y - p1.y) < 0)) * FT_ABS(d);
		fl->offset = 1;
	}
	return (1);
}

t_point			ft_sum_points(t_point p1, t_point p2)
{
	return ((t_point){p1.x + p2.x, p1.y + p2.y});
}

double			ft_get_distance_to_opp(t_filler *fl, t_point pos)
{
	double res;
	int i;
	int j;

	res = 0;
	i = -1;
	while (++i < (int)fl->points[1]->len)
	{
		j = -1;
		while (++j < (int)fl->curr_fig->points->len)
		{
			res += SQ(ft_sum_points(pos, POINT(fl->curr_fig->points, j)).x -
					POINT(fl->points[1], i).x) +
					SQ(ft_sum_points(pos, POINT(fl->curr_fig->points, j)).y -
							POINT(fl->points[1], i).y);
		}
	}
	return (res);
}

int			ft_is_inner_figure(t_filler *fl, t_point pos)
{
	int i;
	int j;

	fl->ray_to_opp = 0;
	i = fl->h + 1;
	while (--i >= -1 && (j = -1))
		while (++j < (int)fl->curr_fig->points->len)
		{
			ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
				(t_point){-1, i}, 1);
			ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
				(t_point){fl->w, i}, 1);
		}
	i = fl->w + 1;
	while (--i >= -1 && (j = -1))
		while (++j < (int)fl->curr_fig->points->len)
		{
			ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
				(t_point){-1, i}, 1);
			ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
				(t_point){i, fl->h}, 1);
		}
	return (fl->ray_to_opp == 0);
}

int 			ft_need_close_door(t_filler *fl, t_point pos)
{
	size_t i;
	t_point p;

	i = (size_t)-1;
	while (++i < fl->curr_fig->points->len)
	{
		p = ft_sum_points(POINT(fl->curr_fig->points, i), pos);
		if (!p.x || !p.y || p.x == fl->w - 1 || p.y == fl->h - 1)
			return (1);
	}
	return (0);
}

void			ft_get_surround_factor(t_filler *fl, int *me, int *opp)
{
	int i;
	int j;
	int k;

	i = fl->h + 1;
	*me = 0;
	*opp = 0;
	while (--i >= -1 && (j = -1) && (k = -1))
	{
		while (++j < (int)fl->points[0]->len)
			*me += ft_send_ray(fl, POINT(fl->points[0], j), (t_point){-1, i}, 0)
			+ ft_send_ray(fl, POINT(fl->points[0], j), (t_point){fl->w, i}, 0);
		while (++k < (int)fl->points[1]->len)
			*opp += ft_send_ray(fl, POINT(fl->points[1], k),(t_point){-1, i}, 0)
			+ ft_send_ray(fl, POINT(fl->points[1], k), (t_point){fl->w, i}, 0);
	}
	i = fl->w + 1;
	while (--i >= -1 && (j = -1) && (k = -1))
	{
		while (++j < (int)fl->points[0]->len)
			*me += ft_send_ray(fl, POINT(fl->points[0], j),(t_point){i, -1}, 0)
			+ ft_send_ray(fl, POINT(fl->points[0], j), (t_point){i, fl->h}, 0);
		while (++k < (int)fl->points[1]->len)
			*opp += ft_send_ray(fl, POINT(fl->points[1], k),(t_point){i, -1}, 0)
			+ ft_send_ray(fl, POINT(fl->points[1], k), (t_point){i, fl->h}, 0);
	}
}

void 		ft_get_perimeter(t_filler *fl, int pl, int *prim, int *sec)
{
	int i;

	i = -1;
	*prim = 0;
	*sec = 0;
	while (++i < (int)PL->len)
	{
		if (POINT(PL, i).x > 0)
			*prim += fl->map[POINT(PL, i).y][POINT(PL, i).x - 1] == '.';
		if (POINT(PL, i).x > 0 && POINT(PL, i).y > 0)
			*sec += fl->map[POINT(PL, i).y - 1][POINT(PL, i).x - 1] == '.';
		if (POINT(PL, i).x < fl->w - 1)
			*prim += fl->map[POINT(PL, i).y][POINT(PL, i).x + 1] == '.';
		if (POINT(PL, i).x < fl->w - 1 && POINT(PL, i).y > 0)
			*sec += fl->map[POINT(PL, i).y - 1][POINT(PL, i).x + 1] == '.';
		if (POINT(PL, i).y > 0)
			*prim += fl->map[POINT(PL, i).y - 1][POINT(PL, i).x] == '.';
		if (POINT(PL, i).y < fl->h - 1 && POINT(PL, i).x < fl->w - 1)
			*sec += fl->map[POINT(PL, i).y + 1][POINT(PL, i).x + 1] == '.';
		if (POINT(PL, i).y < fl->h - 1)
			*prim += fl->map[POINT(PL, i).y + 1][POINT(PL, i).x] == '.';
		if (POINT(PL, i).y < fl->h - 1 && POINT(PL, i).x > 0)
			*sec += fl->map[POINT(PL, i).y + 1][POINT(PL, i).x - 1] == '.';
	}
}

int 		ft_filler_min(int a, int b, int c, int d)
{
	int min1;
	int min2;

	min1 = (a <= b) ? a : b;
	min2 = (c <= d) ? c : d;
	return ((min1 <= min2) ? min1 : min2);
}

int 		ft_get_distance_to_wall(t_filler *fl)
{
	int res;
	int i;

	i = -1;
	res = 0;
	while (++i < (int)fl->points[0]->len)
	{
		res += ft_filler_min(POINT(fl->points[0], i).x,
				POINT(fl->points[0], i).y,
				fl->w - POINT(fl->points[0], i).x,
				fl->h - POINT(fl->points[0], i).y);
	}
	return (res);
}

int 		ft_get_fig_distance_to_wall(t_filler *fl, t_point pos)
{
	int res;
	int i;
	t_fig *fg;

	i = -1;
	res = 0;
	fg = fl->curr_fig;
	while (++i < (int)fg->points->len)
	{
		res += ft_filler_min(POINT(fg->points, i).x + pos.x,
				POINT(fg->points, i).y + pos.y,
				fl->w - POINT(fg->points, i).x - pos.x,
				fl->h - POINT(fg->points, i).y - pos.y);
	}
	return (res);
}















