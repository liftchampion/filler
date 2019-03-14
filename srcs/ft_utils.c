/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:59:08 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 20:31:42 by ggerardy         ###   ########.fr       */
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
	if (!fl)
		return (ret);
	ft_free_fig(&fl->curr_fig, 0);
	if (fl->map)
		while (fl->h > 0)
			free(fl->map[--fl->h]);
	free(fl->map);
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
