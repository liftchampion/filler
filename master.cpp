/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 12:40:43 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/10 05:24:28 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <sstream>
#include <tuple>


using namespace std;

#define MATCHES_COUNT 2

int n_matches;

vector<string> opponents = {"mwunsch", "jcorwin", "carli", "lcharvol", "bmiklaz"};
//vector<string> opponents = {"superjeannot", "carli", "mwunsch", "hcao", "grati", "jcorwin"};
//vector<string> opponents = {"carli"};

char	*ft_itoa(int n)
{
	int		nb;
	int		len;
	char	*ret;

	len = 2;
	if (n < 0)
		len++;
	nb = n;
	while (!(nb < 10 && nb > -10))
	{
		len++;
		nb /= 10;
	}
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ret[--len] = '\0';
	nb = (n < 0) ? -1 : 1;
	while (n || len)
	{
		ret[--len] = n % 10 * nb + '0';
		n /= 10;
	}
	if (nb < 0)
		ret[0] = '-';
	return (ret);
}

typedef struct	s_player_data
{
	int wins_count = 0;
	int total_score = 0;
	int game_wins = 0;
	int num = 0;
	vector<double> coeffs;
	map<string, int> results;
}				t_player_data;

ostream& operator << (ostream& os, const map<string, int>& m)
{
	for (auto i : m)
	{
		os << i.first << ": " << i.second << endl;
	}

	return (os);
}

typedef struct	s_match_result
{
	int O_sc = 0;
	int X_sc = 0;
}				t_match_result;

ostream& operator << (ostream& os, const vector<double>& v)
{
	cout << "[";
	for (auto i : v)
	{
		os << " " << i;
	}
	cout << "]";
	return (os);
}

ostream& operator << (ostream& os, const t_player_data& w)
{
	os << "Warrior: " << w.coeffs << " score is " << w.total_score << " win_rate(round) is ";
	os << ((double)w.wins_count / (opponents.size() * 10 * n_matches)) * 100 << "%" << " win_rate(game) is ";
	os << ((double)w.game_wins / (opponents.size() * 2 * n_matches)) * 100 << endl;
	os << w.results << endl;

	return (os);
}

bool operator < (const t_player_data& l, const t_player_data& r)
{
	auto lt = tie(l.game_wins, l.wins_count, l.total_score);
	auto rt = tie(r.game_wins, r.wins_count, r.total_score);
	return (lt > rt);
}

void ft_build_warrior(const vector<double>& coefficients)
{
	fstream fs;
	fs.open("srcs/koeffs.c", fstream::out);
	bool is_first = true;
	fs << "double kfc[] = {";
	for (double i : coefficients)
	{
		if (!is_first)
			fs << ", ";
		is_first = false;
		fs << i;
	}
	fs << "};" << endl;
	fs.close();

	system("rm -f objs/koeffs.o");
	system("gcc -Ofast -c srcs/koeffs.c -o objs/koeffs.o");
	system("gcc -Ofast -lpthread -I libft/includes objs/*.o libft/libft.a -o ggerardy.filler");
	system("mv ggerardy.filler ./bg/ggerardy.filler");
}

char *ft_make_command(const string& p1, const string& p2, int map)
{
	char *cmd = (char*)malloc(300);
	bzero(cmd, 300);

	strlcat(cmd, "cd resources; ./filler_vm -f maps/map0", 300);
	strlcat(cmd, ft_itoa(map), 300);
	strlcat(cmd, " -p1 ", 300);
	strlcat(cmd, p1.data(), 300);
	strlcat(cmd, " -p2 ", 300);
	strlcat(cmd, p2.data(), 300);
	strlcat(cmd, " | grep 'fin' > ../bg/momental_res; cd ..", 300);

	/*stringstream ss;
	ss << "cd resources; ./filler_vm -f maps/map0" << map << " -p1 " << p1 \
		<< " -p2 " << p2 << " | grep 'fin' > ../bg/momental_res; cd ..";
	string cmd = ss.str();
	cmd.shrink_to_fit();
	cout << cmd << endl;
	char *tmp = cmd.data();*/
	//printf("<%s>\n", cmd);
	return (cmd);
}

t_match_result ft_get_match_result()
{
	fstream fs;
	fs.open("bg/momental_res", fstream::in);
	string str;
	t_match_result res;
	fs >> str >> str >> str >> res.O_sc;
	fs >> str >> str >> str >> res.X_sc;
	fs.close();
	return (res);
}

t_player_data ft_check_warrior(const vector<double>& coefficients)
{
	ft_build_warrior(coefficients);
	string me = "../bg/ggerardy.filler";
	t_match_result res;
	t_player_data warrior;
	warrior.coeffs = coefficients;
	n_matches = 1;
	for (int k = 0; k < MATCHES_COUNT; ++k)
	{
		for (auto opp : opponents)
		{
			cout << "playing with " << opp << endl;
			opp = "players/" + opp + ".filler";
			int c = 0;
			for (int i = 0; i < 5; ++i)
			{
				system(ft_make_command(opp, me, 1));
				res = ft_get_match_result();
				warrior.total_score += res.X_sc;
				warrior.wins_count += res.X_sc > res.O_sc;
				warrior.results[opp] += res.X_sc > res.O_sc;
				c += res.X_sc > res.O_sc;
			}
			warrior.game_wins += c >= 3;
			c = 0;
			for (int i = 0; i < 5; ++i)
			{
				system(ft_make_command(me, opp, 1));
				res = ft_get_match_result();
				warrior.total_score += res.O_sc;
				warrior.wins_count += res.O_sc > res.X_sc;
				warrior.results[opp] += res.O_sc > res.X_sc;
				c += res.O_sc > res.X_sc;
			}
			warrior.game_wins += c >= 3;
		}
		cout << warrior;
		n_matches++;
	}
	return (warrior);
}


void ft_gradient_decrease()
{
	vector<double> coefficients(10);
	coefficients = {0, 2, 3, 1, 0, 1, 1, 0, -1, 0};

	fstream fs;
	fs.open("ML_LOG", fstream::out);

	double step = 0.5;
	int i = 0;
	while (i < 10)
	{
		cout << "Step is " << step << endl;
		fs << "Step is " << step << endl;
		t_player_data init = ft_check_warrior(coefficients);
		vector<t_player_data> ws(10);
		int j = 0;
		while (j < 10)
		{
			coefficients[j] += step * (1 - 2 * (j == 8));
			ws[j] = ft_check_warrior(coefficients);
			ws[j].num = j;
			coefficients[j] -= step * (1 - 2 * (j == 8));
			++j;
		}
		sort(ws.begin(), ws.end());
		if (!(ws[0] < init))
		{
			cout << "**********************************************" << endl;
			cout << "               !INIT IS BETTER!               " << endl;
			fs   << "               !INIT IS BETTER!               " << endl;
			cout << "**********************************************" << endl;
			step *= 0.7;
			ws[0] = init;
		}
		cout << "######################## BEST ####################" << endl;
		cout << ws[0];
		fs << ws[0];
		cout << "##################################################" << endl;
		coefficients = ws[0].coeffs;
		++i;
	}
	fs.close();
}


int main(void)
{
	vector<double> c(9);
	c[0] = 1;
	c[1] = 1;
	c[2] = 1;
	c[3] = 1;

	//ft_check_warrior(c);
	ft_gradient_decrease();

	return (0);
}
