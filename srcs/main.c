/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:02:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/02 11:13:08 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // todo delete it
#include "libft.h"
#include "ft_filler.h"

#include <unistd.h>
#include <fcntl.h>

int main()
{
	t_filler *fl;

	ft_fdprintf(2, "{Red}#######{eof}\n");

	if (!(fl = ft_start_gama()))
		return (0);

	ft_fdprintf(2, "{Red}filler=%p\n", fl);
	ft_fdprintf(2, "player=%d{eof}\n", fl->player);

	if (!ft_game_master(fl))
	{
		ft_filler_free(fl); // todo use filler-free
		return (0);
	}
	ft_send_ray(fl, (t_point){14, 12}, (t_point){13, 0});
	ft_print_map(fl);


	ft_filler_free(fl);
	return 0;
}