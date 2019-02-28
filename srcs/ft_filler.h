/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:03:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/02/28 20:13:16 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLER_H
# define FT_FILLER_H

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

void		ft_print_fig(t_fig *f);
size_t		ft_free_fig(t_fig **f, size_t ret);
t_fig		*ft_parse_fig(void);

#endif
