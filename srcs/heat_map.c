/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:21:45 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 22:16:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

int						ft_make_heat_map(t_filler *fl)
{
	int i;
	int **mtr[3];

	if (!(mtr[0] = (int **)ft_memalloc(sizeof(int *) * fl->h)) ||
			!(mtr[1] = (int **)ft_memalloc(sizeof(int *) * fl->h)) ||
			!(mtr[2] = (int **)ft_memalloc(sizeof(int *) * fl->h)))
		return (0);
	i = -1;
	while (++i < fl->h)
		if (!(mtr[0][i] = (int *)malloc(sizeof(int) * (fl->w))) ||
				!(mtr[1][i] = (int *)malloc(sizeof(int) * (fl->w))) ||
				!(mtr[2][i] = (int *)malloc(sizeof(int) * (fl->w))))
		{
			while (i >= 0)
			{
				free(mtr[0][i]);
				free(mtr[1][i]);
				free(mtr[2][i--]);
			}
			return (ft_free_ret(mtr[0], 0) + ft_free_ret(mtr[1], 0)
					+ ft_free_ret(mtr[2], 0));
		}
	ft_memcpy(fl->heat_map, mtr, sizeof(int**) * 3);
	return (1);
}

static inline int		ft_check_and_add_pt(t_point pt, t_filler *flr,
		int ds, int pl)
{
	if (pt.x > 0 && !HM[pt.y][pt.x - 1] &&
			(HM[pt.y][pt.x - 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y}));
	if (pt.y > 0 && !HM[pt.y - 1][pt.x] &&
			(HM[pt.y - 1][pt.x] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x, pt.y - 1}));
	if (pt.x < flr->w - 1 && !HM[pt.y][pt.x + 1] &&
			(HM[pt.y][pt.x + 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y}));
	if (pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x] &&
			(HM[pt.y + 1][pt.x] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x, pt.y + 1}));
	if (pt.x > 0 && pt.y > 0 && !HM[pt.y - 1][pt.x - 1] &&
			(HM[pt.y - 1][pt.x - 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y - 1}));
	if (pt.x > 0 && pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x - 1] &&
			(HM[pt.y + 1][pt.x - 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y + 1}));
	if (pt.x < flr->w - 1 && pt.y > 0 && !HM[pt.y - 1][pt.x + 1] &&
			(HM[pt.y - 1][pt.x + 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y - 1}));
	if (pt.x < flr->w - 1 && pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x + 1] &&
			(HM[pt.y + 1][pt.x + 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y + 1}));
	return (flr->points[pl] ? 1 : 0);
}

int						ft_fill_heat_map(register t_filler *fl, register int pl)
{
	register size_t	init_len;
	register int	begin;
	register int	i;
	size_t			new_begin;
	int				dst;

	begin = 0;
	dst = 1;
	init_len = fl->points[pl]->len;
	while (1)
	{
		i = (int)fl->points[pl]->len;
		new_begin = fl->points[pl]->len;
		while (--i >= begin)
			if (!ft_check_and_add_pt(POINT(fl->points[pl], i), fl, dst, pl))
				return (0);
		begin = (int)new_begin;
		if (new_begin == fl->points[pl]->len)
			break ;
		++dst;
	}
	fl->points[pl]->len = init_len;
	return (1);
}

void					ft_zero_heat_map(register t_filler *fl, int clean_gates)
{
	register int i;

	i = -1;
	while (++i < fl->h)
	{
		if (!clean_gates)
		{
			ft_bzero(fl->heat_map[0][i], sizeof(int) * fl->w);
			ft_bzero(fl->heat_map[1][i], sizeof(int) * fl->w);
		}
		else
			ft_bzero(fl->heat_map[2][i], sizeof(int) * fl->w);
	}
}

int						ft_update_heat_map(register t_filler *fl)
{
	register size_t	i;
	register size_t	to_go;
	int				pl;

	if ((!fl->heat_map[0] || !fl->heat_map[1]) && !ft_make_heat_map(fl))
		return (0);
	ft_zero_heat_map(fl, 0);
	pl = -1;
	while (++pl < 2)
	{
		i = (size_t)-1;
		to_go = fl->points[pl]->len;
		while (++i < to_go)
		{
			fl->heat_map[pl][POINT(fl->points[pl], i).y]
			[POINT(fl->points[pl], i).x] = -1;
			fl->heat_map[!pl][POINT(fl->points[pl], i).y]
			[POINT(fl->points[pl], i).x] = -2;
		}
	}
	if (!ft_fill_heat_map(fl, 0) || !ft_fill_heat_map(fl, 1))
		return (0);
	ft_parse_gates(fl);
	return (ft_count_enemy_unr(fl));
}
