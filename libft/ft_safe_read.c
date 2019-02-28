/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:13:42 by ggerardy          #+#    #+#             */
/*   Updated: 2019/02/28 19:38:31 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** ssize_t		ft_safe_read(int fd, void *buf, size_t n_byte)
** {
**	ssize_t res;
**	ssize_t moment_res;
**
**	res = read(fd, buf, n_byte);
**	if (res == n_byte || res == -1)
**		return (res);
**	buf += res;
**	moment_res = read(fd, buf, n_byte);
**	if (moment_res == 0 || moment_res == -1)
**		return (moment_res);
**	res += moment_res;
**	buf += moment_res;
**	while (moment_res != 0 && res < n_byte)
**	{
**		moment_res = read(fd, buf, n_byte);
**	}
** }
*/
