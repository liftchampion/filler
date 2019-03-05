/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:06:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/05 21:20:26 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>


#define INIT_BEST_SCORE -2000000000

#define DELTA(a, b) ((double)((a) - (b)) / ((b) ? (b) : 1.))

int 		ft_check_fig(t_filler *fl, t_point pos)
{
	int		i;
	int		to_go;
	int		overlaps;
	t_fig	*fig;
	char 	val;

	//ft_fdprintf(2, "{Blue}To %d %d\n{eof}", pos.x, pos.y);
	i = -1;
	fig = fl->curr_fig;
	to_go = (int)fig->points->len;
	overlaps = 0;
	if (pos.x + fig->w - 1 >= fl->w || pos.y + fig->h - 1 >= fl->h)
	{
		//ft_fdprintf(2, "{Red}Early return %d  %d\n{eof}", pos.x + fig->w, pos.y + fig->h);
		return (0);
	}
	while (++i < to_go)
	{
		val = fl->map[POINT(fig->points, i).y + pos.y]
				[POINT(fig->points, i).x + pos.x];
		if ((overlaps += ft_tolower(val) == PLAYERS[fl->player]) > 1)
		{
			//ft_fdprintf(2, "{Red}Two overlaps\n{eof}");
			return (0);
		}
		if (ft_tolower(val) == PLAYERS[!fl->player])
		{
			//ft_fdprintf(2, "{Red}Other player\n{eof}");
			return (0);
		}
	}
	//ft_fdprintf(2, "{Green}%d\n{eof}", overlaps);
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
		if (!ft_vector_push_back(&fl->points[0], *(void**)&(t_point){p.x + pos.x, p.y + pos.y}))
			return (0);
		if (fl->map[p.y + pos.y][p.x + pos.x] == '.')
			fl->map[p.y + pos.y][p.x + pos.x] = (char)'#';
	}
	return (1);
}

int			ft_unput_fig_tmp(t_filler *fl, t_point pos)
{
	int i;
	t_point p;

	i = -1;
	fl->points[0]->len -= fl->curr_fig->points->len;
	while (++i < (int)fl->curr_fig->points->len)
	{
		p = POINT(fl->curr_fig->points, i);
		if (fl->map[p.y + pos.y][p.x + pos.x] == '#')
			fl->map[p.y + pos.y][p.x + pos.x] = (char)'.';
	}
	return (1);
}

int 		ft_set_fig(t_filler *fl)
{
	int i;
	int j;
	double best_score;
	t_point best_pos;
	double score;

	t_weights w;
	ft_bzero(&w, sizeof(w));
	ft_get_surround_factor(fl, &w.my_rays_pr, &w.opp_rays_pr);
	ft_get_perimiter(fl, 0, &w.my_p_pr, &w.my_s_pr);
	ft_get_perimiter(fl, 1, &w.opp_p_pr, &w.opp_s_pr);
	w.my_dst_to_wall = ft_get_dictance_to_wall(fl);

	i = -1;
	best_score = -1. / 0.;
	best_pos = (t_point){666, 666};
	///ft_fdprintf(2, "{\\200}best:%f##############################################{eof}\n", best_score);
	///ft_fdprintf(2, "{Green}opp_rays:%d{eof}\n", w.opp_rays);
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			if (ft_check_fig(fl, (t_point){j, i}))
			{
				if (!ft_put_fig_tmp(fl, (t_point){j, i}))
					return (0);
				///ft_print_map(fl);
				ft_get_surround_factor(fl, &w.my_rays_new, &w.opp_rays_new);
				ft_get_perimiter(fl, 0, &w.my_p_new, &w.my_s_new);
				ft_get_perimiter(fl, 1, &w.opp_p_new, &w.opp_s_new);
				score = kfc[0] * DELTA(w.my_rays_new, w.my_rays_pr) -
						kfc[1] * DELTA(w.opp_rays_new, w.opp_rays_pr) +
						kfc[2] * DELTA(w.my_p_new, w.my_p_pr) +
						kfc[3] * DELTA(w.my_s_new, w.my_s_pr) -
						kfc[4] * DELTA(w.opp_p_new, w.opp_p_pr) -
						kfc[5] * DELTA(w.opp_s_new, w.opp_s_pr) +
						kfc[6] * ((double)ft_get_fig_dictance_to_wall(fl, (t_point){j, i}) / w.my_dst_to_wall) +
						kfc[7] * (fl->player == 0) +
						kfc[8] * (fl->player == 1);
				ft_unput_fig_tmp(fl, (t_point){j, i});
				if (score > best_score)
				{
					best_score = score;
					best_pos = (t_point){i, j};
				}
				///ft_fdprintf(2, "{\\200}best:%f curr:%f{eof}\n", best_score, score);
			}
		}
	}
	fl->last_pos = (t_point){best_pos.x, best_pos.y};
	return (best_score != INIT_BEST_SCORE ? 1 : 0);
}















