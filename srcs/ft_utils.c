/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:59:08 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 03:59:08 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

int 	ft_free_ret(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

void ft_filler_free(t_filler *fl)
{
	int i;

	i = 0;
	if (!fl)
		return ;
	ft_free_fig(&fl->curr_fig, 0);
	if (fl->map)
		while (fl->h > 0)
			free(fl->map[--fl->h]);
	free(fl->map);
	free(fl);
}
