/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:56:25 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/19 12:53:08 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
//# include "libs/color/color.h"
# include "libs/libft/libft.h"
//# include "libs/mathft/mathft.h"
# include "libs/get_next_line/get_next_line.h"
# include <math.h>

typedef struct s_img
{
	void		*ptr;
//	char		*path;
	char		*addr;
	int			dimy;
	int			dimx;
//	int			y_pos;
//	int			x_pos;
	int			bpp;
	int			lnlen;
	int			endian;
}			t_img;


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

typedef struct s_player
{
	double		posy;
	double		posx;
	double		diry;
	double		dirx;
	char		move[2];
	char		spin;
}			t_player;

typedef	struct s_raycast
{
//	int			**map;
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
	double		dist;
	double		rayimp;
	int			lnh;
	int			color;
}			t_raycast;

typedef struct s_set
{
	t_img		n;
	t_img		s;
	t_img		e;
	t_img		w;
	t_img		s1;
}			t_set;

//typedef struct s_map
//{
////	int			dimy;
////	int			dimx;
////	int			**map;
//	void		*txn;
//	void		*txs;
//	void		*txe;
//	void		*txw;
//	void		*spr;
//}			t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			winw;
	int			winh;
	t_img		img;
	t_raycast	rc;
	t_controls	ctr;
	t_player	py;
	t_set		set;
}			t_mlx;

int		bye(t_mlx *mlx);
//int		key_down(int key, t_mlx *mlx);
int		key_pressed(int key, t_mlx *mlx);
int		key_released(int key, t_mlx *mlx);
void	paint_line(t_mlx *mlx);
void	pixel_push(t_mlx *mlx, int x, int y);
int		play(t_mlx *mlx);
int		raycaster(t_mlx *mlx);
int		button_on(t_mlx *mlx);

#endif