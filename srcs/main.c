/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 19:46:50 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/10 02:27:04 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler_vis.h"


int		ft_main_loop(void)
{
	t_filler *fl;

	if (!(fl = ft_parse_begin()))
		return (ft_free_filler(fl, 0));
	ft_map_parser(fl);
	ft_figure_parser(fl);
	//while (ft_map_parser(fl) && ft_figure_parser(fl))
	//{
		ft_print_filler(fl);
	//}


	return (1);
}

int main()
{
	ft_main_loop();
	return 0;
}