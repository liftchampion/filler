/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:02:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 19:18:15 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

#include <unistd.h>
#include <fcntl.h>

int main()
{
	t_filler *fl;

	if (!(fl = ft_start_gama()))
		return (0);
	if (!ft_game_master(fl))
	{
		return (ft_filler_free(fl, 0));
	}
	return (ft_filler_free(fl, 0));
}
