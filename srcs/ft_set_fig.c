/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 04:06:55 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 06:17:54 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

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
		val = fl->map[POINT(fig, i).y + pos.y][POINT(fig, i).x + pos.x];
		if ((overlaps += ft_tolower(val) == PLAYERS[(int)fl->player]) > 1)
			return (0);
		if (ft_tolower(val) == PLAYERS[!fl->player])
			return (0);
	}
	return (overlaps);
}

/*void		ft_put_fig(t_filler *fl, t_point pos)
{
	int		i;
	int		to_go;
	int		overlaps;
	t_fig	*fig;
	char 	val;

	i = -1;
	fig = fl->curr_fig;
	to_go = (int)fig->points->len;
	while (++i < to_go)
	{
		fl->map[POINT(fig, i).y + pos.y][POINT(fig, i).x + pos.x];
	}
}*/

int 		ft_set_fig(t_filler *fl)
{
	int i;
	int j;

	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			if (ft_check_fig(fl, (t_point){i, j}))
			{
				fl->last_pos = (t_point){i, j};
				return (1);
			}
		}
	}
	return (0);
}