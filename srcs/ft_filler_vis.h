/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_vis.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:13:09 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 04:25:44 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILLER_VIS_H
# define FT_FILLER_VIS_H

# include "libft.h"
# define PTR (void*)(size_t)

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

typedef struct	s_filler
{
	t_mtx 		wait;
	char		*p1;
	char		*p2;
	char 		**map;
	char 		**fig;
	int 		turn;
	int			w;
	int			h;
	int			f_h;
	int 		f_w;
	int 		pos_y;
	int 		pos_x;
	t_status	st[2];
	void		*mlx_ptr;
	void		*win_ptr;
}				t_filler;

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
