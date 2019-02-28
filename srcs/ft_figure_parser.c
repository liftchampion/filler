/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_figure_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:02:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/02/28 22:02:10 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

#define POINT(f, n) (*(t_point*)&((f)->points->data)[(n)])

void		ft_print_fig(t_fig *f)
{
	char **mtr;
	int i;

	i = -1;
	ft_printf("w=%d  h=%d\n", f->w, f->h);
	if (!(mtr = (char**)ft_memalloc(sizeof(char*) * f->h)))
		return;
	while (++i < f->h)
	{
		if (!(mtr[i] = (char *)ft_memalloc(sizeof(char) * (f->w + 1))))
		{
			while (i >= 0)
			{
				free(mtr[i]);
				--i;
			}
			free(mtr);
			return;
		}
		ft_memset(mtr[i], '.', (size_t)f->w);
	}
	i = -1;
	while (++i < (int)f->points->len)
		mtr[POINT(f, i).y][POINT(f, i).x] = '*';
	i = -1;
	while (++i < f->h)
		ft_printf("%s\n", mtr[i]);
	while (f->h > 0)
		free(mtr[f->h-- - 1]);
	free(mtr);
}

size_t		ft_free_fig(t_fig **f, size_t ret)
{
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
			if (!ft_vector_push_back(&f->points, *(void**)&(t_point){len, f->h}))
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

t_fig		*ft_parse_fig(void)
{
	t_fig	*f;
	char	*line;

	if (!(f = ft_memalloc(sizeof(t_fig))) ||
		!(f->points = ft_make_vector(32)))
		return (0);
	while ((line = (char*)1lu) && ft_get_next_line(0, &line, 256))
	{
		if (!line)
			return ((t_fig*)ft_free_fig(&f, 0));
		if (!ft_proceede_fig_line(line, f))
			return (0);
		free(line);
	}
	return (f);
}