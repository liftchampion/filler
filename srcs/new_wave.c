/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 02:20:26 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/11 06:23:46 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"


/*static inline int		ft_check_and_add_pt_f(t_point pt, t_fig *f, int ds, int pl)
{
	if (pt.x > 0 && !HM[pt.y][pt.x - 1] &&
			(HM[pt.y][pt.x - 1] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y}));
	if (pt.y > 0 && !HM[pt.y - 1][pt.x] &&
			(HM[pt.y - 1][pt.x] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x, pt.y - 1}));
	if (pt.x < f->w - 1 && !HM[pt.y][pt.x + 1] &&
			(HM[pt.y][pt.x + 1] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y}));
	if (pt.y < f->h - 1 && !HM[pt.y + 1][pt.x] &&
			(HM[pt.y + 1][pt.x] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x, pt.y + 1}));
	if (pt.x > 0 && pt.y > 0 && !HM[pt.y - 1][pt.x - 1] &&
			(HM[pt.y - 1][pt.x - 1] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y - 1}));
	if (pt.x > 0 && pt.y < f->h - 1 && !HM[pt.y + 1][pt.x - 1] &&
			(HM[pt.y + 1][pt.x - 1] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y + 1}));
	if (pt.x < f->w - 1 && pt.y > 0 && !HM[pt.y - 1][pt.x + 1] &&
			(HM[pt.y - 1][pt.x + 1] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y - 1}));
	if (pt.x < f->w - 1 && pt.y < f->h - 1 && !HM[pt.y + 1][pt.x + 1] &&
			(HM[pt.y + 1][pt.x + 1] = ds))
		VPUSH(f->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y + 1}));
	return (f->points[pl] ? 1 : 0);
}*/


/*int 		ft_set_fig_dummy(t_filler *fl)
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
}*/

/*int 		ft_find_fig_delta(t_filler *fl)
{



}*/

/*int 		ft_set_fig_new(t_filler *fl)
{

	return (1);
}*/