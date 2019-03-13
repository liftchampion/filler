/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_vis.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:13:09 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 11:59:35 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLER_VIS_H
# define FT_FILLER_VIS_H

# include "libft.h"
# define PTR (void*)(size_t)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

# define POINT(v, n) (*(t_point*)&((v)->data)[(n)])

# define VPUSH(v, n) ft_vector_push_back(&(v), (n))
# define HM flr->heat_map[pl]

extern int		g_colors[];

typedef enum	e_colors
{
	RED = 0,
	DARK_RED = 1,
	GREEN = 2,
	DARK_GREEN = 3,
	LIGHT_GRAY = 4,
	GRAY = 5,
	DARK_GRAY = 6,
	TEXT = 7
}				t_colors;

typedef enum	e_status
{
	OK = 0,
	ERR = 1,
	SEG = 2,
	WRG = 3,
	END = 4,
	OUT = 5,
}				t_status;

typedef enum 	e_mtx
{
	DRAW = 0,
	READ = 1,
}				t_mtx;

typedef enum	e_keys
{
	ESC = 53,
	LEFT = 123,
	UP = 126,
	RIGHT = 124,
	DOWN = 125
}				t_keys;

typedef struct	s_point
{
	int		x;
	int 	y;
}				t_point;

typedef struct	s_filler
{
	t_mtx 			wait;
	char			*p1;
	char			*p2;
	char 			**map;
	char 			**fig;
	int 			turn;
	int				w;
	int				h;
	int				f_h;
	int 			f_w;
	int 			pos_y;
	int 			pos_x;
	t_status		st[2];
	void			*mlx_ptr;
	void			*win_ptr;
	int 			sq_size;
	void			*img;
	char			*img_data;
	int 			**heat_map[2];
	t_vector		*pts[2];
	int 			score[2];
	int 			unrch[2];
}				t_filler;

void 	ft_kill_players(t_filler *fl);

void 	ft_draw_rect(t_filler *fl, t_point size, t_point pos, int color);
void	ft_draw_map(t_filler *fl);
void	ft_draw_base(t_filler *fl);
void	ft_draw_status(t_filler *fl);
void			ft_pix_put_img(t_filler *fl, int x, int y, int color);

void		ft_gather_data(t_filler *fl);
int			ft_make_heat_map(t_filler *fl);

void*			ft_main_read_loop(void* dt);

int 			ft_parse_cycle(t_filler *fl);

int				ft_wait(t_filler *fl, t_mtx mtx);

void			ft_print_filler(t_filler *fl);
int				ft_free_filler(t_filler *fl, int ret);
int				ft_free_ret(void *ptr, int ret);

char			*ft_get_name(const char *line);
t_filler		*ft_parse_begin(void);

int				ft_figure_parser(t_filler *fl);

int				ft_result_parser(t_filler *fl);

char**			ft_make_map(int h, int w);
int				ft_map_parser(t_filler *fl);
void			ft_print_map(t_filler *fl);
void			ft_print_fig(t_filler *fl);

#endif
