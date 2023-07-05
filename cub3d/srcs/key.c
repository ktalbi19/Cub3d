/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:10:33 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 11:13:58 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		game->key.w = 1;
	else if (keycode == KEY_A)
		game->key.a = 1;
	else if (keycode == KEY_S)
		game->key.s = 1;
	else if (keycode == KEY_D)
		game->key.d = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key.w = 0;
	else if (keycode == KEY_A)
		game->key.a = 0;
	else if (keycode == KEY_S)
		game->key.s = 0;
	else if (keycode == KEY_D)
		game->key.d = 0;
	return (0);
}
