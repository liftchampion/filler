/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:06:26 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/03/14 19:06:41 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void			ft_fd_print_string(t_string *str, int fd)
{
	if (!str)
	{
		ft_putstr_fd("NO V_STRING\n", fd);
		return ;
	}
	write(fd, str->data, str->len);
}

void			ft_print_string(t_string *str)
{
	if (!str)
	{
		ft_putstr("NO V_STRING\n");
		return ;
	}
	write(1, str->data, str->len);
}
