/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 11:40:56 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"

void		ft_preprocess_data(register t_filler *fl)
{
	register int i;
	register int j;

	ft_bzero(fl->score, sizeof(int) * 2);
	ft_bzero(fl->unrch, sizeof(int) * 2);
	fl->pts[0]->len = 0;
	fl->pts[1]->len = 0;
	i = -1;
	while (++i < fl->h && (j = -1))
		while (++j < fl->w)
			if (fl->map[i][j] != '.')
			{
				if (fl->map[i][j] == 'x' || fl->map[i][j] == 'X')
				{
					fl->score[1]++;
					if (!VPUSH((fl->pts[1]), (*(void **)&(t_point){j, i})))
						exit(666);
				}
				if (fl->map[i][j] == 'o' || fl->map[i][j] == 'O')
				{
					fl->score[0]++;
					if (!VPUSH((fl->pts[0]), (*(void **)&(t_point){j, i})))
						exit(666);
				}
			}
}

void		ft_count_unrch(register t_filler *fl)
{
	register int i;
	register int j;

	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			fl->unrch[1] +=
					!fl->heat_map[1][i][j] || fl->heat_map[1][i][j] == -2;
			fl->unrch[0] +=
					!fl->heat_map[0][i][j] || fl->heat_map[0][i][j] == -2;
		}
	}
}

void		ft_gather_data(t_filler *fl)
{
	if (!fl->heat_map[0] || !fl->heat_map[1])
		ft_make_heat_map(fl);
	if ((!fl->pts[0] && !(fl->pts[0] = ft_make_vector(64))) ||
		(!fl->pts[1] && !(fl->pts[1] = ft_make_vector(64))))
		exit(666);
	ft_preprocess_data(fl);
	ft_update_heat_map(fl);
	ft_count_unrch(fl);
}
