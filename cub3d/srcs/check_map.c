/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:25:03 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/04 11:03:22 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	is_character(char c, int flag)
{
	if (flag == 1 && !(c == '1' || c == '0' || c == ' '))
		return (1);
	if (flag == 2 && (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
		return (1);
	return (0);
}

static void	size_map(t_file *file)
{
	int	i;
	int	j;

	i = 6;
	if (!file->split[i])
		print_err("Error\ninvalid map");
	while (file->split[i])
	{
		j = 0;
		while (file->split[i][j])
			++j;
		if (file->map_w < j)
			file->map_w = j;
		++file->map_h;
		++i;
	}
}

static void	get_map(t_file *file)
{
	int	i;
	int	j;

	file->map = (char **)malloc(sizeof(char *) * (file->map_h + 1));
	if (!file->map)
		print_err("Error\nmalloc error");
	i = 0;
	while (i < file->map_h)
	{
		file->map[i] = (char *)ft_calloc(file->map_w + 1, sizeof(char));
		if (!file->map[i])
			print_err("Error\nmalloc error");
		j = 0;
		while (file->split[i + 6][j])
		{
			file->map[i][j] = file->split[i + 6][j];
			j++;
		}
		while (j < file->map_w)
			file->map[i][j++] = ' ';
		file->map[i][j] = 0;
		++i;
	}
	file->map[i] = 0;
}

static void	check_surround(t_file *file, int x, int y)
{
	if ((x == 0 || x == file->map_w - 1 || y == 0 || y == file->map_h - 1) \
		&& !(file->map[y][x] == '1' || file->map[y][x] == ' '))
		print_err("Error\ninvalid map");
	if (file->map[y][x] == ' ')
	{
		if (x != 0 && !(file->map[y][x - 1] == '1' \
					|| file->map[y][x - 1] == ' '))
			print_err("Error\ninvalid map");
		if (y != 0 && !(file->map[y - 1][x] == '1' \
					|| file->map[y - 1][x] == ' '))
			print_err("Error\ninvalid map");
		if (x != file->map_w - 1 && !(file->map[y][x + 1] == '1' \
					|| file->map[y][x + 1] == ' '))
			print_err("Error\ninvalid map");
		if (y != file->map_h - 1 && !(file->map[y + 1][x] == '1' \
					|| file->map[y + 1][x] == ' '))
			print_err("Error\ninvalid map");
	}
}

void	check_map(t_file *file)
{
	int	x;
	int	y;

	size_map(file);
	get_map(file);
	y = -1;
	while (file->map[++y])
	{
		x = -1;
		while (file->map[y][++x])
		{
			if (is_character(file->map[y][x], 1))
			{
				if (!file->c_flag && is_character(file->map[y][x], 2))
				{
					file->c_x = x;
					file->c_y = y;
					file->c_flag = file->map[y][x];
				}
				else
					print_err("Error\ninvalid map");
			}
			check_surround(file, x, y);
		}
	}
}