/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:46:50 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 18:35:05 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"
#include <mlx.h>
#include <zconf.h>
#include <time.h>

int			ft_key_event_proceeder(int key, void *param)
{
	t_filler *fl;

	fl = (t_filler*)param;
	if (key == ESC)
	{
		ft_kill_players(fl);
		exit(0);
	}
	return (0);
}

int			ft_mlx_close(void *p)
{
	t_filler *fl;

	fl = (t_filler*)p;
	ft_kill_players(fl);
	exit(0);
}

int			ft_parse_cycle(t_filler *fl)
{
	if (!ft_map_parser(fl))
		return (0);
	if (!ft_figure_parser(fl))
		return (0);
	if (!ft_result_parser(fl))
		return (0);
	return (1);
}

int			ft_expose(void *dt)
{
	t_filler	*fl;
	static int	stop = 0;

	fl = (t_filler*)dt;
	if (stop)
		return (0);
	if (!ft_parse_cycle(fl))
	{
		stop = 1;
		return (0);
	}
	ft_gather_data(fl);
	ft_draw_map(fl);
	ft_draw_base(fl);
	ft_draw_info(fl);
	ft_draw_status(fl);
	return (1);
}

int			main(void)
{
	t_filler	*fl;
	static int	for_img[3] = {32, 1600, 0};

	if (!(fl = ft_parse_begin()))
		return (ft_free_filler(fl, 0));
	if (!(fl->mlx_ptr = mlx_init()))
		return (0);
	if (!(fl->win_ptr = mlx_new_window(fl->mlx_ptr, 1600, 1000,
			"The Battle begins")))
		return (0);
	fl->img = mlx_new_image(fl->mlx_ptr, 1600, 1000);
	fl->img_data = mlx_get_data_addr(fl->img, &for_img[0], &for_img[1],
			&for_img[2]);
	ft_bzero(fl->img_data, sizeof(char) * 1000 * 1600 * 4);
	mlx_loop_hook(fl->mlx_ptr, ft_expose, fl);
	mlx_hook(fl->win_ptr, 17, 0, ft_mlx_close, fl);
	mlx_key_hook(fl->win_ptr, ft_key_event_proceeder, fl);
	ft_draw_rect(fl, (t_point){1000, 1000}, (t_point){0, 0},
			g_colors[GRAY]);
	ft_draw_rect(fl, (t_point){600, 1000}, (t_point){1000, 0},
			g_colors[DARK_GRAY]);
	mlx_put_image_to_window(fl->mlx_ptr, fl->win_ptr, fl->img, 0, 0);
	ft_draw_base(fl);
	mlx_loop(fl->mlx_ptr);
	return (0);
}
