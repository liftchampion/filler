/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   results_proceeder.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:28:42 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/04 12:28:42 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;


vector<vector<double> > pms;


ostream& operator << (ostream& os, vector<double> v)
{
	bool is_first = true;
	for (double i : v)
	{
		os << i << " ";
	}
	return (os);
}


typedef struct	s_player_data
{
	int wins_count;
	int total_score;
	int num;
}				t_player_data;

ostream& operator << (ostream& os, t_player_data p)
{
	os << "[" << p.total_score << " " << p.wins_count << "] " << pms[p.num - 1];
	return (os);
}

ostream& operator << (ostream& os, vector<t_player_data> v)
{
	for (auto i : v)
	{
		os << i.num << ": " << i << endl;
	}
	return (os);
}

bool operator < (t_player_data l, t_player_data r)
{
	if (l.wins_count > r.wins_count)
	{
		return (true);
	}
	else if (l.wins_count == r.wins_count)
	{
		if (l.total_score > r.total_score)
			return (true);
		else
			return (false);
	}
	return (false);
}

void ft_set_n(vector<double>& v, int n)
{
	int i = 0;
	while (i < n)
	{
		v[i] = 1;
		++i;
	}
}

int main(void)
{
	vector<t_player_data> players(513);
	int i;
	fstream fs;
	fs.open("logs1/logs1.total", fstream::in);

	vector<double> pm;
	int t = 0;
	while (t <= 9)
	{
		pm.clear();
		pm.resize(9);
		ft_set_n(pm, t);
		pms.push_back(pm);
		while (prev_permutation(pm.begin(), pm.end()))
			pms.push_back(pm);
		++t;
	}



	i = 1;
	while (i <= 512)
	{
		if (i == 256)
		{
			fs.close();
			fs.open("logs2/logs2.total", fstream::in);
		}
		int k = 1;
		while (k <= 5)
		{
			string str;
			int p1;
			int p2;
			fs >> str >> str >> str >> p1;
			fs >> str >> str >> str >> p2;
			if (p1 > p2)
				players[i].wins_count++;
			else
				players[i + 1].wins_count++;
			if (p1 == p2)
				players[i].wins_count++;
			players[i].total_score += p1;
			players[i + 1].total_score += p2;
			players[i].num = i;
			players[i + 1].num = i + 1;
			++k;
		}
		i += 2;
	}
	sort(players.begin(), players.end());
	cout << players;
	fs.close();
}