/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:46:50 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 05:40:42 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"
#include <mlx.h>
#include <pthread.h>
#include <zconf.h>

/*
 *
Warrior: [ 0.35 2 3.85 1.35 0 1 1.7 0 -1 0] score is 14685
 win_rate(round) is 32.6667% win_rate(game) is 40
players/bmiklaz.filler: 2
players/carli.filler: 14
players/jcorwin.filler: 10
players/lcharvol.filler: 11
players/mwunsch.filler: 12
 *
 */

int ft_key_event_proceeder(int key, void *param)
{
	(void)param;
	if (key == ESC)
		exit(0);
	return (0);
}

int			ft_mlx_close(void *p)
{
	(void)p;
	exit(0);
}

int			ft_expose(void *dt)
{
	t_filler *fl;
	//char *str;
	static int pos = 100;

	fl = (t_filler*)dt;
	if (fl->wait == READ)
		return (0);
	//ft_sprintf(&str, "%d %d", fl->pos_x, fl->pos_y);
	//sleep(1);
	//mlx_clear_window(fl->mlx_ptr, fl->win_ptr);
	mlx_string_put(fl->mlx_ptr, fl->win_ptr, pos, pos, 0xffffffff, "HUI");
	//mlx_string_put(fl->mlx_ptr, fl->win_ptr, 200, 200, 0x00ffffff, "HUI");
	//free(str);
	pos += 10;
	fl->wait = READ;
	return (0);
}

void		*ft_main_draw_loop(void* dt)
{
	t_filler *fl;

	fl = (t_filler*)dt;

	//mlx_string_put(fl->mlx_ptr, fl->win_ptr, 500, 500, 0xffffffff, "HUI");
	mlx_loop(fl->mlx_ptr);
	return (0);
}

int 		ft_parse_cycle(t_filler *fl)
{
	int res = 1;

	res *= ft_map_parser(fl);
	if (res)
		res *= ft_figure_parser(fl);
	if (res)
		res *= ft_result_parser(fl);

	ft_printf("{\\202}Total{eof}\n");
	ft_print_filler(fl);
	return (res);
}

void		*ft_main_read_loop(void* dt)
{
	t_filler *fl;


	//ft_map_parser(fl);
	//ft_figure_parser(fl);
	fl = (t_filler*)dt;
	fl->wait = READ;
	int a = 20;
	int b = 20;
	int delta = 20;

	while (((fl->wait = READ) && ft_map_parser(fl) && ft_figure_parser(fl) && ft_result_parser(fl)))
	{
		char *s;
		ft_sprintf(&s, "%d %d", fl->pos_x, fl->pos_y);
		nanosleep(&(struct timespec){0, 50000000}, 0);
		mlx_string_put(fl->mlx_ptr, fl->win_ptr, a, b, 0xffffffff, s);
		mlx_do_sync(fl->mlx_ptr);
		/*fl->wait = DRAW;
		while (fl->wait != READ)
			;*/
		free(s);
		ft_printf("{\\202}Total{eof}\n");
		ft_print_filler(fl);
		a += 20;
		if (b == 1000)
		{
			a = 0;
			delta = -20;
		}
		b += delta;
	}

	return (0);
}

// todo check error sometimes could be before Piece (after map)

int main()
{
	t_filler *fl;
	pthread_t read_th;

	if (!(fl = ft_parse_begin()))
		return (ft_free_filler(fl, 0));
	if (!(fl->mlx_ptr = mlx_init()))
		return (0); // todo 0 ?
	if (!(fl->win_ptr = mlx_new_window(fl->mlx_ptr, 1000, 1000, "The Battle begins")))
		return (0); // todo 0 ?
	//mlx_expose_hook(fl->win_ptr, ft_expose, fl);
	mlx_hook(fl->win_ptr, 17, 0, ft_mlx_close, 0);
	mlx_key_hook(fl->win_ptr, ft_key_event_proceeder, 0);


	pthread_create(&read_th, 0, ft_main_read_loop, fl);

	ft_main_draw_loop(fl);

	pthread_join(read_th, 0);

	/*pthread_create(&draw_th, 0, ft_main_draw_loop, fl);

	pthread_join(draw_th, 0);

	pthread_create(&read_th, 0, ft_main_read_loop, fl);

	pthread_join(read_th, 0);*/

	//ft_main_draw_loop(fl);
	//ft_main_read_loop(fl);
	return 0;
}