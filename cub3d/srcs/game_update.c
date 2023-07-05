/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:23:03 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 11:13:45 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	background(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				game->buf[y][x] = game->ceiling;
			else
				game->buf[y][x] = game->floor;
		}
	}
}

void	display(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			game->img.data[y * WIDTH + x] = game->buf[y][x];
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	update_game(t_game *game)
{
	if (game->key.w)
		move_front(game);
	if (game->key.a)
		rotate_left(game);
	if (game->key.s)
		move_back(game);
	if (game->key.d)
		rotate_right(game);
}

int	loop(t_game *game)
{
	background(game);
	raycasting(game);
	display(game);
	update_game(game);
	return (0);
}
