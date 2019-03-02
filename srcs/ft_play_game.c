/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:57:01 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 06:26:19 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

t_filler *ft_start_gama(void)
{
	t_filler	*fl;
	char		*line;

	ft_fdprintf(2, "{Red}Game started{eof}\n");

	line = (char*)1lu;
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1024) || !line ||
			!(fl = (t_filler*)ft_memalloc(sizeof(t_filler))))
		return (0);
	ft_fdprintf(2, "{Red}Line got <%s>{eof}\n", line);
	if (ft_strstr(line, "$$$ exec p") != line)
	{
		free(line);
		free(fl);
		return (0);
	}
	fl->player = ft_atoi(line + 10);
	if ((fl->player != 1 && fl->player != 2) ||
			!ft_strstr(line + 11, "/ggerardy.filler]") || (--fl->player && 0))
	{
		free(line);
		free(fl);
		return (0);
	}
	ft_fdprintf(2, "{Red}Player is <%d>{eof}\n", fl->player);
	free(line);
	return (fl);
}

int 	ft_gamer(t_filler *fl)
{
	if (!ft_game_parser(fl))
		return (0);
	if (ft_set_fig(fl))
	{
		ft_fdprintf(2, "{\\200}%d %d{eof}\n", fl->last_pos.y, fl->last_pos.x);
		ft_printf("%d %d\n", fl->last_pos.y, fl->last_pos.x);
		return (1);
	}
	return (0);
}

int 	ft_game_master(t_filler *filler)
{
	while (ft_gamer(filler))
		;

	return (1);
}
