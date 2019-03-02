/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:03:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 05:19:22 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLER_H
# define FT_FILLER_H
# define POINT(f, n) (*(t_point*)&((f)->points->data)[(n)])
# define PLAYERS "ox"

# include "libft.h"

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct	s_fig
{
	int			h;
	int			w;
	t_vector	*points;
}				t_fig;

typedef struct	s_filler
{
	char		player;
	int			h;
	int 		w;
	t_fig		*curr_fig;
	char 		**map;
	t_vector	*my_points;
	char 		not_first;
	t_point		last_pos;
}				t_filler;

t_filler		*ft_start_gama(void);
int 			ft_game_master(t_filler *filler);
int 			ft_gamer(t_filler *fl);

int				ft_game_parser(t_filler *fl);
int				ft_figure_parser(const char *str, t_filler *fl);
int				ft_map_parser(t_filler *fl);

int				ft_set_fig(t_filler *fl);

void			ft_print_fig(t_fig *f);
void			ft_print_map(t_filler *fl);

int				ft_free_ret(void *ptr, int ret);
size_t			ft_free_fig(t_fig **f, size_t ret);
void			ft_filler_free(t_filler *fl);

#endif
