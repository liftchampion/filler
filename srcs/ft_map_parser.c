/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 23:46:42 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 17:51:18 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_filler_vis.h"
#include <unistd.h>

int				ft_result_parser(t_filler *fl)
{
	char	*line;
	char	b[2];

	b[1] = 0;
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1) || !line)
		return (0);
	if (line[0] == '<' && (fl->pos_y = ft_atoi(line + 11)) >= 0 &&
			(fl->pos_x = ft_atoi(line + 11 + ft_intlen(fl->pos_y) + 2)) >= 0)
	{
		if (fl->turn == (line[6] == 'X') && !fl->st[line[6] != 'X'])
			fl->st[line[6] != 'X'] = END;
		fl->turn = (line[6] == 'X');
		if (!read(0, b, 2) || !b[1])
			return (ft_free_ret(line, 0));
		if (b[1] == 'i' && (fl->st[fl->turn] = WRG) &&
				(!ft_figure_parser(fl) || !ft_result_parser(fl)))
			return (ft_free_ret(line, 0));
		if (b[0] == '=')
			return (ft_parse_endgame(fl));
		return (ft_free_ret(line, 1));
	}
	return (ft_invalid_res(fl, line));
}

char			**ft_make_map(int h, int w)
{
	int		i;
	char	**mtr;

	if (!(mtr = (char**)ft_memalloc(sizeof(char*) * h)))
		return (0);
	i = -1;
	while (++i < h)
	{
		if (!(mtr[i] = (char *)ft_memalloc(sizeof(char) * (w + 1))))
		{
			while (i >= 0)
				free(mtr[i--]);
			return ((void*)(size_t)ft_free_ret(mtr, 0));
		}
		ft_memset(mtr[i], '.', (size_t)w);
	}
	return (mtr);
}

int				ft_map_parser(t_filler *fl)
{
	int			i;
	int			j;
	char		*l;
	char		*b;
	static int	was_begin = 0;

	if (!(l = (char*)1lu) || !ft_get_next_line(0, &l, 1) || !l ||
		!(b = ft_strstr(l, "ateau ")) ||
		!(fl->h = ft_atoi(b + 6))
		|| !(fl->w = ft_atoi(b + 6 + ft_intlen(fl->h))) || ft_free_ret(l, 0))
		return (ft_free_ret(l, 0));
	if ((i = -1) &&
		!(fl->map = ft_make_map(fl->h, fl->w)))
		return (0);
	while (++i < fl->h && (l = (char*)1lu) && ft_get_next_line(0, &l, 1) && l)
	{
		was_begin = (ft_strstr(l, "000") && !was_begin) ? 1 : was_begin;
		if ((j = 3) && !was_begin && ft_free_ret(l, 1) && (--i || 1))
			continue;
		while (l[++j])
			if (ft_strchr("oOxX", l[j]))
				fl->map[i][j - 4] = l[j];
		free(l);
	}
	return (!(was_begin = 0) && i == fl->h);
}

int				ft_figure_parser(t_filler *fl)
{
	char	*l;
	int		i;
	int		j;
	char	*b;

	if (!(l = (char*)1lu) || !ft_get_next_line(0, &l, 1) || !l
		|| !(b = ft_strstr(l, "ece "))
		|| !(fl->f_h = ft_atoi(b + 4))
		|| !(fl->f_w = ft_atoi(b + 4 + ft_intlen(fl->f_h)))
		|| ft_free_ret(l, 0))
		return (ft_free_ret(l, 0));
	if ((i = -1) &&
			!(fl->fig = ft_make_map(fl->f_h, fl->f_w)))
		return (0);
	while (++i < fl->f_h && (l = (char*)1lu) &&
									ft_get_next_line(0, &l, 1))
	{
		if (!(j = -1) || !l)
			return (0);
		while (l[++j])
			fl->fig[i][j] = l[j];
		free(l);
	}
	return (i == fl->f_h);
}
