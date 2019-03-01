/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:03:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/01 07:42:45 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLER_H
# define FT_FILLER_H
# define POINT(f, n) (*(t_point*)&((f)->points->data)[(n)])

# include "libft.h"

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_fig
{
	int h;
	int	w;
	t_vector *points;
}				t_fig;

typedef struct	s_filler
{
	char	player;
	int		map_h;
	int 	map_w;
	t_fig	*curr_fig;
	char 	**map;
}				t_filler;

void		ft_print_fig(t_fig *f);
size_t		ft_free_fig(t_fig **f, size_t ret);
t_fig		*ft_parse_fig(const char *str);

#endif
