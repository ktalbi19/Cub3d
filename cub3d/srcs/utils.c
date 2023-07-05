/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:25:13 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 10:22:22 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int check_ext(char *str)
{
	if (ft_strlen(str) < 4)
		return (0);
	while (*str)
		++str;
	str -= 4;
	if (ft_strncmp(str, ".cub", 4) == 0)
		return (1);
	return (0);
}

int	**init_buf(void)
{
	int	**res;
	int	*tmp;
	int	i;

	res = (int **)malloc(sizeof(int *) * HEIGHT);
	if (!res)
		print_err("Error\nmalloc error");
	i = 0;
	while (i < HEIGHT)
	{
		tmp = (int *)ft_calloc(WIDTH, sizeof(int));
		if (!tmp)
			print_err("Error\nmalloc error");
		res[i] = tmp;
		++i;
	}
	return (res);
}
