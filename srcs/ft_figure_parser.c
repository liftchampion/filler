/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_figure_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:02:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 20:38:39 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

size_t		ft_free_fig(t_fig **f, size_t ret)
{
	if (!f || !*f)
		return (ret);
	ft_free_vector(&((*f)->points));
	ft_memdel((void**)f);
	return (ret);
}

int			ft_proceede_fig_line(char *line, t_fig *f)
{
	int len;

	len = 0;
	while (*line)
	{
		if (*line == '*')
			if (!ft_vector_push_back(&f->points,
					*(void**)&(t_point){len, f->h}))
			{
				free(line);
				return ((int)ft_free_fig(&f, 0));
			}
		++line;
		++len;
	}
	if (len > f->w)
		f->w = len;
	++f->h;
	return (1);
}

int			ft_figure_parser(const char *str, t_filler *fl)
{
	t_fig	*f;
	char	*line;
	int		i;

	if (!(f = ft_memalloc(sizeof(t_fig))) ||
		!(f->points = ft_make_vector(32)))
		return (0);
	str += 6;
	i = ft_atoi_m(&str) + 1;
	f->w = ft_atoi_m(&str);
	while (--i && (line = (char*)1lu) && ft_get_next_line(0, &line, 1))
	{
		if (!line)
			return ((int)ft_free_fig(&f, 0));
		if (!ft_proceede_fig_line(line, f))
			return (0);
		free(line);
	}
	fl->curr_fig = f;
	return (1);
}
