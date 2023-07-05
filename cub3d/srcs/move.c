/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:30:18 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 10:15:11 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	move_front(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->pos_x + (game->dir_x * game->movespeed);
	move_y = game->pos_y + (game->dir_y * game->movespeed);
	if (game->map[(int)move_y][(int)game->pos_x] != '1')
		game->pos_y = move_y;
	if (game->map[(int)game->pos_y][(int)move_x] != '1')
		game->pos_x = move_x;
}

void	move_back(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = game->pos_x - (game->dir_x * game->movespeed);
	move_y = game->pos_y - (game->dir_y * game->movespeed);
	if (game->map[(int)move_y][(int)game->pos_x] != '1')
		game->pos_y = move_y;
	if (game->map[(int)game->pos_y][(int)move_x] != '1')
		game->pos_x = move_x;
}

void	rotate_right(t_game *game)
{
	double	x;
	double	y;
	double	p_x;
	double	p_y;

	x = game->dir_x;
	y = game->dir_y;
	p_x = game->plane_x;
	p_y = game->plane_y;
	game->dir_x = x * cos(game->rotspeed) - y * sin(game->rotspeed);
	game->dir_y = x * sin(game->rotspeed) + y * cos(game->rotspeed);
	game->plane_x = p_x * cos(game->rotspeed) - p_y * sin(game->rotspeed);
	game->plane_y = p_x * sin(game->rotspeed) + p_y * cos(game->rotspeed);
}
void	rotate_left(t_game *game)
{
	double	x;
	double	y;
	double	p_x;
	double	p_y;

	x = game->dir_x;
	y = game->dir_y;
	p_x = game->plane_x;
	p_y = game->plane_y;
	game->dir_x = x * cos(-(game->rotspeed)) - y * sin(-(game->rotspeed));
	game->dir_y = x * sin(-(game->rotspeed)) + y * cos(-(game->rotspeed));
	game->plane_x = p_x * cos(-(game->rotspeed)) - p_y * sin(-(game->rotspeed));
	game->plane_y = p_x * sin(-(game->rotspeed)) + p_y * cos(-(game->rotspeed));
}
