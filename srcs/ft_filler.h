/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:03:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/11 08:03:46 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLER_H
# define FT_FILLER_H
# define POINT(v, n) (*(t_point*)&((v)->data)[(n)])
# define PLAYERS "ox"

# include "libft.h"

# define WIN_LIMIT 0.7


#define SCALE 10000
#define DBL_EPS (DBL_EPSILON * SCALE)
#define UPD_VAL(v) ((v * SCALE) + (SCALE / 2.) * (1 - 2 * ((v) < 0)))

#define CRD(c) ((int)((c) / SCALE))

#define SQ(a) ((a) * (a))

extern double kfc[];

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
	int 		w;
	t_fig		*curr_fig;
	char 		**map;
	int 		**heat_map[2];
	t_vector	*points[2];
	int 		prev_opp_size;
	int 		unrch_opp;
	char 		offset;   // todo no need
	t_point		last_pos;
	int 		ray_to_opp; // todo no need
}				t_filler;

typedef struct	s_weights
{
	double		max_dst_to_cnt;
	double		curr_dst_to_cnt;
	int 		my_rays_pr;
	int 		opp_rays_pr;
	int 		my_rays_new;
	int 		opp_rays_new;
	int 		my_p_pr;
	int 		opp_p_pr;
	int 		my_s_pr;
	int 		opp_s_pr;
	int 		my_p_new;
	int 		opp_p_new;
	int 		my_s_new;
	int 		opp_s_new;
	int 		my_dst_to_wall;
	int 		rays_to_enemy;
}				t_weights;

typedef struct	s_thr_rays_data
{
	t_filler *fl;
	t_point best_pos;
	double best_score;
	int start;
	int end;
}				t_thr_rays_data;

t_filler		*ft_start_gama(void);
int 			ft_game_master(t_filler *filler);
int 			ft_gamer(t_filler *fl);

int				ft_game_parser(t_filler *fl);
int				ft_figure_parser(const char *str, t_filler *fl);
int				ft_map_parser(t_filler *fl);
int				ft_make_map(t_filler *fl);

int 			ft_update_heat_map(t_filler *fl);
void			ft_print_heat_map(t_filler *fl, int pl);


int 			ft_check_fig(t_filler *fl, t_point pos);
int				ft_set_fig(t_filler *fl);
int 			ft_set_fig_dummy(t_filler *fl);
void			ft_get_surround_factor(t_filler *fl, int *me, int *opp);
int				ft_is_inner_figure(t_filler *fl, t_point pos);
void 			ft_get_perimeter(t_filler *fl, int pl, int *prim, int *sec);
int 			ft_get_distance_to_wall(t_filler *fl);
int 			ft_get_fig_distance_to_wall(t_filler *fl, t_point pos);
double			ft_get_distance_to_opp(t_filler *fl, t_point pos);
int 			ft_need_close_door(t_filler *fl, t_point pos);
double			ft_get_distance_to_center(t_weights *w, t_filler *fl, t_point pos);
int 			ft_send_ray(t_filler *fl, t_point p1, t_point p2, int check_inner);
void			*ft_send_rays_thread(void *vars);

void			ft_print_fig(t_fig *f);
void			ft_print_map(t_filler *fl);

int				ft_free_ret(void *ptr, int ret);
size_t			ft_free_fig(t_fig **f, size_t ret);
void			ft_filler_free(t_filler *fl);

#endif
