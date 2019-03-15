/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:57:01 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 00:55:37 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

t_filler		*ft_start_gama(void)
{
	t_filler	*fl;
	char		*line;

	line = (char*)1lu;
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1) || !line ||
			!(fl = (t_filler*)ft_memalloc(sizeof(t_filler))) ||
			!(fl->points[0] = ft_make_vector(64)) ||
			!(fl->points[1] = ft_make_vector(64)))
		return (0);
	if (!ft_strchr(line, 'p') &&
			(ft_free_ret(line, 0) || ft_filler_free(fl, 1)))
		return (0);
	fl->player = ft_atoi(line + (ft_strchr(line, 'p') - line) + 1);
	if ((fl->player != 1 && fl->player != 2) ||
			!ft_strstr(line, "ggerardy.filler") || (--fl->player && 0))
	{
		free(line);
		free(fl);
		return (0);
	}
	free(line);
	return (fl);
}

int				ft_gamer(t_filler *fl)
{
	if (!ft_game_parser(fl))
		return (0);
	if (((int)fl->points[1]->len == fl->prev_opp_size ||
	(double)fl->unrch_opp / (fl->h * fl->w) > WIN_LIMIT)
			? ft_set_fig_dummy(fl) : ft_set_fig(fl))
	{
		fl->prev_opp_size = (int)fl->points[1]->len;
		ft_printf("%d %d\n", fl->last_pos.x, fl->last_pos.y);
		return (1);
	}
	return (0);
}

int				ft_game_master(t_filler *filler)
{
	while (ft_gamer(filler))
		;
	return (1);
}
