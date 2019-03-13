/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:46:50 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 08:50:19 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"
#include <mlx.h>
#include <zconf.h>

int 		ft_expose(void *dt);

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


int 		ft_parse_cycle(t_filler *fl)
{
	if (!ft_map_parser(fl))
		return (0);
	if (!ft_figure_parser(fl))
		return (0);
	if (!ft_result_parser(fl))
		return (0);
	return (1);
}



int 		ft_expose(void *dt)
{
	t_filler *fl;
	static int pos = 20;
	char *s;

	fl = (t_filler*)dt;
	ft_draw_rect(fl, (t_point){1000, 1000}, (t_point){0, 0}, g_colors[GRAY]);
	ft_draw_rect(fl, (t_point){600, 1000}, (t_point){1000, 0}, g_colors[DARK_GRAY]);
	ft_draw_base(fl);
	while (ft_parse_cycle(fl))
	{
		ft_draw_map(fl);
		ft_sprintf(&s, "%d %d", fl->pos_x, fl->pos_y);
		mlx_string_put(fl->mlx_ptr, fl->win_ptr, pos, pos, 0x00ffffff, s);
		mlx_do_sync(fl->mlx_ptr);
		free(s);
		pos += 20;
		ft_printf("{\\202}Total{eof}\n");
		ft_print_filler(fl);
	}
	pos += 20;
	return (0);
}

// todo check error sometimes could be before Piece (after map)

int main()
{
	t_filler *fl;

	if (!(fl = ft_parse_begin()))
		return (ft_free_filler(fl, 0));
	if (!(fl->mlx_ptr = mlx_init()))
		return (0); // todo 0 ?
	if (!(fl->win_ptr = mlx_new_window(fl->mlx_ptr, 1600, 1000, "The Battle begins")))
		return (0); // todo 0 ?
	mlx_expose_hook(fl->win_ptr, ft_expose, fl);
	mlx_hook(fl->win_ptr, 17, 0, ft_mlx_close, 0);
	mlx_key_hook(fl->win_ptr, ft_key_event_proceeder, fl);
	mlx_loop(fl->mlx_ptr);


	return 0;
}