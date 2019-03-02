/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:02:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 03:54:36 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // todo delete it
#include "libft.h"
#include "ft_filler.h"

#include <unistd.h>
#include <fcntl.h>

int 	ft_free_ret(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

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
			!ft_strstr(line + 11, "/ggerardy.filler]"))
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
	char *line;

	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1024) || !line)
		return (0);
	if (ft_strstr(line, "Plateau ") != line || (fl->h = ft_atoi(line + 8)) <= 0
			|| (fl->w = ft_atoi(line + 8 + ft_intlen(fl->h))) <= 0 ||
			!ft_map_parser(fl) || ft_free_ret(line, 0))
		return (ft_free_ret(line, 0));
	ft_print_map(fl);
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1024) || !line)
		return (0);
	ft_fdprintf(2, "{Red}Pic line is <%s>{eof}\n", line);
	if (ft_strstr(line, "Piece ") != line || !ft_figure_parser(line, fl) ||
												ft_free_ret(line, 0))
		return (ft_free_ret(line, 0));
	ft_print_fig(fl->curr_fig);
	return (1);
}

int 	ft_game_master(t_filler *filler)
{
	//char *line;

	ft_gamer(filler);



	return (1);
}

void ft_filler_free(t_filler *fl)
{
	int i;

	i = 0;
	if (!fl)
		return ;
	ft_free_fig(&fl->curr_fig, 0);
	if (fl->map)
		while (fl->h > 0)
			free(fl->map[--fl->h]);
	free(fl->map);
	free(fl);
}

int main()
{
	t_filler *fl;

	ft_fdprintf(2, "{Red}#######{eof}\n");

	if (!(fl = ft_start_gama()))
		return (0);

	ft_fdprintf(2, "{Red}filler=%p\n", fl);
	ft_fdprintf(2, "player=%d{eof}\n", fl->player);

	if (!ft_game_master(fl))
	{
		ft_filler_free(fl); // todo use filler-free
		return (0);
	}


	ft_filler_free(fl);
	return 0;
}