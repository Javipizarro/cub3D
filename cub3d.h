/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:56:25 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 12:54:29 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
//# include <stdlib.h>
//# include <unistd.h>
# include <fcntl.h>
//# include "libs/color/color.h"
# include "libs/libft/libft.h"
//# include "libs/mathft/mathft.h"
# include "libs/get_next_line/get_next_line.h"
# include <math.h>

typedef struct s_controls
{
	char			esc;
	char			moveforward;
	char			movebackward;
	char			moveleft;
	char			moveright;
	char			turnleft;
	char			turnright;
//	char			jump;
//	char			sh;
	double			speed;
	double			turn;
}			t_controls;

typedef struct s_player
{
	double			posy;
	double			posx;
	double			diry;
	double			dirx;
	char			moveforward;
	char			movebackward;
	char			advance;
	char			moveleft;
	char			moveright;
	char			sidemove;
	char			turnleft;
	char			turnright;
	char			turn;
}			t_player;

typedef struct s_img
{
	void			*ptr;
	char			*addr;
	int				dimy;
	int				dimx;
//	int				y_pos;
//	int				x_pos;
	int				bpp;
	int				lnlen;
	int				endian;
}			t_img;

typedef struct s_map
{
	char			**map;
	int				dimy;
}			t_map;

typedef struct s_one_sprite
{
	int				x;
	int				y;
	double			cam;
	double			dir;
	double			dist;
}			t_one_sprite;

typedef struct s_sprites
{
	int				num;
	t_one_sprite	*list;
	int				*order;
	
}			t_sprites;

typedef struct s_paint_sprite_tools
{
	double			dy;
	double			dx;
	double			det;
	int				dimx;
	int				dimy;
	int				inix;
	int				posx;
	int				ini_paint_x;
	int				endx;
	int				iniy;
	int				endy;
	int				ini_paint_y;
	int				sp_col;
	int				sp_row;
}			t_paint_sprite_tools;

/////////
//typedef struct s_paint_sprites
//{
//	double			sp_py_dx;
//	double			sp_py_dy;
//	double			det_inv;
//	double			sp_py_dir;
//	double			sp_py_cam;
//}			t_paint_sprites;
////////////

typedef	struct s_raycast
{
	int				mapy;
	int				mapx;
	double			fov;
	double			camy;
	double			camx;
	int				line;
	double			camdot;
	double			rayy;
	double			rayx;
	double			incy;
	double			incx;
	double			iniy;
	double			inix;
	char			face;
	double			*wall_dist;
	double			max_dist;
	double			rayimp;
	int				lnh;
	int				color;
}			t_raycast;

typedef struct s_set
{
	char			*pathn;
	t_img			n;
	char			*paths;
	t_img			s;
	char			*pathe;
	t_img			e;
	char			*pathw;
	t_img			w;
	char			*paths1;
	t_img			s1;
	int				f;
	int				c;
}			t_set;

typedef struct s_mlx
{
///////
	char	print_var;
	///////////
	void			*mlx;
	void			*win;
	int				winw;
	int				winh;
	char			err;
	char			argc;
	t_controls		ctr;
	t_img			img;
	t_map			map;
	t_player		py;
	t_raycast		rc;
	t_set			set;
	t_sprites		sp;
}			t_mlx;

typedef struct s_mapping
{
	unsigned int	dimy;
	unsigned int	dimx;
	char			*map;
	char			*buff;
	char			**g_pig;
	char			diri;
	char			dirj;
	unsigned int	i;
	unsigned int	j;
	char			gnl;
	char			py_in;
	int				loop;
	int				loopi;
	int				loopj;
}			t_mapping;

int		another_line(t_mapping *map, int fd, char **line);
int		arenum(char **elem, char k);
int		game_over(t_mlx *mlx);
int		colorizer(t_mlx *mlx, char place, char **elem);
void	dot_cub_parser(t_mlx *mlx, char *cub_path);
int		free_mapping(t_mapping *map);
int		free_mlx(t_mlx *mlx);
int		free_split(int ret, char **split);
void	fresh_mlx_vars(t_mlx *mlx);
void	guinea_pig_map(t_mlx *mlx, t_mapping *map);
void	set_player(t_mlx *mlx);
void	bmp_of_game_ini(t_mlx *mlx);
int		key_pressed(int key, t_mlx *mlx);
int		key_released(int key, t_mlx *mlx);
void	mapper(t_mlx *mlx, int fd, char **line, char *gnl);
int		msnprt(int fd, char *msn);
void	paint_line(t_mlx *mlx);
int		parse_map_line(t_mlx *mlx, int fd, char **line, t_mapping *map);
void	pixel_push(t_mlx *mlx, int x, int y);
int		play(t_mlx *mlx);
int		player_set(t_mlx *mlx, t_mapping *map, char dir, char **line);
int		printerror(int err);
void	raycaster(t_mlx *mlx);
void	return_sprites_to_map(t_mlx *mlx);
void	set_control(t_mlx *mlx);
int		set_set(t_mlx *mlx);
int		set_rc_constants(t_mlx *mlx);
void	spriter(t_mlx *mlx);
int		mlx_start_and_set_up(t_mlx *mlx);
void	game_start(t_mlx *mlx);
int		texturizer(t_mlx *mlx, char *line);
int		window_sizer(t_mlx *mlx, char **elem);
void	write_bmp_header(t_mlx *mlx, int fd);
void	write_dib_header(t_mlx *mlx, int fd);
void	write_pixels_to_bmp(t_mlx *mlx, int fd);

int	prepare_sprites(t_mlx *mlx);
//void	sprite_to_array(t_mlx *mlx);


#endif