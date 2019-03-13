/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:31:10 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/13 09:58:16 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"
#include <stdlib.h>

void			ft_pix_put_img(t_filler *fl, int x, int y, int color)
{
	int *img;

	if (x >= 0 && x < 1600 && y >= 0 && y < 1000)
	{
		img = (int*)fl->img_data;
		img[y * 1600 + x] = color;
	}
}

void			ft_print_filler(t_filler *fl)
{
	char enm[6][4] = {"OKE", "ERR", "SEG", "WRG", "END", "OUT"};
	ft_printf("p1 - %s, p2 - %s\n", fl->p1, fl->p2);
	ft_printf("p1 - %s, p2 - %s\n", enm[fl->st[0]], enm[fl->st[1]]);
	ft_printf("turn - %d\n", fl->turn);
	ft_print_map(fl);
	ft_print_fig(fl);
	ft_printf("to %d %d\n", fl->pos_y, fl->pos_x);
}

int 	ft_free_filler(t_filler *fl, int ret)
{
	if (!fl)
		return (ret);
	fl = 0;
	// todo free
	return (ret);
}

int 	ft_free_ret(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

int		ft_wait(t_filler *fl, t_mtx mtx)
{
	while (fl->wait == mtx)
	{
		;
	}
	fl->wait = !mtx;
	return (1);
}
