/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 22:16:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strncat(char *dest, const char *src, size_t nb)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = dest;
	while (*dest)
		dest++;
	while (*src && i < nb)
	{
		i++;
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
	return (ptr);
}
