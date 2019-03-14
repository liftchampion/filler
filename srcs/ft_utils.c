/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:59:08 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 21:42:38 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

int			ft_free_ret(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

int			ft_filler_free(t_filler *fl, int ret)
{
	int i;

	i = -1;
	if (!fl)
		return (ret);
	ft_free_fig(&fl->curr_fig, 0);
	if (fl->map)
		ft_free_matrix((void**)fl->map, (size_t)fl->h);
	while (++i < 3)
		if (fl->heat_map[i])
			ft_free_matrix((void **)fl->heat_map[i], (size_t)fl->h);
	ft_free_vector(&fl->points[0]);
	ft_free_vector(&fl->points[1]);
	free(fl);
	return (ret);
}

int			ft_count_enemy_unr(register t_filler *fl)
{
	register int res;
	register int i;
	register int j;

	res = 0;
	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			res += !fl->heat_map[1][i][j] || fl->heat_map[1][i][j] == -2;
		}
	}
	fl->unrch_opp = res;
	return (1);
}
