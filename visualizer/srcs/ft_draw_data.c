/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 05:46:25 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 16:35:46 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "ft_filler_vis.h"
#include <math.h>

#define DLT(n) (double)(fl->h * fl->w - fl->unrch[(n)])

#define AVL(n) (int)lround((((1. - (DLT(n) / (fl->h * fl->w)))) * 100))

int		g_colors[] =
{
	0x009C3437,
	0x00FF6666,
	0x0021806A,
	0x0000EFB7,
	0x00292929,
	0x002e2e2e,
	0x00272727,
	0x00909090,
	0x00442526,
	0x00263934
};

char	g_statuses[6][9] =
{
	"OK\0\0\0\0\0\0",
	"Fallen\0\0",
	"Segfault",
	"Wrong\0\0\0",
	"Left\0\0\0\0",
	"Timeout\0"
};

void		ft_draw_map(t_filler *fl)
{
	int i;
	int j;

	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			if (fl->map[i][j] == 'O' || fl->map[i][j] == 'o')
				ft_draw_sq(fl, (t_point){j, i}, (fl->map[i][j] == 'o') + 0);
			else if (fl->map[i][j] == 'X' || fl->map[i][j] == 'x')
				ft_draw_sq(fl, (t_point){j, i}, (fl->map[i][j] == 'x') + 2);
			else if (fl->heat_map[1][i][j] == 0)
				ft_draw_sq(fl, (t_point){j, i}, 5);
			else if (fl->heat_map[0][i][j] == 0)
				ft_draw_sq(fl, (t_point){j, i}, 6);
			else
				ft_draw_sq(fl, (t_point){j, i}, 4);
		}
	}
	mlx_put_image_to_window(fl->mlx_ptr, fl->win_ptr, fl->img, 0, 0);
}

void		ft_draw_line(t_filler *fl, t_point pos, int len, int color)
{
	int i;

	i = pos.x;
	while (i <= pos.x + len)
	{
		mlx_pixel_put(fl->mlx_ptr, fl->win_ptr, i, pos.y, color);
		mlx_pixel_put(fl->mlx_ptr, fl->win_ptr, i, pos.y + 1, color);
		++i;
	}
}

void		ft_draw_status(t_filler *fl)
{
	mlx_string_put(fl->mlx_ptr, fl->win_ptr, 1000 + 30, 190,
			g_colors[TEXT], "Status:");
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
			1300 - 15 - ((int)ft_strlen(fl->p1) * 10) / 2 -
			(int)ft_strlen(g_statuses[fl->st[0]]) * 10,
			190, g_colors[RED], g_statuses[fl->st[0]]);
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
			1300 + 45 + ((int)ft_strlen(fl->p2) * 10) / 2 -
			(int)ft_strlen(g_statuses[fl->st[1]]) * 10,
			190, g_colors[GREEN], g_statuses[fl->st[1]]);
}

void		ft_draw_info(t_filler *fl)
{
	char buf[20];

	mlx_string_put(fl->mlx_ptr, fl->win_ptr, 1000 + 30, 130,
			g_colors[TEXT], "Score:");
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
1300 - 15 - ((int)ft_strlen(fl->p1) * 10) / 2 - ft_intlen(fl->score[0]) * 10,
			130, g_colors[RED], ft_itoa_buf(fl->score[0], buf));
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
1300 + 45 + ((int)ft_strlen(fl->p2) * 10) / 2 - ft_intlen(fl->score[1]) * 10,
			130, g_colors[GREEN], ft_itoa_buf(fl->score[1], buf));
	mlx_string_put(fl->mlx_ptr, fl->win_ptr, 1000 + 30, 160,
			g_colors[TEXT], "Guaranteed area:");
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
			1300 - 15 - ((int)ft_strlen(fl->p1) * 10) / 2 -
			ft_intlen(AVL(1)) * 10 - 10,
			160, g_colors[RED],
			ft_strcat(ft_itoa_buf(AVL(1), buf), "%"));
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
			1300 + 45 + ((int)ft_strlen(fl->p2) * 10) / 2 -
			ft_intlen(AVL(0)) * 10 - 10,
			160, g_colors[GREEN],
			ft_strcat(ft_itoa_buf(AVL(0), buf), "%"));
}

void		ft_draw_base(t_filler *fl)
{
	fl->p1 = ft_toupper_str(fl->p1);
	fl->p2 = ft_toupper_str(fl->p2);
	if (fl->st[0] && !fl->st[1])
		fl->turn = 0;
	if (fl->st[1] && !fl->st[0])
		fl->turn = 1;
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
			1300 - 30 - (int)ft_strlen(fl->p1) * 10, 80, g_colors[RED], fl->p1);
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
			1300 - 30, 80, g_colors[TEXT], "  VS  ");
	mlx_string_put(fl->mlx_ptr, fl->win_ptr,
			1300 + 30, 80, g_colors[GREEN], fl->p2);
	if (fl->turn == 1)
		ft_draw_line(fl,
				(t_point){1300 - 30 - (int)ft_strlen(fl->p1) * 10, 100},
				(int)ft_strlen(fl->p1) * 10, g_colors[RED]);
	else
		ft_draw_line(fl, (t_point){1300 + 30, 100},
				(int)ft_strlen(fl->p2) * 10, g_colors[GREEN]);
}
