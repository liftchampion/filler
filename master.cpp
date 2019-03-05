/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 12:40:43 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/05 12:40:43 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

vector<string> opponents = {"abanlin", "carli", "champely", "hcao", "grati", "superjeannot"};

typedef struct	s_player_data
{
	int wins_count;
	int total_score;
	int num;
	vector<double> coeffs;
}				t_player_data;

typedef struct	s_match_result
{
	int O_sc;
	int X_sc;
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
	system("gcc -Ofast -I libft/includes objs/*.o libft/libft.a -o ggerardy.filler");
	system("mv ggerardy.filler ./bg/ggerardy.filler");
}

char *ft_make_command(const string& p1, const string& p2, int map)
{
	stringstream ss;
	ss << "cd resources; ./filler_vm -f maps/map0" << map << " -p1 " << p1 <<
			" -p2 " << p2 << " | grep 'fin' > ../bg/momental_res; cd ..";
	string cmd = ss.str();
	return (cmd.data());
}

t_match_result ft_get_match_result()
{
	fstream fs;
	fs.open("bg/momental_res", fstream::out);
	string str;
	t_match_result res;
	fs >> str >> str >> str >> res.O_sc;
	fs >> str >> str >> str >> res.X_sc;
	fc.close();
	return (res);
}

t_player_data ft_check_warrior(const vector<double>& coefficients)
{
	string me = "../bg/ggerardy.filler";
	t_match_result res;
	t_player_data warrior;
	warrior.coeffs = coefficients;
	for (auto opp : opponents)
	{
		opp = "players/" + opp + ".filler";
		for (int i = 0; i < 5; ++i)
		{
			system(ft_make_command(opp, me, 0));
			res = ft_get_match_result();
			warrior.total_score += res.X_sc;
			warrior.wins_count += res.X_sc > res.O_sc;
		}
		for (int i = 0; i < 5; ++i)
		{
			system(ft_make_command(me, opp, 0));
			res = ft_get_match_result();
			warrior.total_score += res.O_sc;
			warrior.wins_count += res.O_sc > res.X_sc;
		}

	}
	cout << "Warrior" <<
}


int main(void)
{

	return (0);
}