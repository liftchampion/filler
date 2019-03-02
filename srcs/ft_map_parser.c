/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 08:52:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 03:33:27 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

void ft_print_map(t_filler *fl)
{
	int i;

	i = -1;
	ft_fdprintf(2, "{Yellow}map_w=%d map_h=%d{eof}\n", fl->w, fl->h);
	while (++i < fl->h)
		ft_fdprintf(2, "%s\n", fl->map[i]);
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

	if (!fl->map && !ft_make_map(fl))
		return (0);
	i = -1;
	was_begin = 0;
	while (++i < fl->h && (line = (char*)1lu) && ft_get_next_line(0, &line, 1))
	{
		if (!line)
			return (0);
		was_begin = (ft_strstr(line, "000") && !was_begin) ? 1 : was_begin;
		if ((j = 3) && !was_begin && ft_free_ret(line, 1) && (--i || 1))
			continue;
		while (line[++j])
			if (ft_strchr("oOxX", line[j]))
				fl->map[i][j - 4] = line[j];
		ft_fdprintf(2, "{Blue}%s{eof}\n", line);
		free(line);
	}
	return (1);
}