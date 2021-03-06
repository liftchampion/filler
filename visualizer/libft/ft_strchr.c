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

char		*ft_strchr(const char *str, int ch)
{
	char c;

	c = (char)ch;
	while (*str)
	{
		if (*str == c)
		{
			return ((char*)str);
		}
		str++;
	}
	if (*str == 0 && c == 0)
		return ((char*)str);
	return (0);
}
