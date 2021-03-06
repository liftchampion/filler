/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_gatherers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 07:03:49 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 22:16:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

t_poi_fl			ft_sum_points(t_poi_fl p1, t_poi_fl p2)
{
	return ((t_poi_fl){p1.x + p2.x, p1.y + p2.y});
}
