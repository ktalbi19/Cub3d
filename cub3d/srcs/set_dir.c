/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:57:50 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/04 11:58:05 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	set_dir_plane_n(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = -1;
	game->plane_x = 0.66;
	game->plane_y = 0;
}

void	set_dir_plane_s(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = 1;
	game->plane_x = -0.66;
	game->plane_y = 0;
}

void	set_dir_plane_w(t_game *game)
{
	game->dir_x = -1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = -0.66;
}

void	set_dir_plane_e(t_game *game)
{
	game->dir_x = 1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0.66;
}
