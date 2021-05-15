/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 12:30:30 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/15 16:07:33 by jpizarro         ###   ########.fr       */
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

void	paint_sprites(t_mlx *mlx)
{
	int		i;
	double	sp_py_x;
	double	sp_py_y;
	double	det_inv;
	double	sp_py_dir;
	double	sp_py_cam;
	double	sp_horpos;
	int		sp_height;
	int		sp_width;
	int		sp_ver_ini;
	int		sp_ver_end;
	int		sp_hor_ini;
	int		sp_hor_end;


	i = 0;
	while (i < mlx->map.sp_num && mlx->rc.sprites[i].dist)
	{
//	
		sp_py_x = mlx->rc.sprites[i].x + 0.5 - mlx->py.posx;
		sp_py_y = mlx->rc.sprites[i].y + 0.5 - mlx->py.posy;
		
//	Cambiamos el sistema de referencia a los ejes dirección-pantalla
//	Por qué corrige con el inverso del determinante????????????
		det_inv = 1 / (mlx->rc.camx * mlx->py.diry - mlx->rc.camy * mlx->py.dirx);
//		sp_py_dir = (mlx->py.diry * sp_py_x - mlx->py.dirx * sp_py_y) * det_inv;
//		sp_py_cam = (mlx->rc.camx * sp_py_y - mlx->rc.camy *sp_py_x) * det_inv;
		sp_py_cam = (mlx->py.dirx * sp_py_y - mlx->py.diry * sp_py_x) * det_inv;
		sp_py_dir = (mlx->rc.camx * sp_py_y - mlx->rc.camy * sp_py_x) * det_inv;
//		printf("sp_py_x = %f, sp_py_y = %f, sp_py_cam = %f, sp_py_dir = %f\n", sp_py_x, sp_py_y, sp_py_cam, sp_py_dir);
//	Calculamos la posición horizontal en pantalla
		sp_horpos = (1 - sp_py_cam / sp_py_dir) * (mlx->winw - 1) / 2;
//	Calculamos la altura del sprite en pantalla
		sp_height = mlx->winh / sp_py_dir;
//	Dónde comenzar y acabar de pintar el sprite
		sp_ver_ini = (int)((mlx->winh - sp_height) / 2);
		sp_ver_end = (int)((mlx->winh + sp_height) / 2);
//	Ancho del sprite
		sp_width = mlx->set.sp.dimx * sp_height / mlx->set.sp.dimy;
		sp_hor_ini = (int)(sp_horpos - sp_width / 2);
		sp_hor_end = (int)(sp_horpos + sp_width / 2);
//	Pintamos el sprite
		int k;	//	Debería ser i, pero de momento es lo que hay
		int j;
		int	sp_col;
		int	sp_row;
		t_img	*txtr;

		txtr = &mlx->set.sp;
		k = sp_hor_ini * (sp_hor_ini > 0);
		while (k < sp_hor_ini + sp_width && k < mlx->winw)
		{	
			if (mlx->rc.dist[k] < mlx->rc.sprites[i].dist && k++)
				continue;
			j = (mlx->winh > sp_height) * (mlx->winh - sp_height) / 2;
			while (j < (sp_height + mlx->winh) / 2 && j < mlx->winh)
			{
				// En qué columna caigo en la imagen .xpm del sprite
				sp_col = (int)((mlx->set.sp.dimx - 1) * (k - sp_hor_ini) / sp_width);
				// En qué fila caigo en la imagen .xpm del sprite
				sp_row = (int)((mlx->set.sp.dimy - 1) * (j - sp_ver_ini) / sp_height);
//				if (mlx->err)
					if (sp_col < 0 || sp_row < 0 || sp_col >= mlx->set.sp.dimx || sp_row >= mlx->set.sp.dimy)
//					{
//						mlx->err = 0;
						printf("sp_col = %d, sp_row = %d\t", sp_col, sp_row); 
//					}
				mlx->rc.color = *(unsigned*)(txtr->addr + (sp_row * txtr->dimx + sp_col) * txtr->bpp / 8);
			//	mlx->rc.color = 0x444444;
				if (mlx->rc.color)
					pixel_push(mlx, k, j);
				j++;
			}
			k++;
		}
		i++;
	}


}
