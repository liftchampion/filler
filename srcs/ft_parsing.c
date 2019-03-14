/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 00:05:06 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 18:30:58 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"
#include <unistd.h>
#include <stdio.h>

char			*ft_get_name(const char *line)
{
	size_t begin;
	size_t end;

	end = (size_t)ft_strstr(line, ".filler]");
	if (end == 0)
		return (0);
	end -= (size_t)line;
	begin = (size_t)ft_rstrchr(line, '/');
	begin = (begin == 0) ? (size_t)ft_rstrchr(line, '[') : begin;
	++begin;
	if (begin == 0)
		return (0);
	begin -= (size_t)line;
	if (begin >= end)
		return (0);
	return (ft_strsub(line, (unsigned)begin, end - begin));
}

t_filler		*ft_parse_begin(void)
{
	t_filler	*fl;
	char		*line;

	if (!(fl = (t_filler*)ft_memalloc(sizeof(t_filler))))
		return (0);
	fl->turn = 1;
	while (!fl->p2 && (line = (char*)1lu) && ft_get_next_line(0, &line, 1))
	{
		if (!line)
			return (PTR(ft_free_filler(fl, 0)));
		if ((line[0] == '#' || line[0] == 'l') && ft_free_ret(line, 1))
			continue;
		if (fl->p1 && !(fl->p2 = ft_get_name(line)))
			return (PTR(ft_free_filler(fl, 0) + ft_free_ret(line, 0)));
		if (!fl->p1 && !(fl->p1 = ft_get_name(line)))
			return (PTR(ft_free_filler(fl, 0) + ft_free_ret(line, 0)));
	}
	return (fl);
}

int				ft_timeout(t_filler *fl, char *ln)
{
	char buf[2];

	fl->st[ln[12] == 'X'] = OUT;
	free(ln);
	if (read(0, &buf, 2) <= 0)
		return (0);
	return (ft_figure_parser(fl) && ft_result_parser(fl));
}

int				ft_parse_endgame(t_filler *fl)
{
	char *line;

	fl->unrch[0] = 0;
	if (!(line = (char *)1lu) || !ft_get_next_line(0, &line, 1) || !line)
		return (0);
	ft_printf("==%s\n", line);
	free(line);
	if (!(line = (char *)1lu) || !ft_get_next_line(0, &line, 1) || !line)
		return (0);
	ft_printf("%s\n", line);
	free(line);
	return (0);
}

int				ft_invalid_res(t_filler *fl, char *ln)
{
	char	b[2];
	int		pl;

	b[0] = 0;
	if (ft_strstr(ln, "timedout"))
		return (ft_timeout(fl, ln));
	if (!ft_strstr(ln, "error"))
		return (1);
	fl->st[ln[12] == 'X'] = ERR;
	pl = ln[12] == 'X';
	if (!read(0, &b, 2) || b[0] != 'p')
		return (b[0] == 'P' && ft_figure_parser(fl) && ft_result_parser(fl));
	free(ln);
	if (!(ln = (char*)1lu) || !ft_get_next_line(0, &ln, 1) || !ln)
		return (0);
	if (ft_strstr(ln, "Segfault"))
		fl->st[pl] = SEG;
	free(ln);
	if (!ft_figure_parser(fl) || !ft_result_parser(fl))
		return (0);
	return (1);
}
