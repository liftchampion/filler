/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 02:20:26 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <math.h>

double		ft_map_sum(register t_filler *fl, register int pl)
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

int			ft_sum_opp_points(t_filler *fl, t_fig *fg, t_point pos, int pl)
{
	size_t	i;
	t_point	pt;
	int		res;

	res = 0;
	i = (size_t)-1;
	while (++i < fg->points->len)
	{
		pt = ft_sum_points(POINT(fg->points, i), pos);
		if (fl->heat_map[pl][pt.y][pt.x] == 0)
			res += lround((fl->h + fl->w) * 0.5);
		else if (fl->heat_map[pl][pt.y][pt.x] > 0)
			res += fl->heat_map[pl][pt.y][pt.x];
	}
	return (res);
}

int			ft_sum_gate_points(t_filler *fl, t_fig *fg, t_point pos)
{
	size_t	i;
	t_point	pt;
	int		res;

	res = 0;
	i = (size_t)-1;
	while (++i < fg->points->len)
	{
		pt = ft_sum_points(POINT(fg->points, i), pos);
		res += fl->heat_map[2][pt.y][pt.x];
	}
	return (res);
}
