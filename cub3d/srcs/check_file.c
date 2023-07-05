/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:28:28 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 11:13:11 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_info(t_file *file)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (file->split[i] == NULL)
			print_err("Error\ninvalid file");
		if (ft_strncmp(file->split[i], "NO ", 3) == 0)
			file->info[NO] = file->split[i];
		else if (ft_strncmp(file->split[i], "SO ", 3) == 0)
			file->info[SO] = file->split[i];
		else if (ft_strncmp(file->split[i], "WE ", 3) == 0)
			file->info[WE] = file->split[i];
		else if (ft_strncmp(file->split[i], "EA ", 3) == 0)
			file->info[EA] = file->split[i];
		else if (ft_strncmp(file->split[i], "F ", 2) == 0)
			file->info[F] = file->split[i];
		else if (ft_strncmp(file->split[i], "C ", 2) == 0)
			file->info[C] = file->split[i];
	}
	while (--i >= 0)
	{
		if (!file->info[i])
			print_err("Error\ninvalid file");
	}
}

char	*read_file(char *pathname)
{
	char	*res;
	char	*buf;
	int		fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		print_err("Error\nFailed to open file");
	res = (char *)malloc(sizeof(char));
	buf = (char *)malloc(sizeof(char) * 2);
	if (!res || !buf)
		print_err("Error\nmalloc error");
	res[0] = 0;
	while (read(fd, buf, 1))
	{
		buf[1] = 0;
		res = ft_strjoin_free_s1(res, buf);
		if (!res)
			print_err("Error\nstrjoin error");
	}
	free(buf);
	close(fd);
	return (res);
}

void	init_file(t_file *file)
{
	int	i;

	file->split = NULL;
	i = 0;
	while (i < 6)
		file->info[i++] = NULL;
	file->map = NULL;
	file->map_w = 0;
	file->map_h = 0;
	file->c_flag = 0;
}

void	check_file(t_file *file, char *path)
{
	char	*str;

	init_file(file);
	str = read_file(path);
	file->split = ft_split_remove_empty(str, '\n');
	free(str);
	if (!file->split)
		print_err("Error\nsplit error");
	check_info(file);
	check_map(file);
	if (!file->c_flag)
		print_err("Error\ninvalid map");
}
