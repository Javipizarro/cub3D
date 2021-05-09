/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:56:25 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/09 22:13:42 by jpizarro         ###   ########.fr       */
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



//typedef struct s_img
//{
//	void		*ptr;
//	char		*addr;
//	int			bpp;
//	int			lnlen;
//	int			endian;
//}			t_img;

typedef struct s_controls
{
	char		esc;
	char		u;
	char		d;
	char		l;
	char		r;
	char		tl;
	char		tr;
	char		jp;
	char		sh;
	double		speed;
	double		turn;
}			t_controls;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			dimy;
	int			dimx;
//	int			y_pos;
//	int			x_pos;
	int			bpp;
	int			lnlen;
	int			endian;
}			t_img;

typedef struct s_map
{
	char		**map;
	int			dimy;
	int			sp_num;
}			t_map;

typedef struct s_player
{
	double		posy;
	double		posx;
	double		diry;
	double		dirx;
	char		move[2];
	char		spin;
}			t_player;

typedef struct s_sprite
{
	double		dist;
	int			x;
	int			y;
}			t_sprite;

typedef	struct s_raycast
{
	int			mapy;
	int			mapx;
	double		fov;
	double		camy;
	double		camx;
	int			line;
	double		camdot;
	double		rayy;
	double		rayx;
	double		incy;
	double		incx;
	double		iniy;
	double		inix;
	char		face;
	double		*dist;
	t_sprite	*sps;
	double		rayimp;
	int			lnh;
	int			color;
}			t_raycast;

typedef struct s_set
{
	char		*pathn;
	t_img		n;
	char		*paths;
	t_img		s;
	char		*pathe;
	t_img		e;
	char		*pathw;
	t_img		w;
	char		*pathp;
	t_img		p;
	int			f;
	int			c;
}			t_set;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			winw;
	int			winh;
	char		err;
	t_controls	ctr;
	t_img		img;
	t_map		map;
	t_player	py;
	t_raycast	rc;
	t_set		set;
}			t_mlx;

typedef struct s_mapping
{
	int			dimy;
	int			dimx;
	char		*map;
	char		*buff;
	char		**g_pig;
	char		diri;
	char		dirj;
	int			i;
	int			j;
	char		gnl;
	char		py_in;
	int			loop;
	int			loopi;
	int			loopj;
}			t_mapping;

int		builder(int ac, t_mlx *mlx);
int		bye(t_mlx *mlx);
void	dot_cub_parser(t_mlx *mlx, char *cub_path);
int		free_mapping(t_mapping *map);
int		free_mlx(t_mlx *mlx);
int		free_split(int ret, char **split);
void	fresh_mlx_vars(t_mlx *mlx);
int		key_pressed(int key, t_mlx *mlx);
int		key_released(int key, t_mlx *mlx);
void	map_leaks(t_mlx *mlx, t_mapping *map);
void	mapper(t_mlx *mlx, int fd, char **line, char *gnl);
int		msnprt(int fd, char *msn);
void	paint_line(t_mlx *mlx);
int		parse_map_line(t_mlx *mlx, int fd, char **line, t_mapping *map);
void	pixel_push(t_mlx *mlx, int x, int y);
int		play(t_mlx *mlx);
int		printerror(int err);
int		raycaster(t_mlx *mlx);
int		set_rc_constants(t_mlx *mlx);
int		window_sizer(t_mlx *mlx, char **elem);
int		texturizer(t_mlx *mlx, char **elem);
int		colorizer(t_mlx *mlx, char **elem);

#endif