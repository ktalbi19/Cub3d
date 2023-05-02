/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:44:57 by katalbi           #+#    #+#             */
/*   Updated: 2023/05/02 11:29:47 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx,
			1920,
			1080,
			"cub3d");
	//mlx_hook(game->window, 17, 0, end_program, game);
	//open_images(game);
}

int	start(t_game *game, int ac, char **av)
{
	(void)ac;
	(void)av;
	// check the map and create a map we can work in
	game_init(game);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!start(&game, ac, av))
		return (0);
	mlx_loop(game.mlx);
}