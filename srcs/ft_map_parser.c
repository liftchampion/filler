/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 08:52:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/14 19:25:54 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_filler.h"
#include <math.h>

#define VPUSH(v, n) ft_vector_push_back(&(v), (n))
#define HM flr->heat_map[pl]

int ft_make_map(t_filler *fl)
{
	int i;
	char **mtr;

	if (!(mtr = (char**)ft_memalloc(sizeof(char*) * fl->h)))
		return (0);
	i = -1;
	while (++i < fl->h)
	{
		if (!(mtr[i] = (char *)ft_memalloc(sizeof(char) * (fl->w + 1))))
		{
			while (i >= 0)
				free(mtr[i--]);
			return (ft_free_ret(mtr, 0));
		}
		ft_memset(mtr[i], '.', (size_t)fl->w);
	}
	fl->map = mtr;
	return (1);
}

int ft_make_heat_map(t_filler *fl)
{
	int i;
	int **mtr[3];

	if (!(mtr[0] = (int **)ft_memalloc(sizeof(int *) * fl->h)) ||
			!(mtr[1] = (int **)ft_memalloc(sizeof(int *) * fl->h)) ||
			!(mtr[2] = (int **)ft_memalloc(sizeof(int *) * fl->h)))
		return (0);
	i = -1;
	while (++i < fl->h)
	{
		if (!(mtr[0][i] = (int *)malloc(sizeof(int) * (fl->w))) ||
				!(mtr[1][i] = (int *)malloc(sizeof(int) * (fl->w))) ||
				!(mtr[2][i] = (int *)malloc(sizeof(int) * (fl->w))))
		{
			while (i >= 0)
			{
				free(mtr[0][i]);
				free(mtr[1][i]);
				free(mtr[2][i--]);
			}
			return (ft_free_ret(mtr[0], 0) + ft_free_ret(mtr[1], 0)
					+ ft_free_ret(mtr[2], 0));
		}
	}
	fl->heat_map[0] = mtr[0];
	fl->heat_map[1] = mtr[1];
	fl->heat_map[2] = mtr[2];
	return (1);
}

static inline int		ft_check_and_add_pt(t_point pt, t_filler *flr, int ds, int pl)
{
	if (pt.x > 0 && !HM[pt.y][pt.x - 1] &&
				(HM[pt.y][pt.x - 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y}));
	if (pt.y > 0 && !HM[pt.y - 1][pt.x] &&
				(HM[pt.y - 1][pt.x] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x, pt.y - 1}));
	if (pt.x < flr->w - 1 && !HM[pt.y][pt.x + 1] &&
				(HM[pt.y][pt.x + 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y}));
	if (pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x] &&
				(HM[pt.y + 1][pt.x] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x, pt.y + 1}));
	if (pt.x > 0 && pt.y > 0 && !HM[pt.y - 1][pt.x - 1] &&
				(HM[pt.y - 1][pt.x - 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y - 1}));
	if (pt.x > 0 && pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x - 1] &&
				(HM[pt.y + 1][pt.x - 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x - 1, pt.y + 1}));
	if (pt.x < flr->w - 1 && pt.y > 0 && !HM[pt.y - 1][pt.x + 1] &&
				(HM[pt.y - 1][pt.x + 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y - 1}));
	if (pt.x < flr->w - 1 && pt.y < flr->h - 1 && !HM[pt.y + 1][pt.x + 1] &&
				(HM[pt.y + 1][pt.x + 1] = ds))
		VPUSH(flr->points[pl], (*(void**)&(t_point){pt.x + 1, pt.y + 1}));
	return (flr->points[pl] ? 1 : 0);
}

int	ft_fill_heat_map(register t_filler *fl, register int pl)
{
	register size_t init_len;
	register int begin;
	register int i;
	size_t new_begin;
	int dst;

	begin = 0;
	dst = 1;
	init_len = fl->points[pl]->len;
	while (1)
	{
		i = (int)fl->points[pl]->len;
		new_begin = fl->points[pl]->len;
		while (--i >= begin)
			if (!ft_check_and_add_pt(POINT(fl->points[pl], i), fl, dst, pl))
				return (0);
		begin = (int)new_begin;
		if (new_begin == fl->points[pl]->len)
			break ;
		++dst;
	}
	fl->points[pl]->len = init_len;
	return (1);
}

void		ft_zero_heat_map(register t_filler *fl, int clean_gates)
{
	register int i;

	i = -1;
	while (++i < fl->h)
	{
		if (!clean_gates)
		{
			ft_bzero(fl->heat_map[0][i], sizeof(int) * fl->w);
			ft_bzero(fl->heat_map[1][i], sizeof(int) * fl->w);
		}
		else
			ft_bzero(fl->heat_map[2][i], sizeof(int) * fl->w);
	}
}

int 	ft_count_enemy_unr(register t_filler *fl)
{
	register int res;
	register int i;
	register int j;

	res = 0;
	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			res += !fl->heat_map[1][i][j] || fl->heat_map[1][i][j] == -2;
		}
	}
	fl->unrch_opp = res;
	return (1);
}

void 	ft_fill_nhbs(t_filler *fl, t_point pt, int nhbs[8], int pl)
{
	nhbs[0] = (pt.x > 0) ?
			fl->heat_map[pl][pt.y][pt.x - 1] : -1;
	nhbs[1] = (pt.x > 0 && pt.y > 0) ?
			fl->heat_map[pl][pt.y - 1][pt.x - 1] : -1;
	nhbs[2] = (pt.y > 0) ?
			fl->heat_map[pl][pt.y - 1][pt.x] : -1;
	nhbs[3] = (pt.y > 0 && pt.x < fl->w - 1) ?
			fl->heat_map[pl][pt.y - 1][pt.x + 1] : -1;
	nhbs[4] = (pt.x < fl->w - 1) ?
			fl->heat_map[pl][pt.y][pt.x + 1] : -1;
	nhbs[5] = (pt.x < fl->w - 1 && pt.y < fl->h - 1) ?
			fl->heat_map[pl][pt.y + 1][pt.x + 1] : -1;
	nhbs[6] = (pt.y < fl->h - 1) ?
			fl->heat_map[pl][pt.y + 1][pt.x] : -1;
	nhbs[7] = (pt.x > 0 && pt.y < fl->h - 1) ?
			fl->heat_map[pl][pt.y + 1][pt.x - 1] : -1;
}

void 	ft_sum_gate(register t_filler *fl, t_point pt, int *sum, int deep)
{
	int nhbs[8];
	int val;
	int i;
	int is_start;

	is_start = !deep;
	++deep;
	val = fl->heat_map[0][pt.y][pt.x];
	if (val <= 0)
		return;
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

void 	ft_restore_map(register t_filler *fl)
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

int 	ft_is_gate_pt(register t_filler *fl, t_point pt)
{
	const int val = fl->heat_map[1][pt.y][pt.x];
	int nhbs[8];
	int i;
	int res;

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

void 	ft_draw_circle_y(register t_filler *fl, int val, int r, t_point c)
{
	double y_fr;
	double y_to;
	int x1;

	y_fr = c.y - r / 2.;
	y_to = c.y + r / 2.;
	while (y_fr <= y_to)
	{
		x1 = (int)(sqrt(SQ(r) - SQ(y_fr - c.y)) + 0.);
		if ((int)(y_fr + 0.) >= 0 && (int)(y_fr + 0.) <= fl->h - 1)
		{
			if (x1 + c.x >= 0 && x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.)][x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.)][x1 + c.x] = val;
			}
			if (-x1 + c.x >= 0 && -x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.)][-x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.)][-x1 + c.x] = val;
			}
		}
		x1 = (int)(sqrt(SQ(r) - SQ(y_fr - c.y)) + 0.5);
		if ((int)(y_fr + 0.5) >= 0 && (int)(y_fr + 0.5) <= fl->h - 1)
		{
			if (x1 + c.x >= 0 && x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.5)][x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.5)][x1 + c.x] = val;
			}
			if (-x1 + c.x >= 0 && -x1 + c.x <= fl->w - 1)
			{
				if (fl->heat_map[1][(int)(y_fr + 0.5)][-x1 + c.x] > 0)
					fl->heat_map[2][(int)(y_fr + 0.5)][-x1 + c.x] = val;
			}
		}
		++y_fr;
	}
}

void 	ft_draw_circle(register t_filler *fl, int val, int r, t_point c)
{
	double x_fr;
	double x_to;
	int y1;

	ft_draw_circle_y(fl, val, r, c);
	x_fr = c.x - r / 2.;
	x_to = c.x + r / 2.;
	while (x_fr <= x_to)
	{
		y1 = (int)(sqrt(SQ(r) - SQ(x_fr - c.x)) + 0.);
		if ((int)(x_fr + 0.) >= 0 && (int)(x_fr + 0.) <= fl->w - 1)
		{
			if (y1 + c.y >= 0 && y1 + c.y <= fl->h - 1)
				if (fl->heat_map[1][y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][y1 + c.y][(int)(x_fr + 0.)] = val;
			if (-y1 + c.y >= 0 && -y1 + c.y <= fl->h - 1)
				if (fl->heat_map[1][-y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][-y1 + c.y][(int)(x_fr + 0.)] = val;
		}
		y1 = (int)(sqrt(SQ(r) - SQ(x_fr - c.x)) + 0.5);
		if ((int)(x_fr + 0.5) >= 0 && (int)(x_fr + 0.5) <= fl->w - 1)
		{
			if (y1 + c.y >= 0 && y1 + c.y <= fl->h - 1)
			{
				if (fl->heat_map[1][y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][y1 + c.y][(int)(x_fr + 0.5)] = val;
			}
			if (-y1 + c.y >= 0 && -y1 + c.y <= fl->h - 1)
			{
				if (fl->heat_map[1][-y1 + c.y][(int)x_fr] > 0)
					fl->heat_map[2][-y1 + c.y][(int)(x_fr + 0.5)] = val;
			}
		}
		++x_fr;
	}
}

int 	ft_parse_gates(register t_filler *fl)
{
	register int 	i;
	register int	j;
	int 			k;
	int 			gate_val;
	int 			val;

	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
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
					ft_draw_circle(fl, gate_val, k, (t_point){j, i});
				}
			}
		}
	}
	ft_restore_map(fl);

	return (1);
}

int 	ft_update_heat_map(register t_filler *fl)
{
	register size_t	i;
	register size_t	to_go;
	int				pl;

	if ((!fl->heat_map[0] || !fl->heat_map[1]) && !ft_make_heat_map(fl))
		return (0);
	ft_zero_heat_map(fl, 0);
	pl = -1;
	while (++pl < 2)
	{
		i = (size_t)-1;
		to_go = fl->points[pl]->len;
		while (++i < to_go)
		{
			fl->heat_map[pl][POINT(fl->points[pl], i).y]
				[POINT(fl->points[pl], i).x] = -1;
			fl->heat_map[!pl][POINT(fl->points[pl], i).y]
				[POINT(fl->points[pl], i).x] = -2;
		}

	}
	if (!ft_fill_heat_map(fl, 0) || !ft_fill_heat_map(fl, 1))
		return (0);
	ft_parse_gates(fl);
	return (ft_count_enemy_unr(fl));
}

int		ft_map_parser(register t_filler *fl)
{
	register int	i;
	register int	j;
	char			*line;
	int 			was_begin;

	if ((i = -1) && !fl->map && !ft_make_map(fl))
		return (0);
	was_begin = 0;
	while (++i < fl->h && (line = (char*)1lu) && ft_get_next_line(0, &line, 1))
	{
		if (!line)
			return (0);
		was_begin = (ft_strstr(line, "000") && !was_begin) ? 1 : was_begin;
		if ((j = 3) && !was_begin && ft_free_ret(line, 1) && (--i || 1))
			continue;
		while (line[++j])
			if (ft_strchr("oOxX", line[j]) && (fl->map[i][j - 4] = line[j]))
				if (!ft_vector_push_back(&fl->points[ft_tolower(line[j]) !=
				PLAYERS[fl->player]] , *(void**)&(t_point){j - 4, i}))
					return (ft_free_ret(line, 0));

		free(line);
	}
	return (ft_update_heat_map(fl));
}

int		ft_game_parser(register t_filler *fl)
{
	char *line;

	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1) || !line)
		return (0);
	fl->points[0]->len = 0;
	fl->points[1]->len = 0;
	if (ft_strstr(line, "Plateau ") != line || (fl->h = ft_atoi(line + 8)) <= 0
			|| (fl->w = ft_atoi(line + 8 + ft_intlen(fl->h))) <= 0 ||
			!ft_map_parser(fl) || ft_free_ret(line, 0))
		return (ft_free_ret(line, 0));
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1) || !line)
		return (0);
	if (ft_strstr(line, "Piece ") != line || !ft_figure_parser(line, fl) ||
			ft_free_ret(line, 0))
		return (ft_free_ret(line, 0));
	return (1);
}