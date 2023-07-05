/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katalbi <katalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:34:03 by katalbi           #+#    #+#             */
/*   Updated: 2023/07/05 11:16:15 by katalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../mlx/mlx.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <math.h>

# define HEIGHT 640
# define WIDTH 960
# define TEX_SIZE 128

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 4
# define C 5

typedef struct s_file
{
	char	**split;
	char	*info[6];
	char	**map;
	int		map_w;
	int		map_h;
	int		c_x;
	int		c_y;
	char	c_flag;
}	t_file;

typedef struct s_key
{
	int		w;
	int		a;
	int		s;
	int		d;
}	t_key;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_key	key;
	t_img	img;
	int		**buf;
	int		*texture[4];
	int		ceiling;
	int		floor;
	char	**map;
	int		map_w;
	int		map_h;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	movespeed;
	double	rotspeed;
}	t_game;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texnum;
	int		tex_x;
	int		tex_y;
	int		index_y;
	double	wallx;
	double	step;
	double	texpos;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	double	perpwalldist;
}	t_dda;

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	check_info(t_file *file);
char	*read_file(char *pathname);
void	init_file(t_file *file);
void	check_file(t_file *file, char *path);
int		is_character(char c, int flag);
void	size_map(t_file *file);
void	get_map(t_file *file);
void	check_surround(t_file *file, int x, int y);
void	check_map(t_file *file);
int		rgb_comma_check(char *str);
int		rgb_check(char **split);
int		rgb_atoi(char **split, int *r, int *g, int *b);
int		get_rgb(char *str);
void	print_err(char *str);
int		close_game(t_game *game);
void	background(t_game *game);
void	display(t_game *game);
void	update_game(t_game *game);
int		loop(t_game *game);
char	*get_path_tex(char *str, char *cut);
int		*load_texture(t_game *game, char *path, t_img *img);
void	get_textures(t_game *game, t_file file);
void	init_game(t_game *game);
void	make_game(t_game *game, t_file file);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	move_front(t_game *game);
void	move_back(t_game *game);
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
void	cal_color(t_dda *dda, t_game *game, int x);
void	tex_input(t_dda *dda, t_game *game);
void	hit_check(t_dda *dda, t_game *game);
void	cal_sidedist(t_dda *dda, t_game *game);
void	raycasting(t_game *game);
void	set_dir_plane_n(t_game *game);
void	set_dir_plane_s(t_game *game);
void	set_dir_plane_w(t_game *game);
void	set_dir_plane_e(t_game *game);
int		get_size(char const *s, char c);
char	*get_ptr_child(char const *s, char c, int i);
void	get_ptr(char **ptr, char const *s, char c);
void	free_ptr(char **ptr);
char	**ft_split_remove_empty(char const *s, char c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_free_s1(char *s1, char *s2);
int		check_ext(char *str);
int		**init_buf(void);

#endif