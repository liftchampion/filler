/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:02:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/01 08:47:27 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // todo delete it
#include "libft.h"
#include "ft_filler.h"

#include <unistd.h>
#include <fcntl.h>

t_filler *ft_start_gama(void)
{
	t_filler	*fl;
	char		*line;

	line = (char*)1lu;
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 32) || !line ||
		!(fl = (t_filler*)ft_memalloc(sizeof(t_filler))))
		return (0);
	if (!ft_strstr(line, "$$$ exec p"))
	{
		free(line);
		free(fl);
		return (0);
	}
	fl->player = ft_atoi(line + 10);
	if ((fl->player != 1 && fl->player != 2) ||
								ft_strcmp(line + 11, " : [./ggerardy.filler]"))
	{
		free(line);
		free(fl);
		return (0);
	}
	free(line);
	return (fl);
}

int main()
{
	t_fig *f;
	t_filler *filler;

	if (!(filler = ft_start_gama()))
		return (0);

	int file = open("log", O_TRUNC | O_WRONLY);

	ft_fdprintf(file, "filler=%p\n", filler);
	ft_fdprintf(file, "player=%d\n", filler->player);


	free(filler);
	return 0;
}