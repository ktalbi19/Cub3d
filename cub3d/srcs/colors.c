/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:51:17 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 10:58:03 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	rgb_comma_check(char *str)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			++cnt;
		++i;
	}
	if (cnt == 2)
		return (0);
	return (1);
}

int	rgb_check(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (1);
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	rgb_atoi(char **split, int *r, int *g, int *b)
{
	int	res;
	int	cnt;
	int	i;

	cnt = 0;
	res = 0;
	while (split[cnt])
	{
		i = -1;
		res = 0;
		while (split[cnt][++i])
		{
			res = 10 * res + (split[cnt][i] - '0');
			if (res < 0 || res > 255)
				return (1);
			if (!split[cnt][i + 1] && cnt == 0)
				*r = res;
			else if (!split[cnt][i + 1] && cnt == 1)
				*g = res;
			else if (!split[cnt][i + 1] && cnt == 2)
				*b = res;
		}
		cnt++;
	}
	return (0);
}

int	get_rgb(char *str)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	int		i;

	if (rgb_comma_check(str))
		print_err("Error\ncannot load RGB color");
	split = ft_split_remove_empty(str, ',');
	if (!split)
		print_err("Error\nsplit error");
	if (rgb_check(split))
		print_err("Error\ncannot load RGB color");
	if (rgb_atoi(split, &r, &g, &b))
		print_err("Error\ncannot load RGB color");
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return ((r * 256 * 256) + (g * 256) + b);
}
