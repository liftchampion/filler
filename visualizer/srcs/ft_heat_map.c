/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heat_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 18:18:17 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"

int						ft_make_heat_map(t_filler *fl)
{
	int i;
	int **mtr[2];

	if (!(mtr[0] = (int**)ft_memalloc(sizeof(int*) * fl->h)) ||
			!(mtr[1] = (int**)ft_memalloc(sizeof(int*) * fl->h)))
		return (0);
	i = -1;
	while (++i < fl->h)
	{
		if (!(mtr[0][i] = (int*)malloc(sizeof(int) * (fl->w))) ||
				!(mtr[1][i] = (int*)malloc(sizeof(int) * (fl->w))))
		{
			exit(666);
		}
	}
	fl->heat_map[0] = mtr[0];
	fl->heat_map[1] = mtr[1];
	return (1);
}

void					ft_zero_heat_map(register t_filler *fl)
{
	register int i;

	i = -1;
	while (++i < fl->h)
	{
		ft_bzero(fl->heat_map[0][i], sizeof(int) * fl->w);
		ft_bzero(fl->heat_map[1][i], sizeof(int) * fl->w);
	}
}

static inline int		ft_check_and_add_pt(t_point pt, t_filler *flr,
		int ds, int pl)
{
	if (pt.x > 0 && !HM[pt.y][pt.x - 1] &&
			(HM[pt.y][pt.x - 1] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x - 1, pt.y}));
	if (pt.y > 0 && !HM[pt.y - 1][pt.x] &&
			(HM[pt.y - 1][pt.x] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x, pt.y - 1}));
	if (pt.x < flr->w - 1 && !HM[pt.y][pt.x + 1] &&
			(HM[pt.y][pt.x + 1] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x + 1, pt.y}));
	if (pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x] &&
			(HM[pt.y + 1][pt.x] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x, pt.y + 1}));
	if (pt.x > 0 && pt.y > 0 && !HM[pt.y - 1][pt.x - 1] &&
			(HM[pt.y - 1][pt.x - 1] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x - 1, pt.y - 1}));
	if (pt.x > 0 && pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x - 1] &&
			(HM[pt.y + 1][pt.x - 1] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x - 1, pt.y + 1}));
	if (pt.x < flr->w - 1 && pt.y > 0 && !HM[pt.y - 1][pt.x + 1] &&
			(HM[pt.y - 1][pt.x + 1] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x + 1, pt.y - 1}));
	if (pt.x < flr->w - 1 && pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x + 1] &&
			(HM[pt.y + 1][pt.x + 1] = ds))
		VPUSH(flr->pts[pl], (*(void**)&(t_point){pt.x + 1, pt.y + 1}));
	return (flr->pts[pl] ? 1 : 0);
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
	init_len = fl->pts[pl]->len;
	while (1)
	{
		i = (int)fl->pts[pl]->len;
		new_begin = fl->pts[pl]->len;
		while (--i >= begin)
			if (!ft_check_and_add_pt(POINT(fl->pts[pl], i), fl, dst, pl))
				return (0);
		begin = (int)new_begin;
		if (new_begin == fl->pts[pl]->len)
			break ;
		++dst;
	}
	fl->pts[pl]->len = init_len;
	return (1);
}

void					ft_update_heat_map(register t_filler *fl)
{
	register size_t	i;
	register size_t	to_go;
	int				pl;

	if ((!fl->heat_map[0] || !fl->heat_map[1]) && !ft_make_heat_map(fl))
		exit(666);
	ft_zero_heat_map(fl);
	pl = -1;
	while (++pl < 2)
	{
		i = (size_t)-1;
		to_go = fl->pts[pl]->len;
		while (++i < to_go)
		{
			fl->heat_map[pl][POINT(fl->pts[pl], i).y]
			[POINT(fl->pts[pl], i).x] = -1;
			fl->heat_map[!pl][POINT(fl->pts[pl], i).y]
			[POINT(fl->pts[pl], i).x] = -2;
		}
	}
	if (!ft_fill_heat_map(fl, 0) || !ft_fill_heat_map(fl, 1))
		exit(666);
}
