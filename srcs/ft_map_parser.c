/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 08:52:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/01 11:05:32 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

void ft_print_map(t_filler *fl)
{
	int i;

	i = -1;
	while (++i < fl->h)
		ft_fdprintf(3, "%s\n", fl->map[i]);
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

	if (!fl->map && !ft_make_map(fl))
		return (0);
	i = 0;
	while (++i <= fl->h + 1 && (line = (char*)1lu) && ft_get_next_line(0, &line, 1024))
	{
		ft_fdprintf(3, "{Red}%s{eof}\n", line);
		if (i == 1)
		{
			free(line);
			continue;
		}
		if (!line)
			return (0);
		j = 3;
		while (line[++j])
			if (ft_strchr("oOxX", line[j]))
				fl->map[i - 2][j - 4] = line[j];
		free(line);
		ft_fdprintf(3, "{Green}%s{eof}\n", fl->map[i - 2]);
	}
	return (1);
}