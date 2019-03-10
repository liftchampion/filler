/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 00:05:06 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/10 04:24:28 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"
#include <unistd.h>

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
	char 		*line;

	if (!(fl = (t_filler*)ft_memalloc(sizeof(t_filler))))
		return (0);
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

int				ft_invalid_res(t_filler *fl, char *ln)
{
	char b;

	b = 0;
	if (!ft_strstr(ln, "error"))
		return (1);
	fl->st[ln[12] == 'X'] = ERR;
	if (!read(0, &b, 1) || b != 'p')
		return (b == 'P');
	if (!ft_strstr(ln, "Segfault"))
		fl->st[ln[12] == 'X'] = SEG;
	free(ln);
	if (!(ln = (char*)1lu) || !ft_get_next_line(0, &ln, 1) || !ln ||
							ft_free_ret(ln, 0))
		return (0);
	return (1);
}

int				ft_result_parser(t_filler *fl)
{
	char	*line;
	int		curr_turn;

	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1) || !line)
		return (0);
	if (line[0] == '<')
	{
		curr_turn = (line[6] == 'X');
		if (curr_turn != fl->turn)
		{
			fl->st[fl->turn] = WRG;
			fl->turn = curr_turn;
		}
		else
			fl->turn = !fl->turn;
		fl->pos_y = ft_atoi(line + 11);
		fl->pos_x = ft_atoi(line + 11 + ft_intlen(fl->pos_y) + 2);
		ft_printf("{\\200}RP_V{eof}\n");
		ft_print_filler(fl);
		return (ft_free_ret(line, 1));
	}
	ft_printf("{\\200}RP_I{eof}\n");
	ft_print_filler(fl);
	return (ft_invalid_res(fl, line));
}












