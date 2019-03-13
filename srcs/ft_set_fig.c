/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:06:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 02:42:51 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

#include <pthread.h>
#include <printf.h>

#define BIG 1000000000000000000.

#define THREAD_COUNT 8



#define INIT_BEST_SCORE -2000000000

#define DELTA(a, b) ((double)((a) - (b)) / ((b) ? (b) : 1.))

int 		ft_check_fig(t_filler *fl, t_point pos)
{
	int		i;
	int		to_go;
	int		overlaps;
	t_fig	*fig;
	char 	val;

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
	int i;
	t_point p;

	i = -1;
	while (++i < (int)fl->curr_fig->points->len)
	{
		p = POINT(fl->curr_fig->points, i);
		if (!ft_vector_push_back(&fl->points[0],
				*(void**)&(t_point){p.x + pos.x, p.y + pos.y}))
			return (0);
		//if (fl->map[p.y + pos.y][p.x + pos.x] == '.')
		//	fl->map[p.y + pos.y][p.x + pos.x] = (char)'#';
	}
	return (1);
}

int			ft_unput_fig_tmp(t_filler *fl)
{
	/*int i;
	t_point p;

	i = -1;*/
	fl->points[0]->len -= fl->curr_fig->points->len;
	/*while (++i < (int)fl->curr_fig->points->len)
	{
		p = POINT(fl->curr_fig->points, i);
		if (fl->map[p.y + pos.y][p.x + pos.x] == '#')
			fl->map[p.y + pos.y][p.x + pos.x] = (char)'.';
	}*/
	return (1);
}



t_filler *ft_fl_copy(t_filler *fl)
{
	t_filler *res;
	int i;

	if (!(res = ft_memalloc(sizeof(*res))) || !(res->h = fl->h) || !(res->w = fl->w) ||
		!ft_make_map(res) || !(res->points[0] = ft_vector_cpy(fl->points[0])) ||
			!(res->points[1] = ft_vector_cpy(fl->points[1])) ||
			!(res->curr_fig = ft_memalloc(sizeof(t_fig))) ||
			!(res->curr_fig->points = ft_vector_cpy(fl->curr_fig->points)))
	{
		ft_filler_free(fl);
		return (0);
	}
	res->offset = fl->offset;
	res->player = fl->player;
	res->curr_fig->h = fl->curr_fig->h;
	res->curr_fig->w = fl->curr_fig->w;
	i = -1;
	while (++i < fl->h)
		ft_memcpy(res->map[i], fl->map[i], sizeof(char) * (fl->w + 1));
	return (res);
}

int 		ft_set_fig_dummy(t_filler *fl)
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

double 		ft_map_sum(register t_filler *fl, register int pl)
{
	static int		map_size = 0;
	register double	res;
	register int	i;
	register int	j;
	register int	curr_res;

	res = 0;
	i = -1;
	if (map_size == 0)
		map_size = fl->h + fl->w;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			curr_res = fl->heat_map[pl][i][j];
			if (curr_res > 0)
				res += curr_res;
			else if (!curr_res)
				res += map_size;
			else if (curr_res == -1 - pl)
				res += map_size;
		}
	}
	return (res);
}

int 		ft_sum_opp_points(t_filler *fl, t_fig *fg, t_point pos)
{
	size_t i;
	t_point pt;
	int res;

	res = 0;
	i = (size_t)-1;
	while (++i < fg->points->len)
	{
		pt = ft_sum_points(POINT(fg->points, i), pos);
		if (fl->heat_map[1][pt.y][pt.x] == 0)
			res += (fl->h + fl->w) * 2;
		else if (fl->heat_map[1][pt.y][pt.x] > 0)
			res += fl->heat_map[1][pt.y][pt.x];
	}
	return (res);
}

int 		ft_sum_gate_points(t_filler *fl, t_fig *fg, t_point pos)
{
	size_t i;
	t_point pt;
	int res;

	res = 0;
	i = (size_t)-1;
	while (++i < fg->points->len)
	{
		pt = ft_sum_points(POINT(fg->points, i), pos);
		res += fl->heat_map[2][pt.y][pt.x];
	}
	return (res);
}

int 		ft_set_fig(register t_filler *fl)
{
	static int end_game = 0;
	double best_score;
	double score;
	t_point best_pos;
	register int i;
	register int j;

	i = -1;
	best_score = -1. / 0.;
	best_pos = (t_point){666, 666};

	//int my_sum_p = ft_map_sum(fl, 0);
	double opp_sum_p = ft_map_sum(fl, 1);
	ft_zero_heat_map(fl, 1);
	ft_parse_gates(fl);
	//ft_print_heat_map(fl, 2);
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			if (ft_check_fig(fl, (t_point){j, i}))
			{
				if (!ft_put_fig_tmp(fl, (t_point){j, i}))
					return (0);
				if (!ft_update_heat_map(fl))
					return (0);
				if ((double)fl->unrch_opp / (fl->h * fl->w) > 0.7 && end_game != 2)
					end_game = 1;
				double fig_opp_sum = ft_sum_opp_points(fl, fl->curr_fig, (t_point){j, i});
				double opp_sum = ft_map_sum(fl, 1);
				double my_sum = (opp_sum == opp_sum_p) ? 1000000000 : ft_map_sum(fl, 0);
				double gate_sum = (opp_sum == opp_sum_p) ? 0 : ft_sum_gate_points(fl, fl->curr_fig, (t_point){j, i});

				//k1 = SQ(k1);
				//k2 = SQ(k2);

				opp_sum = 5 * SQ(opp_sum);
				my_sum = 1 * SQ(my_sum);
				gate_sum = 3 * SQ(gate_sum) * gate_sum;
				fig_opp_sum = fl->w * fl->h * SQ(fig_opp_sum);

				//score = k1 + k1;

				score = (end_game == 1) * BIG + opp_sum - my_sum + gate_sum - fig_opp_sum;
				ft_unput_fig_tmp(fl);
				if (score > best_score)
				{
					//ft_fdprintf(2, "{\\202}%f %f{eof}\n", k1, k2);
					//ft_fdprintf(2, "{\\202}%f %f %f %f %d{eof}\n", opp_sum, my_sum, gate_sum, fig_opp_sum, end_game);
					best_score = score;
					best_pos = (t_point){i, j};
				}
			}
			///ft_fdprintf(2, "{\\200}best:%f curr:%f{eof}\n", thd->best_score, score);
		}
	}
	if (end_game == 1)
		ft_fdprintf(2, "{\\202}GG!\n{eof}");
	ft_fdprintf(2, "{\\200}%f\n{eof}", (double)fl->unrch_opp / (fl->h * fl->w));
	end_game = (end_game == 1) ? 2 : end_game;
	fl->last_pos = best_pos;
	return (1);
}
















