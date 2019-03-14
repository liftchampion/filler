/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgalyeon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 03:34:22 by rgalyeon          #+#    #+#             */
/*   Updated: 2018/12/07 21:32:55 by rgalyeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_ft.h"

double	ft_matrix_max(t_matrix *mass)
{
	size_t	i;
	size_t	j;
	double	mmax;

	mmax = (mass->matrix)[0][0];
	i = -1;
	while (++i < mass->row)
	{
		j = -1;
		while (++j < mass->col)
		{
			if ((mass->matrix)[i][j] > mmax)
				mmax = (mass->matrix)[i][j];
		}
	}
	return (mmax);
}
