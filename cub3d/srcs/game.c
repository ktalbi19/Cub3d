/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:33:26 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 11:13:55 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*get_path_tex(char *str, char *cut)
{
	while (*cut && *str)
	{
		if (*cut != *str)
			return (NULL);
		++cut;
		++str;
	}
	while (*str == ' ')
		++str;
	return (str);
}

int	*load_texture(t_game *game, char *path, t_img *img)
{
	int	*res;
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(game->mlx,
			path, &img->width, &img->height);
	if (!img->img || img->width != TEX_SIZE || img->height != TEX_SIZE)
		print_err("Error\ninvalid texture");
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	res = (int *)malloc(sizeof(int) * (TEX_SIZE * TEX_SIZE));
	if (!res)
		print_err("Error\nmalloc error");
	y = -1;
	while (++y < TEX_SIZE)
	{
		x = -1;
		while (++x < TEX_SIZE)
			res[y * TEX_SIZE + x] = img->data[x * TEX_SIZE + y];
	}
	mlx_destroy_image(game->mlx, img->img);
	return (res);
}

void	get_textures(t_game *game, t_file file)
{
	t_img	tmp;
	char	*path;

	path = get_path_tex(file.info[NO], "NO");
	game->texture[NO] = load_texture(game, path, &tmp);
	path = get_path_tex(file.info[SO], "SO");
	game->texture[SO] = load_texture(game, path, &tmp);
	path = get_path_tex(file.info[WE], "WE");
	game->texture[WE] = load_texture(game, path, &tmp);
	path = get_path_tex(file.info[EA], "EA");
	game->texture[EA] = load_texture(game, path, &tmp);
	path = get_path_tex(file.info[C], "C");
	game->ceiling = get_rgb(path);
	path = get_path_tex(file.info[F], "F");
	game->floor = get_rgb(path);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->key.w = 0;
	game->key.s = 0;
	game->key.a = 0;
	game->key.d = 0;
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, \
										&game->img.size_l, &game->img.endian);
	game->buf = init_buf();
	game->movespeed = 0.04;
	game->rotspeed = 0.04;
}

void	make_game(t_game *game, t_file file)
{
	init_game(game);
	get_textures(game, file);
	game->map = file.map;
	game->map_w = file.map_w;
	game->map_h = file.map_h;
	game->pos_x = file.c_x + 0.5;
	game->pos_y = file.c_y + 0.5;
	if (file.c_flag == 'N')
		set_dir_plane_n(game);
	if (file.c_flag == 'S')
		set_dir_plane_s(game);
	if (file.c_flag == 'W')
		set_dir_plane_w(game);
	if (file.c_flag == 'E')
		set_dir_plane_e(game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
}
