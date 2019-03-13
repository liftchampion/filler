/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle_master.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 07:17:34 by ggerardy          #+#    #+#             */
/*   Updated: 2019/03/04 07:17:34 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

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

void ft_exec_cmd(int i, int j, int k)
{
	char fl[200];
	bzero(fl, 200);
	strlcat(fl, ft_itoa(i), 200);
	strlcat(fl, ".", 200);
	strlcat(fl, ft_itoa(j), 200);
	strlcat(fl, ".", 200);
	strlcat(fl, ft_itoa(k), 200);
	char cmd[300];
	bzero(cmd, 300);
	strlcat(cmd, "cd resources; ./filler_vm -f maps/map00 -p1 ../battleground/ggerardy.filler.", 300);
	strlcat(cmd, ft_itoa(i), 300);
	strlcat(cmd, " -p2 ../battleground/ggerardy.filler.", 300);
	strlcat(cmd, ft_itoa(j), 300);
	strlcat(cmd, " | grep 'fin'", 300);
	strlcat(cmd, " > ../logs1/", 300);
	strlcat(cmd, fl, 300);
	cout << cmd << endl;
	system(cmd);
}

int main(void)
{
	int i;
	int j;
	int k;

	i = 1;
	while (i < 256)
	{
		int k = 1;
		while (k <= 5)
		{
			ft_exec_cmd(i, i + 1, k);
			++k;
		}
		i += 2;
	}
}