/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 04:23:37 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/04 06:05:11 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

/*double ft_generate_double(double low, double high)
{
	int low_i = (int)low;
	int high_i = (int)high;
	int low_p = (low - (int)low) * 1000;
	int high_p = (high - (int)high) * 1000;
	double i_p;
	double p_p;
}*/

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

ostream& operator << (ostream& os, vector<double> v)
{
	bool is_first = true;
	os << "double kfc[] = {";
	for (double i : v)
	{
		if (!is_first)
			os << ", ";
		is_first = false;
		os << i;
	}
	os << "};" << endl;
	return (os);
}

ostream& operator << (ostream& os, vector<vector<double> > v)
{
	for (auto i : v)
		os << i;
	return (os);
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
	FILE* fil;
	int i;
	int j;

	vector<vector<double> > pms;
	vector<double> pm;

	i = 0;
	while (i <= 9)
	{
		pm.clear();
		pm.resize(9);
		ft_set_n(pm, i);
		pms.push_back(pm);
		while (prev_permutation(pm.begin(), pm.end()))
			pms.push_back(pm);
		++i;
	}

	i = 1;
	for (auto k : pms)
	{
		fstream fs;
		fs.open("srcs/koeffs.c", fstream::out);
		fs << k;
		fs.close();

		char *str = (char*)malloc(100);
		bzero(str, 100);
		strlcat(str, "mv ggerardy.filler ./battleground/ggerardy.filler.", 100);
		strlcat(str, ft_itoa(i), 100);

		system("rm -f objs/koeffs.o");
		system("gcc -c srcs/koeffs.c -o objs/koeffs.o");
		system("gcc -I libft/includes objs/*.o libft/libft.a -o ggerardy.filler");
		system(str);
		++i;
	}

	return (0);
}
