/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:03:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/15 05:21:55 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLER_H
# define FT_FILLER_H
# define POINT(v, n) (*(t_point*)&((v)->data)[(n)])
# define PLAYERS "ox"
# define WIN_LIMIT 1.1
# define SQ(a) ((a) * (a))
# define FIG_OPP_SUM metrics[0]
# define FIG_MY_SUM metrics[1]
# define OPP_SUM metrics[2]
# define MY_SUM metrics[3]
# define GATE_SUM metrics[4]
# define VPUSH(v, n) ft_vector_push_back(&(v), (n))
# define HM flr->heat_map[pl]

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
	int			player;
	int			h;
	int			w;
	t_fig		*curr_fig;
	char		**map;
	int			**heat_map[3];
	t_vector	*points[2];
	int			prev_opp_size;
	int			unrch_opp;
	t_point		last_pos;
	double		opp_sum_p;
	int			end_game;
	int 		closen_corners[2];
	double		crns_dst;
}				t_filler;

t_filler		*ft_start_gama(void);
int				ft_game_master(t_filler *filler);
int				ft_gamer(t_filler *fl);

int				ft_game_parser(t_filler *fl);
int				ft_figure_parser(const char *str, t_filler *fl);
int				ft_map_parser(t_filler *fl);
int				ft_make_map(t_filler *fl);

t_point			ft_sum_points(t_point p1, t_point p2);
int				ft_sum_opp_points(t_filler *fl, t_fig *fg, t_point pos, int pl);
int				ft_sum_gate_points(t_filler *fl, t_fig *fg, t_point pos);
double			ft_map_sum(register t_filler *fl, register int pl);

void			ft_zero_heat_map(register t_filler *fl, int clean_gates);
int				ft_update_heat_map(t_filler *fl);
int				ft_count_enemy_unr(register t_filler *fl);

void			ft_draw_circle_y(register t_filler *fl, int val, int r,
		t_point c);
void			ft_draw_circle_x(register t_filler *fl, int val, int r,
		t_point c);
int				ft_parse_gates(register t_filler *fl);

int				ft_check_fig(t_filler *fl, t_point pos);
int				ft_set_fig(t_filler *fl);
int				ft_set_fig_dummy(t_filler *fl);

int				ft_free_ret(void *ptr, int ret);
size_t			ft_free_fig(t_fig **f, size_t ret);
int				ft_filler_free(t_filler *fl, int ret);

#endif
