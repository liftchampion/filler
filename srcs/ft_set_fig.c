/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:06:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 06:17:33 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

#define BIG 1000000000000000000.

int			ft_check_fig(t_filler *fl, t_point pos)
{
	int		i;
	int		to_go;
	int		overlaps;
	t_fig	*fig;
	char	val;

	i = -1;
	fig = fl->curr_fig;
	to_go = (int)fig->points->len;
	overlaps = 0;
	if (pos.x + fig->w - 1 >= fl->w || pos.y + fig->h - 1 >= fl->h)
		return (0);
	while (++i < to_go)
	{
		val = fl->map[POINT(fig->points, i).y + pos.y]
				[POINT(fig->points, i).x + pos.x];
		if ((overlaps += ft_tolower(val) == PLAYERS[fl->player]) > 1)
			return (0);
		if (ft_tolower(val) == PLAYERS[!fl->player])
			return (0);
	}
	return (overlaps);
}

int			ft_put_fig_tmp(t_filler *fl, t_point pos)
{
	int		i;
	t_point	p;

	i = -1;
	while (++i < (int)fl->curr_fig->points->len)
	{
		p = POINT(fl->curr_fig->points, i);
		if (!ft_vector_push_back(&fl->points[0],
				*(void**)&(t_point){p.x + pos.x, p.y + pos.y}))
			return (0);
	}
	return (1);
}

int			ft_set_fig_dummy(t_filler *fl)
{
	int i;
	int j;

	i = -1;
	fl->last_pos = (t_point){666, 666};
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			if (ft_check_fig(fl, (t_point){j, i}))
			{
				fl->last_pos = (t_point){i, j};
				return (1);
			}
		}
	}
	return (1);
}

static inline int 	ft_min_4(int a, int b, int c, int d)
{
	if (a <= b && a <= c && a <= d)
		return (a);
	else if (b <= a && b <= c && b <= d)
		return (b);
	else if (c <= a && c <= b && c <= d)
		return (c);
	else
		return (d);
}

double		ft_get_distance_from_opp(t_filler *fl, double sum)
{
	if (sum < fl->curr_fig->points->len * (fl->h / 20.) || sum > fl->curr_fig->points->len * (fl->h / 10.))
	{
		return (sum + fl->h * fl->w * 2);
	}
	return (sum);
}

double		ft_get_distance_to_walls(register t_filler *fl, t_point pos)
{
	register size_t i;
	t_point pt;
	double res;

	res = 0;
	i = (size_t)-1;
	while (++i < fl->curr_fig->points->len)
	{
		pt = ft_sum_points(POINT(fl->curr_fig->points, i), pos);
		res += ft_min_4(pt.x, pt.y, fl->h - 1 - pt.y, fl->w - 1 -pt.x);
	}
	return (res);
}

int 		ft_check_close_corner(t_filler *fl, int type)
{
	int i;

	i = -1;
	while (++i < fl->h / 10)
	{
		if (type == 1)
			if (fl->heat_map[0][i][fl->w - 1] == -1)
				return (1);
		if (type == 2)
			if (fl->heat_map[0][fl->h - 1 - i][0] == -1)
				return (1);
	}
	i = -1;
	while (++i < fl->w / 10)
	{
		if (type == 1)
			if (fl->heat_map[0][0][fl->w - 1 - i] == -1)
				return (1);
		if (type == 2)
			if (fl->heat_map[0][fl->h - 1][i] == -1)
				return (1);
	}
	return (0);
}

int 		ft_find_dst_to_corner(t_filler *fl, int type)
{
	int i;
	int res = 2000000000;

	i = -1;
	while (++i < fl->h / 10)
	{
		if (type == 1)
			if (fl->heat_map[0][i][fl->w - 1] > 0 && fl->heat_map[0][i][fl->w - 1] < res)
				res = fl->heat_map[0][i][fl->w - 1];
		if (type == 2)
			if (fl->heat_map[0][fl->h - 1 - i][0] > 0 && fl->heat_map[0][fl->h - 1 - i][0] < res)
				res = fl->heat_map[0][fl->h - 1 - i][0];
	}
	i = -1;
	while (++i < fl->w / 10)
	{
		if (type == 1)
			if (fl->heat_map[0][0][fl->w - 1 - i] > 0 && fl->heat_map[0][0][fl->w - 1 - i] < res)
				res = fl->heat_map[0][0][fl->w - 1 - i];
		if (type == 2)
			if (fl->heat_map[0][fl->h - 1][i] > 0 && fl->heat_map[0][fl->h - 1][i] < res)
				res = fl->heat_map[0][fl->h - 1][i];
	}
	// todo check res = 2000000000
	return (res);
}

int 		ft_find_corner_to(t_filler *fl)
{
	if (fl->closen_corners[0])
		return (1);
	else if (fl->closen_corners[1])
		return (0);
	else
	{
		if (fl->heat_map[1][0][fl->w - 1] <= fl->heat_map[1][fl->h - 1][0])
			return (0);
		else
			return (1);
	}
}

double		ft_get_dst_to_corners(t_filler *fl)
{
	double res;

	res = -1 * ft_find_dst_to_corner(fl, ft_find_corner_to(fl) + 1) +
			1000 * ft_check_close_corner(fl, ft_find_corner_to(fl) + 1);

	//int cls_crns[2];

	/*cls_crns[0] = ft_check_close_corner(fl, 1);
	cls_crns[1] = ft_check_close_corner(fl, 2);

	res = ft_find_dst_to_corner(fl, 1) * (1 - 2 * !fl->closen_corners[0])
		+ ft_find_dst_to_corner(fl, 2) * (1 - 2 * !fl->closen_corners[1])
			+ 1000 * (cls_crns[0] == 1 && !fl->closen_corners[0])
			+ 1000 * (cls_crns[1] == 1 && !fl->closen_corners[1]);
	ft_fdprintf(2, "{\\202}%d - %d{eof}\n", ft_find_dst_to_corner(fl, 1) *
		(1 - 2 * !fl->closen_corners[0]) + 1000 *
		(cls_crns[0] == 1 && !fl->closen_corners[0]), fl->closen_corners[0]);
	ft_fdprintf(2, "{\\200}%d - %d{eof}\n", ft_find_dst_to_corner(fl, 2) *
			(1 - 2 * !fl->closen_corners[1]) + 1000 *
			(cls_crns[1] == 1 && !fl->closen_corners[1]), fl->closen_corners[1]);*/
	return (res);
}

double		ft_get_score_game_stage(t_filler *fl, const double metrics[5], t_point pt)
{
	double score;

	score = 0;
	score = ft_get_dst_to_corners(fl) /*- 100000000 *
			(FIG_OPP_SUM > (fl->h / 2. )* fl->curr_fig->points->len)*/;
	return (score);
	if ((1. * fl->points[0]->len) / (fl->w * fl->h) <= 0.007)
		score = - (fl->heat_map[0][0][fl->w - 1] + fl->heat_map[0][fl->h - 1][0]);
	else if ((1. * fl->points[0]->len) / (fl->w * fl->h) <= 0.02)
		score = - (fl->heat_map[0][0][fl->w - 1] + fl->heat_map[0][fl->h - 1][0]);
	return (score);
	if ((1. * fl->points[0]->len) / (fl->w * fl->h) <= 1)
		score = 0 * OPP_SUM - 1 * SQ(MY_SUM) + 0 * GATE_SUM -
				0 * ft_get_distance_from_opp(fl, FIG_OPP_SUM) + 1 * SQ(FIG_MY_SUM);
	else if ((1. * fl->points[0]->len) / (fl->w * fl->h) <= 0.03)
		score = 0.5 * SQ(OPP_SUM) - 2 * MY_SUM + 0 * GATE_SUM -
				1 * ft_get_distance_from_opp(fl, FIG_OPP_SUM) + 0 * FIG_MY_SUM -
				100 * ft_get_distance_to_walls(fl, pt);
	else if ((1. * fl->points[0]->len) / (fl->w * fl->h) <= 0.12)
		score = -ft_get_distance_to_walls(fl, pt);
	else if ((1. * fl->points[0]->len) / (fl->w * fl->h) <= 0.20)
		score = 2 * OPP_SUM - 2 * MY_SUM + 0 * GATE_SUM -
				1 * FIG_OPP_SUM + 1 * FIG_MY_SUM;

	return (score);
}

double		ft_find_pos_score(t_filler *fl, int i, int j)
{
	double score;
	double metrics[5];

	FIG_OPP_SUM = ft_sum_opp_points(fl, fl->curr_fig, (t_point){j, i}, 1);
	FIG_MY_SUM = ft_sum_opp_points(fl, fl->curr_fig, (t_point){j, i}, 0);
	if (!ft_put_fig_tmp(fl, (t_point){j, i}) || !ft_update_heat_map(fl))
		return (0);
	if ((double)fl->unrch_opp / (fl->h * fl->w) > 0.5 && fl->end_game != 2)
		fl->end_game = 1;
	OPP_SUM = ft_map_sum(fl, 1);
	MY_SUM = (OPP_SUM == fl->opp_sum_p) ? BIG :
			ft_map_sum(fl, 0);
	GATE_SUM = (OPP_SUM == fl->opp_sum_p) ? 0 :
			ft_sum_gate_points(fl, fl->curr_fig, (t_point){j, i});
	GATE_SUM = 0;
	/*OPP_SUM = 5 * SQ(OPP_SUM);
	MY_SUM = 1 * SQ(MY_SUM);
	GATE_SUM = 3 * SQ(0.3 * GATE_SUM) * SQ(0.3 * GATE_SUM);
	FIG_OPP_SUM = SQ(FIG_OPP_SUM) * SQ(FIG_OPP_SUM);
	FIG_MY_SUM = SQ(FIG_MY_SUM) * FIG_MY_SUM;*/
	score = ft_get_score_game_stage(fl, metrics, (t_point){j, i});
	/**score = (fl->end_game == 1) * SQ(BIG) + OPP_SUM - MY_SUM + GATE_SUM -
			FIG_OPP_SUM + FIG_MY_SUM;*/
	fl->points[0]->len -= fl->curr_fig->points->len;
	return (score);
}

int			ft_set_fig(register t_filler *fl)
{
	double			best_score;
	double			score;
	t_point			best_pos;
	register int	i;
	register int	j;

	i = -1;
	best_score = -1. / 0.;
	best_pos = (t_point){666, 666};
	fl->opp_sum_p = ft_map_sum(fl, 1);
	fl->closen_corners[0] = ft_check_close_corner(fl, 1);
	fl->closen_corners[1] = ft_check_close_corner(fl, 2);
	//fl->crns_dst = ft_get_dst_to_corners(fl);

	//ft_fdprintf(2, "{\\202}%d - %d{eof}\n", fl->closen_corners[0], fl->closen_corners[1]);

	ft_zero_heat_map(fl, 1);
	ft_parse_gates(fl);
	while (++i < fl->h && (j = -1))
		while (++j < fl->w)
			if (ft_check_fig(fl, (t_point){j, i}) &&
				((score = ft_find_pos_score(fl, i, j)) || 1))
				if (score > best_score)
				{
					best_score = score;
					best_pos = (t_point){i, j};
				}
	fl->end_game = (fl->end_game == 1) ? 2 : fl->end_game;
	fl->last_pos = best_pos;
	return (1);
}
