/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:39:06 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 11:14:01 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main(int ac, char **av)
{
	t_file	file;
	t_game	game;

	if (ac != 2 || !check_ext(av[1]))
		print_err("Arg error\n");
	check_file(&file, av[1]);
	make_game(&game, file);
	mlx_hook(game.win, 17, 0, &close_game, &game);
	mlx_hook(game.win, 2, 0, &key_press, &game);
	mlx_hook(game.win, 3, 0, &key_release, &game);
	mlx_loop_hook(game.mlx, &loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
