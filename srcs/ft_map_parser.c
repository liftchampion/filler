/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 08:52:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 06:11:54 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

void ft_print_map(t_filler *fl)
{
	int i;
	int j;

	j = -1;
	ft_fdprintf(2, "{Yellow}map_w=%d map_h=%d{eof}\n   ", fl->w, fl->h);
	while (++j < fl->w)
	{
		ft_fdprintf(2, "{Magenta} %2d{eof}", j);
	}
	i = -1;
	ft_fdprintf(2, "\n");
	while (++i < fl->h)
	{
		j = -1;
		ft_fdprintf(2, "{Magenta}%3d{eof}", i);
		while (++j < fl->w)
		{
			ft_fdprintf(2, "{Magenta}  %c{eof}", fl->map[i][j]);
		}
		ft_fdprintf(2, "\n");
	}
		//ft_fdprintf(2, "{Magenta}%s{eof}\n", fl->map[i]);
}

int ft_make_map(t_filler *fl)
{
	int i;
	char **mtr;

	if (!(mtr = (char**)ft_memalloc(sizeof(char*) * fl->h)))
		return (0);
	i = -1;
	while (++i < fl->h)
	{
		if (!(mtr[i] = (char *)ft_memalloc(sizeof(char) * (fl->w + 1))))
		{
			while (i >= 0)
				free(mtr[i--]);
			return (ft_free_ret(mtr, 0));
		}
		ft_memset(mtr[i], '.', (size_t)fl->w);
	}
	fl->map = mtr;
	return (1);
}

int		ft_map_parser(t_filler *fl)
{
	int		i;
	int		j;
	char	*line;
	int 	was_begin;

	if ((i = -1) && !fl->map && !ft_make_map(fl))
		return (0);
	was_begin = 0;
	while (++i < fl->h && (line = (char*)1lu) && ft_get_next_line(0, &line, 1))
	{
		if (!line)
			return (0);
		was_begin = (ft_strstr(line, "000") && !was_begin) ? 1 : was_begin;
		if ((j = 3) && !was_begin && ft_free_ret(line, 1) && (--i || 1))
			continue;
		/*while (line[++j])
			if (ft_strchr("oOxX", line[j]))
				fl->map[i][j - 4] = line[j];*/
		while (line[++j])
			if (ft_strchr("oOxX", line[j]) && (fl->map[i][j - 4] = line[j]))
				if (!ft_vector_push_back((!fl->not_first && ft_tolower(line[j])
					== PLAYERS[(int)fl->player]) ? &fl->my_points : 0 ,
						*(void**)&(t_point){i, j - 4}))
					return (ft_free_ret(line, 0));

		free(line);
	}
	return (1);
}

int		ft_game_parser(t_filler *fl)
{
	char *line;

	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1024) || !line)
		return (0);
	if (ft_strstr(line, "Plateau ") != line || (fl->h = ft_atoi(line + 8)) <= 0
			|| (fl->w = ft_atoi(line + 8 + ft_intlen(fl->h))) <= 0 ||
			!ft_map_parser(fl) || ft_free_ret(line, 0))
		return (ft_free_ret(line, 0));
	fl->not_first = 1;
	ft_print_map(fl); // todo print
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1024) || !line)
		return (0);
	if (ft_strstr(line, "Piece ") != line || !ft_figure_parser(line, fl) ||
			ft_free_ret(line, 0))
		return (ft_free_ret(line, 0));
	ft_print_fig(fl->curr_fig); // todo print
	return (1);
}