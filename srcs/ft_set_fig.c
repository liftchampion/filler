/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:06:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 20:40:56 by ggerardy         ###   ########.fr       */
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

double		ft_find_pos_score(t_filler *fl, int i, int j)
{
	double score;
	double metrics[5];

	if (!ft_put_fig_tmp(fl, (t_point){j, i}) || !ft_update_heat_map(fl))
		return (0);
	if ((double)fl->unrch_opp / (fl->h * fl->w) > 0.7 && fl->end_game != 2)
		fl->end_game = 1;
	OPP_SUM = ft_map_sum(fl, 1);
	FIG_OPP_SUM = (OPP_SUM == fl->opp_sum_p) ? BIG :
			ft_sum_opp_points(fl, fl->curr_fig, (t_point){j, i}, 1);
	FIG_MY_SUM = (OPP_SUM == fl->opp_sum_p) ? 0 :
			ft_sum_opp_points(fl, fl->curr_fig, (t_point){j, i}, 0);
	MY_SUM = (OPP_SUM == fl->opp_sum_p) ? BIG :
			ft_map_sum(fl, 0);
	GATE_SUM = (OPP_SUM == fl->opp_sum_p) ? 0 :
			ft_sum_gate_points(fl, fl->curr_fig, (t_point){j, i});
	OPP_SUM = 5 * SQ(OPP_SUM);
	MY_SUM = 1 * SQ(MY_SUM);
	GATE_SUM = 3 * SQ(GATE_SUM) * GATE_SUM;
	FIG_OPP_SUM = SQ(FIG_OPP_SUM) * SQ(FIG_OPP_SUM);
	FIG_MY_SUM = SQ(FIG_MY_SUM) * FIG_MY_SUM;
	score = (fl->end_game == 1) * BIG + OPP_SUM - MY_SUM + GATE_SUM -
			FIG_OPP_SUM + FIG_MY_SUM;
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
