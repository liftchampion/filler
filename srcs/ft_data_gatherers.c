/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 07:03:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/06 00:09:40 by ggerardy         ###   ########.fr       */
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

int			ft_check_point(t_point c, t_filler *fl, int inv, int check_inner) // todo inline ?
{
	if (!inv && fl->offset)
	{
		if (CRD(c.x) < 0 || CRD(c.y) < 0 || CRD(c.x) >= fl->w || CRD(c.y) >= fl->h ||
			(fl->map[CRD(c.y)][CRD(c.x)] != '.')) // todo . only
		{
			return (0);
		}
	}
	else if (fl->offset)
	{
		if (CRD(c.x) < 0 || CRD(c.y) < 0 || CRD(c.y) >= fl->w || CRD(c.x) >= fl->h ||
				(fl->map[CRD(c.x)][CRD(c.y)] != '.'))  // todo . only
		{
			//if (check_inner && fl->map[CRD(c.x)][CRD(c.y)] == PLAYERS[!fl->player]) // todo finish
			//	fl->
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

/*int			ft_get_surround_factor(t_filler *fl, int player)
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
}*/

t_point			ft_sum_points(t_point p1, t_point p2)
{
	return ((t_point){p1.x + p2.x, p1.y + p2.y});
}

void			ft_get_figure_inner_factor(t_filler *fl, t_point pos)
{
	int i;
	int j;

	i = fl->h + 1;
	while (--i >= -1 && (j = -1))
	{
		while (++j < (int)fl->curr_fig->points->len)
		{
			ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
				(t_point){-1, i}, 1) +
				ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
				(t_point){fl->w, i}, 1);
		}
	}
	i = fl->w + 1;
	while (--i >= -1 && (j = -1))
	{
		while (++j < (int)fl->curr_fig->points->len)
		{
			ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
				(t_point){-1, i}, 1) +
				ft_send_ray(fl, ft_sum_points(POINT(fl->curr_fig->points, j), pos),
					(t_point){i, fl->h}, 1);
		}
	}
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
			*me += ft_send_ray(fl, POINT(fl->points[0], j),(t_point){-1, i}, 0) +
					ft_send_ray(fl, POINT(fl->points[0], j),
							(t_point){fl->w, i}, 0);
		while (++k < (int)fl->points[1]->len)
			*opp += ft_send_ray(fl, POINT(fl->points[1], k),(t_point){-1, i}, 0) +
					ft_send_ray(fl, POINT(fl->points[1], k),
							(t_point){fl->w, i}, 0);
	}
	i = fl->w + 1;
	while (--i >= -1 && (j = -1) && (k = -1))
	{
		while (++j < (int)fl->points[0]->len)
			*me += ft_send_ray(fl, POINT(fl->points[0], j),(t_point){i, -1}, 0) +
					ft_send_ray(fl, POINT(fl->points[0], j),
							(t_point){i, fl->h}, 0);
		while (++k < (int)fl->points[1]->len)
			*opp += ft_send_ray(fl, POINT(fl->points[1], k),(t_point){i, -1}, 0) +
					ft_send_ray(fl, POINT(fl->points[1], k),
							(t_point){i, fl->h}, 0);
	}
}

void 		ft_get_perimiter(t_filler *fl, int pl, int *prim, int *sec)
{
	int i;

	i = -1;
	*prim = 0;
	*sec = 0;
	while (++i < (int)fl->points[pl]->len)
	{
		if (POINT(fl->points[pl], i).x > 0)
			*prim += fl->map[POINT(fl->points[pl], i).y][POINT(fl->points[pl], i).x - 1] == '.';
		if (POINT(fl->points[pl], i).x > 0 && POINT(fl->points[pl], i).y > 0)
			*sec += fl->map[POINT(fl->points[pl], i).y - 1][POINT(fl->points[pl], i).x - 1] == '.';
		if (POINT(fl->points[pl], i).x < fl->w - 1)
			*prim += fl->map[POINT(fl->points[pl], i).y][POINT(fl->points[pl], i).x + 1] == '.';
		if (POINT(fl->points[pl], i).x < fl->w - 1 && POINT(fl->points[pl], i).y > 0)
			*sec += fl->map[POINT(fl->points[pl], i).y - 1][POINT(fl->points[pl], i).x + 1] == '.';
		if (POINT(fl->points[pl], i).y > 0)
			*prim += fl->map[POINT(fl->points[pl], i).y - 1][POINT(fl->points[pl], i).x] == '.';
		if (POINT(fl->points[pl], i).y < fl->h - 1 && POINT(fl->points[pl], i).x < fl->w - 1)
			*sec += fl->map[POINT(fl->points[pl], i).y + 1][POINT(fl->points[pl], i).x + 1] == '.';
		if (POINT(fl->points[pl], i).y < fl->h - 1)
			*prim += fl->map[POINT(fl->points[pl], i).y + 1][POINT(fl->points[pl], i).x] == '.';
		if (POINT(fl->points[pl], i).y < fl->h - 1 && POINT(fl->points[pl], i).x > 0)
			*sec += fl->map[POINT(fl->points[pl], i).y + 1][POINT(fl->points[pl], i).x - 1] == '.';
	}
}


int 		ft_get_secondary_perimiter(t_filler *fl, int pl)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (++i < (int)fl->points[pl]->len)
	{
		if (POINT(fl->points[pl], i).x > 0 && POINT(fl->points[pl], i).y > 0)
		{
			res += fl->map[POINT(fl->points[pl], i).y - 1][POINT(fl->points[pl], i).x - 1] == '.';
		}
		if (POINT(fl->points[pl], i).x < fl->w - 1 && POINT(fl->points[pl], i).y > 0)
		{
			res += fl->map[POINT(fl->points[pl], i).y - 1][POINT(fl->points[pl], i).x + 1] == '.';
		}
		if (POINT(fl->points[pl], i).y < fl->h - 1 && POINT(fl->points[pl], i).x < fl->w - 1)
		{
			res += fl->map[POINT(fl->points[pl], i).y + 1][POINT(fl->points[pl], i).x + 1] == '.';
		}
		if (POINT(fl->points[pl], i).y < fl->h - 1 && POINT(fl->points[pl], i).x > 0)
		{
			res += fl->map[POINT(fl->points[pl], i).y + 1][POINT(fl->points[pl], i).x - 1] == '.';
		}
	}
	return (res);
}

int 		ft_filler_min(int a, int b, int c, int d)
{
	int min1;
	int min2;

	min1 = (a <= b) ? a : b;
	min2 = (c <= d) ? c : d;
	return ((min1 <= min2) ? min1 : min2);
}

int 		ft_get_dictance_to_wall(t_filler *fl) // todo use distance to opposite of enemy wall
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

int 		ft_get_fig_dictance_to_wall(t_filler *fl, t_point pos)
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















