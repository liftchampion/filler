/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gates.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:25:36 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 22:16:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"

static inline void		ft_fill_nhbs(t_filler *flr, t_point p, int nbs[8],
							int plr)
{
	nbs[0] = (p.x > 0) ?
				flr->heat_map[plr][p.y][p.x - 1] : -1;
	nbs[1] = (p.x > 0 && p.y > 0) ?
				flr->heat_map[plr][p.y - 1][p.x - 1] : -1;
	nbs[2] = (p.y > 0) ?
				flr->heat_map[plr][p.y - 1][p.x] : -1;
	nbs[3] = (p.y > 0 && p.x < flr->w - 1) ?
				flr->heat_map[plr][p.y - 1][p.x + 1] : -1;
	nbs[4] = (p.x < flr->w - 1) ?
				flr->heat_map[plr][p.y][p.x + 1] : -1;
	nbs[5] = (p.x < flr->w - 1 && p.y < flr->h - 1) ?
				flr->heat_map[plr][p.y + 1][p.x + 1] : -1;
	nbs[6] = (p.y < flr->h - 1) ?
				flr->heat_map[plr][p.y + 1][p.x] : -1;
	nbs[7] = (p.x > 0 && p.y < flr->h - 1) ?
				flr->heat_map[plr][p.y + 1][p.x - 1] : -1;
}

void					ft_sum_gate(register t_filler *fl, t_point pt,
							int *sum, int deep)
{
	int nhbs[8];
	int val;
	int i;
	int is_start;

	is_start = !deep;
	++deep;
	val = fl->heat_map[0][pt.y][pt.x];
	if (val <= 0)
		return ;
	fl->heat_map[0][pt.y][pt.x] = -1000000 - fl->heat_map[0][pt.y][pt.x];
	*sum += val;
	ft_fill_nhbs(fl, pt, nhbs, 0);
	i = -1;
	while (++i < 8)
	{
		if (nhbs[i] > val || (!is_start && nhbs[i] == val))
			ft_sum_gate(fl, (t_point){
					pt.x + (i >= 3 && i <= 5) - (!i || i == 1 || i == 7),
					pt.y - (i >= 1 && i <= 3) + (i >= 5 && i <= 7)}, sum, deep);
	}
}

void					ft_restore_map(register t_filler *fl)
{
	register int i;
	register int j;

	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			if (fl->heat_map[0][i][j] < -900000)
			{
				fl->heat_map[0][i][j] = -1000000 - fl->heat_map[0][i][j];
			}
		}
	}
}

int						ft_is_gate_pt(register t_filler *fl, t_point pt)
{
	const int	val = fl->heat_map[1][pt.y][pt.x];
	int			nhbs[8];
	int			i;
	int			res;

	ft_fill_nhbs(fl, pt, nhbs, 1);
	i = -1;
	while (++i < 4)
		if (nhbs[i * 2] <= 0 && nhbs[(i * 2 + 1) % 8] <= 0 &&
				nhbs[(i * 2 + 2) % 8] <= 0)
			return (0);
	res = 0;
	i = -1;
	while (++i < 8)
	{
		if (nhbs[i] == -2 || nhbs[i] > val)
			return (0);
		if ((nhbs[i] == nhbs[(i + 3) % 8] ||
				nhbs[i] == nhbs[(i + 4) % 8] ||
				nhbs[i] == nhbs[(i + 5) % 8]) && nhbs[i] < val)
			res = 1;
	}
	return (res == 1);
}

int						ft_parse_gates(register t_filler *fl)
{
	register int	i;
	register int	j;
	int				k;
	int				gate_val;
	int				val;

	i = -1;
	while (++i < fl->h && (j = -1))
		while (++j < fl->w)
			if (ft_is_gate_pt(fl, (t_point){j, i}))
			{
				gate_val = fl->heat_map[1][i][j];
				ft_sum_gate(fl, (t_point){j, i}, &(fl->heat_map[2][i][j]), 0);
				fl->heat_map[2][i][j] /= gate_val;
				k = gate_val;
				val = 0;
				while (--k > 0)
				{
					val += gate_val / k;
					ft_draw_circle_x(fl, gate_val, k, (t_point){j, i});
					ft_draw_circle_y(fl, gate_val, k, (t_point){j, i});
				}
			}
	ft_restore_map(fl);
	return (1);
}
