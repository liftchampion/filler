/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:02:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/01 10:13:48 by ggerardy         ###   ########.fr       */
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

	line = (char*)1lu;
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1024) || !line ||
		!(fl = (t_filler*)ft_memalloc(sizeof(t_filler))))
		return (0);
	if (ft_strstr(line, "$$$ exec p") != line)
	{
		free(line);
		free(fl);
		return (0);
	}
	fl->player = ft_atoi(line + 10);
	if ((fl->player != 1 && fl->player != 2) ||
								ft_strcmp(line + 11, " : [./ggerardy.filler]"))
	{
		free(line);
		free(fl);
		return (0);
	}
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
			!ft_map_parser(fl))
		return (ft_free_ret(line, 0));
	ft_print_map(fl);
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1024) || !line)
		return (0);
	if (ft_strstr(line, "Piece ") != line || !ft_figure_parser(line, fl))
		return (0);
	ft_print_fig(fl->curr_fig);
	return (1);
}

int 	ft_game_master(t_filler *filler)
{
	char *line;

	ft_gamer(filler);



	return (1);
}

int main()
{
	t_filler *fl;
	int file = open("log", O_TRUNC | O_WRONLY);

	if (!(fl = ft_start_gama()))
		return (0);

	ft_fdprintf(3, "#######\n");
	ft_fdprintf(3, "filler=%p\n", fl);
	ft_fdprintf(3, "player=%d\n", fl->player);

	if (!ft_game_master(fl))
	{
		free(fl); // todo use filler-free
		return (0);
	}



	return 0;
}