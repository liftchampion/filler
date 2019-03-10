/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_vis.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:13:09 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/10 03:59:00 by ggerardy         ###   ########.fr       */
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
}				t_status;

typedef struct	s_filler
{
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
}				t_filler;

int				ft_main_loop(void);

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
