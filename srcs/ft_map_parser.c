/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 08:52:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/11 15:23:24 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h> // todo
#include "libft.h"
#include "ft_filler.h"

#define VPUSH(v, n) ft_vector_push_back(&(v), (n))
#define HM flr->heat_map[pl]

//!HM[pt.y + 1][pt.x + 1]
#define LG(a, b) (HM[pt.y + b][pt.x + a] > ds)

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
	int **mtr[2];

	if (!(mtr[0] = (int**)ft_memalloc(sizeof(int*) * fl->h)) ||
		!(mtr[1] = (int**)ft_memalloc(sizeof(int*) * fl->h)))
		return (0);
	i = -1;
	while (++i < fl->h)
	{
		if (!(mtr[0][i] = (int*)malloc(sizeof(int) * (fl->w))) ||
			!(mtr[1][i] = (int*)malloc(sizeof(int) * (fl->w))))
		{
			while (i >= 0)
			{
				free(mtr[0][i--]);
				free(mtr[1][i--]);
			}
			return (ft_free_ret(mtr[0], 0) + ft_free_ret(mtr[1], 0));
		}
	}
	fl->heat_map[0] = mtr[0];
	fl->heat_map[1] = mtr[1];
	return (1);
}

void ft_print_map(t_filler *fl)
{
	int i;
	int j;

	char **mtr;

	if (!(mtr = (char**)ft_memalloc(sizeof(char*) * fl->h)))
		return ;
	i = -1;
	while (++i < fl->h)
	{
		if (!(mtr[i] = (char *)ft_memalloc(sizeof(char) * (fl->w + 1))))
		{
			while (i >= 0)
				free(mtr[i--]);
			return (free(mtr));
		}
		ft_memset(mtr[i], '.', (size_t)fl->w);
	}

	i = -1;
	while (++i < (int)fl->points[0]->len)
	{
		mtr[POINT(fl->points[0], i).y][POINT(fl->points[0], i).x] = 'X';
	}
	i = -1;
	while (++i < (int)fl->points[1]->len)
	{
		mtr[POINT(fl->points[1], i).y][POINT(fl->points[1], i).x] = 'O';
	}
	char **tmp = fl->map;
	fl->map = mtr;

	j = -1;
	ft_fdprintf(2, "{Yellow}map_w=%d map_h=%d{eof}\n   ", fl->w, fl->h);
	while (++j < fl->w)
	{
		ft_fdprintf(2, "{Magenta} %2d{eof}", j);
	}
	i = -1;
	ft_fdprintf(2, "\n");
	while (++i < fl->h)
	{
		j = -1;
		ft_fdprintf(2, "{Magenta}%3d{eof}", i);
		while (++j < fl->w)
		{
			ft_fdprintf(2, "{Magenta}  %c{eof}", fl->map[i][j]);
		}
		ft_fdprintf(2, "\n");
	}
	fl->map = tmp;
	//ft_fdprintf(2, "{Magenta}%s{eof}\n", fl->map[i]);
}

void	ft_print_heat_map(t_filler *fl, int pl)
{
	int i;
	int j;
	static int count = 0;

	j = -1;
	/*for (int e = 0; e < fl->h + 2; ++e)
	{
		ft_fdprintf(2, "\033[A\033[K");
	}*/
	ft_fdprintf(2, "{Yellow}map_w=%d map_h=%d pl = %d num = %d{eof}\n   ",
			fl->w, fl->h, pl, ++count);
	while (++j < fl->w)
	{
		ft_fdprintf(2, "{Green} %3d{eof}", j);
	}
	i = -1;
	ft_fdprintf(2, "\n");
	while (++i < fl->h)
	{
		j = -1;
		ft_fdprintf(2, "{Green}%3d{eof}", i);
		while (++j < fl->w)
		{
			if (fl->heat_map[pl][i][j] == -1)
				ft_fdprintf(2, "{\\202}  %2d{eof}", fl->heat_map[pl][i][j]);
			else if (fl->heat_map[pl][i][j] == -2)
				ft_fdprintf(2, "{\\200}  %2d{eof}", fl->heat_map[pl][i][j]);
			else if (fl->heat_map[pl][i][j] < -10)
				ft_fdprintf(2, "{Red}  %2d{eof}", -1 * fl->heat_map[pl][i][j] - 10);
			else
				ft_fdprintf(2, "{Magenta}  %2d{eof}", fl->heat_map[pl][i][j]);
		}
		ft_fdprintf(2, "\n");
	}

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

void		ft_zero_heat_map(register t_filler *fl)
{
	register int i;

	i = -1;
	while (++i < fl->h)
	{
		ft_bzero(fl->heat_map[0][i], sizeof(int) * fl->w);
		ft_bzero(fl->heat_map[1][i], sizeof(int) * fl->w);
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
	///ft_fdprintf(2, "{Magenta}Unreachable for enemy %d{eof}\n", res);
	fl->unrch_opp = res;
	return (1);
}

void 	ft_fill_nhbs(t_filler *fl, t_point pt, int nhbs[8])
{
	nhbs[0] = (pt.x > 0) ?
			fl->heat_map[1][pt.y][pt.x - 1] : -1;
	nhbs[1] = (pt.x > 0 && pt.y > 0) ?
			fl->heat_map[1][pt.y - 1][pt.x - 1] : -1;
	nhbs[2] = (pt.y > 0) ?
			fl->heat_map[1][pt.y - 1][pt.x] : -1;
	nhbs[3] = (pt.y > 0 && pt.x < fl->w - 1) ?
			fl->heat_map[1][pt.y - 1][pt.x + 1] : -1;
	nhbs[4] = (pt.x < fl->w - 1) ?
			fl->heat_map[1][pt.y][pt.x + 1] : -1;
	nhbs[5] = (pt.x < fl->w - 1 && pt.y < fl->h - 1) ?
			fl->heat_map[1][pt.y + 1][pt.x + 1] : -1;
	nhbs[6] = (pt.y < fl->h - 1) ?
			fl->heat_map[1][pt.y + 1][pt.x] : -1;
	nhbs[7] = (pt.x > 0 && pt.y < fl->h - 1) ?
			fl->heat_map[1][pt.y + 1][pt.x - 1] : -1;
}

int 	ft_is_gate_pt(register t_filler *fl, t_point pt)
{
	const int val = fl->heat_map[1][pt.y][pt.x];
	int nhbs[8];
	int i;
	int res;

	ft_fill_nhbs(fl, pt, nhbs);
	i = -1;
	res = 0;
	while (++i < 8)
	{
		if (nhbs[i] == -2)
			return (0);
		if ((nhbs[i] == nhbs[(i + 3) % 8] ||
			nhbs[i] == nhbs[(i + 4) % 8] ||
			nhbs[i] == nhbs[(i + 5) % 8]) && nhbs[i] < val)
		{
			ft_fdprintf(2, "{Red}%d %d{eof}\n", pt.x, pt.y);
			res = (res == -1) ? -1 : 1;
			if (res == 1)
				fl->heat_map[0][pt.y][pt.x] = -10 - fl->heat_map[1][pt.y][pt.x];
		}
		if (nhbs[i] > val)
			res = -1;
	}
	return (res == 1);
}

void 	ft_parse_gates(register t_filler *fl)
{
	register int i;
	register int j;

	i = -1;
	while (++i < fl->h)
	{
		j = -1;
		while (++j < fl->w)
		{
			ft_is_gate_pt(fl, (t_point){j, i});
		}
	}
}

int 	ft_update_heat_map(register t_filler *fl)
{
	register size_t i;
	register size_t to_go;
	int pl;

	if ((!fl->heat_map[0] || !fl->heat_map[1]) && !ft_make_heat_map(fl))
		return (0);
	ft_zero_heat_map(fl);
	pl = -1;
	while (++pl < 2)
	{
		i = (size_t)-1;
		to_go = fl->points[pl]->len;
		while (++i < to_go)
		{
			fl->heat_map[pl][POINT(fl->points[pl], i).y][POINT(fl->points[pl], i).x] = -1;
			fl->heat_map[!pl][POINT(fl->points[pl], i).y][POINT(fl->points[pl], i).x] = -2;
		}
		if (!ft_fill_heat_map(fl, pl))
			return (0);
	}
	ft_parse_gates(fl);
	ft_print_heat_map(fl, 0);
	ft_print_heat_map(fl, 1);
	ft_fdprintf(2, "{Black}T{eof}\n");
	ft_fdprintf(2, "{Red}T{eof}\n");
	ft_fdprintf(2, "{Green}T{eof}\n");
	ft_fdprintf(2, "{Yellow}T{eof}\n");
	ft_fdprintf(2, "{Blue}T{eof}\n");
	ft_fdprintf(2, "{Magenta}T{eof}\n");
	ft_fdprintf(2, "{Cyan}T{eof}\n");
	ft_fdprintf(2, "{White}T{eof}\n");

	exit(42);
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
	///ft_print_map(fl); // todo print
	if (!(line = (char*)1lu) || !ft_get_next_line(0, &line, 1) || !line)
		return (0);
	if (ft_strstr(line, "Piece ") != line || !ft_figure_parser(line, fl) ||
			ft_free_ret(line, 0))
		return (ft_free_ret(line, 0));
	///ft_print_fig(fl->curr_fig); // todo print
	return (1);
}