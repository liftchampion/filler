/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:31:10 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/10 01:54:40 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"
#include <stdlib.h>

void			ft_print_filler(t_filler *fl)
{
	ft_printf("p1 - %s, p2 - %s\n", fl->p1, fl->p2);
	ft_print_map(fl);
	ft_print_fig(fl);
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