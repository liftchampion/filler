/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:06:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 21:01:55 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

#define INIT_BEST_SCORE -2000000000

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
	if (pos.x + fig->w >= fl->w || pos.y + fig->h >= fl->h)
		return (0);
	while (++i < to_go)
	{
		val = fl->map[POINT(fig->points, i).y + pos.y]
				[POINT(fig->points, i).x + pos.x];
		if ((overlaps += ft_tolower(val) == PLAYERS[(int)fl->player]) > 1)
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
		if (!ft_vector_push_back(&fl->points[0], *(void**)&(t_point){p.x + pos.x, p.y + pos.y}))
			return (0);
	}
	return (1);
}

int 		ft_set_fig(t_filler *fl)
{
	int i;
	int j;
	int best_score;
	t_point best_pos;
	int score;

	t_weights w;
	ft_bzero(&w, sizeof(w));
	w.my_rays_b = ft_get_surround_factor(fl, 0);
	w.opp_rays_b = ft_get_surround_factor(fl, 1);

	i = -1;
	best_score = INIT_BEST_SCORE;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			if (ft_check_fig(fl, (t_point){i, j}))
			{
				if (!ft_put_fig_tmp(fl, (t_point){i, j}))
					return (0);
				//ft_print_map(fl);
				score = 1  * (ft_get_surround_factor(fl, 0) - w.my_rays_b) +
						1  * (w.opp_rays_b - ft_get_surround_factor(fl, 1)) +
						1  * ft_get_primary_perimiter(fl) +
						1  * ft_get_secondary_perimiter(fl) +
						-1 * ft_get_dictance_to_wall(fl);
				fl->points[0]->len -= fl->curr_fig->points->len;
				if (score > best_score)
				{
					best_score = score;
					best_pos = (t_point){i, j};
				}
				fl->last_pos = (t_point){i, j};
				//ft_fdprintf(2, "{\\200}%d\n", best_score);
			}
		}
	}
	return (best_score != INIT_BEST_SCORE ? 1 : 0);
}















