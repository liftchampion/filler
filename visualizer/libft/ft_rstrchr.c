/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rstrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 22:41:02 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 22:16:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_rstrchr(const char *str, int ch)
{
	char c;
	char *chr;

	c = (char)ch;
	chr = 0;
	while (*str)
	{
		if (*str == c)
		{
			chr = (char*)str;
		}
		str++;
	}
	if (*str == 0 && c == 0)
		return ((char*)str);
	return (chr);
}
