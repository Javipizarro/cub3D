/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 12:30:30 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/15 20:12:00 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Everyting related with the sprites management is here.
*/

#include "../cub3d.h"

/*
**	Stores the data of the deteted sprite on the sprites array, and sorts it
**	among the alrady stored by distance.
**	Then erase the sprite form the map, so it's detected just once while
**	working in a given frame.
*/

void	sprite_to_array(t_mlx *mlx)
{
	float	sprt_dist;
	int		i;
	int		j;

	i = 0;
//	Distancia jugador-sprite (si solo se usa para ordenar los sprites, no hace falta la ra'iz cuadrada de la hipotenusa)
	sprt_dist = hypotf(mlx->py.posy - mlx->rc.mapy
	- 0.5, mlx->py.posx - mlx->rc.mapx - 0.5);
// almacenar sprite en array por orden
	while (sprt_dist < mlx->rc.sprites[i].dist)
		i++;
	j = i;
////////////////
	if (i >= mlx->map.sp_num)
	{
		printf("i = %d	ESTAMOS FUERA DEL RANGO!!!!!!!!!!\n", i);
		bye(mlx);
	}
	////////////
	while (mlx->rc.sprites[j].dist)
		++j;
////////////////
	if (j >= mlx->map.sp_num)
	{
		printf("j = %d	ESTAMOS FUERA DEL RANGO!!!!!!!!!!\n", j);
		bye(mlx);
	}
	////////////
	while (j > i)
	{
		mlx->rc.sprites[j] = mlx->rc.sprites[j - 1];
		j--;
	}
	mlx->rc.sprites[i].dist = sprt_dist;
	mlx->rc.sprites[i].y = mlx->rc.mapy;
	mlx->rc.sprites[i].x = mlx->rc.mapx;
	mlx->map.map[mlx->rc.mapy][mlx->rc.mapx] = '0';
/////////////////
//	int jj = 0;
//	while (jj < mlx->map.sp_num)
//		printf("sprite %d, dist = %f, x = %d, y = %d\n", jj , mlx->rc.sprites[jj].dist, mlx->rc.sprites[jj].y, mlx->rc.sprites[jj++].x);
//	printf("sprites in map = %d\n", mlx->map.sp_num);
//	/////////////
}

/*
**	Return the sprites on the array to the map, and empties the array.
*/

void	return_sprites_to_map(t_mlx *mlx)
{
	int i;
	
	i = 0;
	while (mlx->rc.sprites[i].dist && i < mlx->map.sp_num)
	{
		mlx->map.map[mlx->rc.sprites[i].y][mlx->rc.sprites[i].x] = '2';
		i++;
	}
	ft_bzero((char*)mlx->rc.sprites, sizeof(t_sprite) * mlx->map.sp_num);
/////////////////
//	int jj = 0;
//	while (jj < mlx->map.sp_num)
//		printf("sprite %d, dist = %f, x = %d, y = %d\n", jj, mlx->rc.sprites[jj].dist, mlx->rc.sprites[jj].y, mlx->rc.sprites[jj++].x);
//	printf("sprites in map = %d\nEL ARRAY DEBE ESTAR VACIO!!!!!!!!!!!!!!!!!\n", mlx->map.sp_num);
//	/////////////
}

/*
**	Changes the reference base x and y to the cam and dir.
**	Also dimensions and situates the sprites in the window.
*/

void	change_base(t_paint_sprites *psp, t_mlx *mlx, int i)
{
	psp->sp_py_dx = mlx->rc.sprites[i].x + 0.5 - mlx->py.posx;
	psp->sp_py_dy = mlx->rc.sprites[i].y + 0.5 - mlx->py.posy;
	psp->det_inv = 1 / (mlx->rc.camx * mlx->py.diry
	- mlx->rc.camy * mlx->py.dirx);
	psp->sp_py_cam = (mlx->py.dirx * psp->sp_py_dy
	- mlx->py.diry * psp->sp_py_dx)	* psp->det_inv;
	psp->sp_py_dir = (mlx->rc.camx * psp->sp_py_dy
	- mlx->rc.camy * psp->sp_py_dx)	* psp->det_inv;
	psp->sp_dimy = mlx->winh / psp->sp_py_dir;
	psp->sp_dimx = mlx->set.sp.dimx * psp->sp_dimy / mlx->set.sp.dimy;
	psp->sp_inix = (((int)((1 - psp->sp_py_cam / psp->sp_py_dir)
	* (mlx->winw - 1)) - psp->sp_dimx) / 2);
}

/*
**	Calculates what parts of the current spray are hidden,
**	and paint the rest.
*/

void	paint_this_sprite(t_mlx *mlx, t_paint_sprites *psp)
{
	int i;
	int j;
	i = psp->sp_inix * (psp->sp_inix > 0);
	while (i < psp->sp_inix + psp->sp_dimx && i < mlx->winw)
	{	
		if (mlx->rc.dist[i] < psp->sp_py_dir && i++)
			continue;
		j = (mlx->winh > psp->sp_dimy) * (mlx->winh - psp->sp_dimy) / 2;
		while (j < (psp->sp_dimy + mlx->winh) / 2 && j < mlx->winh)
		{
			psp->sp_col = (int)((mlx->set.sp.dimx - 1)
			* (i - psp->sp_inix) / psp->sp_dimx);
			psp->sp_row = (int)((mlx->set.sp.dimy - 1)
			* (j - (mlx->winh - psp->sp_dimy) / 2) / psp->sp_dimy);
			mlx->rc.color = *(unsigned*)(mlx->set.sp.addr + (psp->sp_row
			* mlx->set.sp.dimx + psp->sp_col) * mlx->set.sp.bpp / 8);
			if (mlx->rc.color)
				pixel_push(mlx, i, j);
			j++;
		}
		i++;
	}
}

/*
**	Manages the proccess of painting all the sprays that are on screen.
*/

void	paint_sprites(t_mlx *mlx)
{
	t_paint_sprites	psp;
	int		i;

	i = 0;
	while (i < mlx->map.sp_num && mlx->rc.sprites[i].dist)
	{
		change_base(&psp, mlx, i);
		paint_this_sprite(mlx, &psp);
		i++;
	}
}
