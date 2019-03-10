/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 23:46:42 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/10 10:36:16 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_filler_vis.h"

char**		ft_make_map(int h, int w)
{
	int i;
	char **mtr;

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

void		ft_print_map(t_filler *fl)
{
	int i;
	int j;

	j = -1;
	ft_fdprintf(1, "{Yellow}map_w=%d map_h=%d{eof}\n   ", fl->w, fl->h);
	while (++j < fl->w)
	{
		ft_fdprintf(1, "{Magenta} %2d{eof}", j);
	}
	i = -1;
	ft_fdprintf(1, "\n");
	while (++i < fl->h)
	{
		j = -1;
		ft_fdprintf(1, "{Magenta}%3d{eof}", i);
		while (++j < fl->w)
		{
			ft_fdprintf(1, "{Magenta}  %c{eof}", fl->map[i][j]);
		}
		ft_fdprintf(1, "\n");
	}
}

void		ft_print_fig(t_filler *fl)
{
	int i;
	int j;

	j = -1;
	ft_fdprintf(1, "{Green}fig_w=%d fig_h=%d{eof}\n   ", fl->f_w, fl->f_h);
	while (++j < fl->f_w)
	{
		ft_fdprintf(1, "{Blue} %2d{eof}", j);
	}
	i = -1;
	ft_fdprintf(1, "\n");
	while (++i < fl->f_h)
	{
		j = -1;
		ft_fdprintf(1, "{Blue}%3d{eof}", i);
		while (++j < fl->f_w)
		{
			ft_fdprintf(1, "{Blue}  %c{eof}", fl->fig[i][j]);
		}
		ft_fdprintf(1, "\n");
	}
}

int			ft_map_parser(t_filler *fl)
{
	int		i;
	int		j;
	char	*l;
	char 	*b;
	int 	was_begin;

	ft_printf("{Red}MP{eof}\n");

	if (!(l = (char*)1lu) || !ft_get_next_line(0, &l, 1) || !l ||
		!(b = ft_strstr(l, "ateau ")) ||
		!(fl->h = ft_atoi(b + 6))
		|| !(fl->w = ft_atoi(b + 6 + ft_intlen(fl->h))) || ft_free_ret(l, 0))
		return (ft_free_ret(l, 0));
	if ((i = -1) && !(fl->map = ft_make_map(fl->h, fl->w)))
		return (0);
	was_begin = 0;
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
	ft_printf("{\\200}MP{eof}\n");
	///ft_print_filler(fl);
	return (i == fl->h);
}

int			ft_figure_parser(t_filler *fl)
{
	char	*l;
	int		i;
	int		j;
	char 	*b;

	if (!(l = (char*)1lu) || !ft_get_next_line(0, &l, 1) || !l
		|| !(b = ft_strstr(l, "ece "))
		|| !(fl->f_h = ft_atoi(b + 4))
		|| !(fl->f_w = ft_atoi(b + 4 + ft_intlen(fl->f_h)))
		|| ft_free_ret(l, 0))
		return (ft_free_ret(l, 0));
	if ((i = -1) && !(fl->fig = ft_make_map(fl->f_h, fl->f_w)))
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
	ft_printf("{\\200}FP{eof}\n");
	///ft_print_filler(fl);
	return (i == fl->f_h);
}