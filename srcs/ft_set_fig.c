/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:06:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/07 09:14:57 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <float.h>

#include <pthread.h>
#include <printf.h>

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

void		*ft_set_fig_mt(void *tdt)
{
	int i;
	int j;
	t_thr_rays_data *thd;
	double score;

	thd = (t_thr_rays_data*)tdt;

	t_weights w;
	ft_bzero(&w, sizeof(w));
	ft_get_surround_factor(thd->fl, &w.my_rays_pr, &w.opp_rays_pr);
	ft_get_perimiter(thd->fl, 0, &w.my_p_pr, &w.my_s_pr);
	ft_get_perimiter(thd->fl, 1, &w.opp_p_pr, &w.opp_s_pr);
	w.my_dst_to_wall = ft_get_dictance_to_wall(thd->fl);

	i = thd->start - 1;
	thd->best_score = -1. / 0.;
	thd->best_pos = (t_point){666, 666};
	while (++i < thd->end)
	{
		j = -1;
		while (++j < thd->fl->w)
		{
			if (ft_check_fig(thd->fl, (t_point){j, i}))
			{
				if (ft_is_inner_figure(thd->fl, (t_point){j, i}))
				{
					///ft_fdprintf(2, "{\\200}INNER_FIG\n{eof}");
					score = -1000000 - ft_get_dictance_to_opp(thd->fl, (t_point){j, i});
				}
				else
				{
					///ft_fdprintf(2, "{\\202}NO_INNER_FIG 1337{eof}\n");
					if (!ft_put_fig_tmp(thd->fl, (t_point){j, i}))
						return (0);
					///ft_print_map(fl);
					ft_get_surround_factor(thd->fl, &w.my_rays_new,
							&w.opp_rays_new);
					ft_get_perimiter(thd->fl, 0, &w.my_p_new, &w.my_s_new);
					ft_get_perimiter(thd->fl, 1, &w.opp_p_new, &w.opp_s_new);

					score = kfc[0] * DELTA(w.my_rays_new, w.my_rays_pr) -
							kfc[1] * DELTA(w.opp_rays_new, w.opp_rays_pr) +
							kfc[2] * DELTA(w.my_p_new, w.my_p_pr) +
							kfc[3] * DELTA(w.my_s_new, w.my_s_pr) -
							kfc[4] * DELTA(w.opp_p_new, w.opp_p_pr) -
							kfc[5] * DELTA(w.opp_s_new, w.opp_s_pr) +
							kfc[6] * ((double)ft_get_fig_dictance_to_wall(
									thd->fl,
									(t_point){j, i}) / w.my_dst_to_wall) +
							kfc[7] * (thd->fl->player == 0) +
							kfc[8] * (thd->fl->player == 1);
					ft_unput_fig_tmp(thd->fl, (t_point){j, i});
				}
				if (score > thd->best_score)
				{
					thd->best_score = score;
					thd->best_pos = (t_point){i, j};
				}
				///ft_fdprintf(2, "{\\200}best:%f curr:%f{eof}\n", best_score, score);
			}
		}
	}
	return (0);
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

int 		ft_set_fig(t_filler *fl)
{
	t_filler *fls[THREAD_COUNT];
	pthread_t tid[THREAD_COUNT];
	t_thr_rays_data pdt[THREAD_COUNT];
	pthread_attr_t attr;
	double best_score;
	int i;

	int thread_size = fl->h / THREAD_COUNT;
	int last_thread = fl->h - thread_size * THREAD_COUNT;


	i = -1;
	while (++i < THREAD_COUNT)
		if (!(fls[i] = ft_fl_copy(fl)))
			return (0);
	i = -1;
	while (++i < THREAD_COUNT)
		pdt[i] = (t_thr_rays_data){fls[i], (t_point){666, 666}, -1. / 0,
				i * thread_size,
				i * thread_size + ((i == THREAD_COUNT - 1) ? last_thread : thread_size)};
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = -1;
	while (++i < THREAD_COUNT)
		pthread_create(&tid[i], &attr, ft_set_fig_mt, &pdt[i]);
	pthread_attr_destroy(&attr);
	i = -1;
	while (++i < THREAD_COUNT)
		pthread_join(tid[i], 0);
	i = -1;
	best_score = -1. / 0;
	fl->last_pos = (t_point){666, 666};
	while (++i < THREAD_COUNT)
	{
		//ft_fdprintf(2, "{Red}%d %d{eof}\n", pdt[i].best_pos.x, pdt[i].best_pos.y);
		if (pdt[i].best_score > best_score)
		{
			fl->last_pos = pdt[i].best_pos;
			best_score = pdt[i].best_score;
		}
	}
	//ft_fdprintf(2, "{\\200}%d %d{eof}\n", fl->last_pos.x, fl->last_pos.y);
	return (1);
}
















