/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:31:10 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 18:24:46 by ggerardy         ###   ########.fr       */
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

int				ft_free_filler(t_filler *fl, int ret)
{
	if (!fl)
		return (ret);
	fl = 0;
	free(fl);
	return (ret);
}

int				ft_free_ret(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

void			ft_kill_players(t_filler *fl)
{
	char buf[100];

	ft_bzero(buf, 100);
	ft_strlcpy(buf, "kill -KILL $(pgrep ", 100);
	ft_strlcat(buf, ft_tolower_str(fl->p1), 100);
	ft_strlcat(buf, ".filler) 2> /dev/null", 100);
	system(buf);
	ft_bzero(buf, 100);
	ft_strlcpy(buf, "kill -KILL $(pgrep ", 100);
	ft_strlcat(buf, ft_tolower_str(fl->p2), 100);
	ft_strlcat(buf, ".filler) 2> /dev/null", 100);
	system(buf);
	system("kill -KILL $(pgrep ruby) 2> /dev/null");
}
