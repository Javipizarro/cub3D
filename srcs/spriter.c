/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 12:30:30 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 11:25:59 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Everyting related with the sprites management is here.
*/

#include "../cub3d.h"

/*
**	Given the sprite's positon and dimensions, prints the visible
**	portion of it.
*/

void	paint_sprite(t_mlx *mlx, t_paint_sprite_tools *pst, int i)
{
	int x;
	int y;

	x = pst->ini_paint_x;
	if (!(pst->endx < 0))
	while (x < pst->endx)
	{	
		if (mlx->rc.wall_dist[x] < mlx->sp.list[i].dir && x++)
			continue;
		pst->sp_col = (mlx->set.s1.dimx - 1)
		* (x - pst->inix) / pst->dimx;
		y = pst->ini_paint_y;
		while (y < pst->endy)
		{
			pst->sp_row = ((mlx->set.s1.dimy - 1)
			* (y - pst->iniy) / pst->dimy);
			mlx->rc.color = *(unsigned*)(mlx->set.s1.addr + (pst->sp_row
			* mlx->set.s1.dimx + pst->sp_col) * 4);
			if (mlx->rc.color)
				pixel_push(mlx, x, y);
			y++;
		}
		x++;
	}
}

/*
**	Situates and dimensions the sprites on the window.
*/

void	place_sprite(t_mlx *mlx, t_paint_sprite_tools *pst, int i)
{
	pst->dimy = mlx->winh / mlx->sp.list[i].dir;
	pst->iniy = (mlx->winh - pst->dimy) / 2;
	pst->ini_paint_y = pst->iniy * (pst->iniy > 0);
	pst->endy = pst->iniy + pst->dimy;
	pst->endy = pst->endy * (pst->endy <= mlx->winh) + mlx->winh * (pst->endy > mlx->winh);
	pst->dimx = mlx->set.s1.dimx * pst->dimy / mlx->set.s1.dimy;
	pst->posx = (1 - mlx->sp.list[i].cam / mlx->sp.list[i].dir) * (mlx->winw - 1) / 2; 
	pst->inix = (pst->posx - pst->dimx / 2);
	pst->endx = pst->inix + pst->dimx; 
	pst->ini_paint_x = pst->inix * (pst->inix > 0);
	pst->endx = pst->endx * (pst->endx <= mlx->winw) + mlx->winw * (pst->endx > mlx->winw);
	if (mlx->print_var)
	{
		printf("dy %f, dx %f, inix %d, inipaintx%d, endx %d, iniy %d, inipainty %d, endy%d\n", pst->dx, pst->dy, pst->inix, pst->ini_paint_x, pst->endx, pst->iniy, pst->ini_paint_y, pst->endy);
		printf("\n");
	}
}

/*
**	Sorts the sprites' indexes in order by ascending distance to the player.
*/

void	sort_sprite(t_mlx *mlx, int	i)
{
	int j;
	int k;

	j = 0;
	while ((mlx->sp.order[j] >= 0)
	&& (mlx->sp.list[i].dist < mlx->sp.list[mlx->sp.order[j]].dist))
		j++;
	k = j;
	while (mlx->sp.order[j] >= 0)
		j++;
	mlx->sp.order[++j] = -1;
	while (--j > k)
		mlx->sp.order[j] = mlx->sp.order[j - 1];
	mlx->sp.order[k] = i;
}

/*
**	Changes the base to work from the player's position.
*/

int	base_change_to_cam_dir(t_mlx *mlx, t_paint_sprite_tools *pst, int i)
{
	pst->dy = mlx->sp.list[i].y + 0.5 - mlx->py.posy;
	pst->dx = mlx->sp.list[i].x + 0.5 - mlx->py.posx;
	mlx->sp.list[i].dist = hypotf(pst->dy, pst->dx);
	if (mlx->sp.list[i].dist > mlx->rc.max_dist)
		return (2);
	mlx->sp.list[i].dir = (mlx->rc.camx * pst->dy
	- mlx->rc.camy * pst->dx) / pst->det;
	if (mlx->sp.list[i].dir < 0)
		return (2);
	mlx->sp.list[i].cam = (mlx->py.dirx * pst->dy
	- mlx->py.diry * pst->dx) / pst->det;
	return (0);
}

/*
**	Manages the proccess of painting all the sprays that are on screen.
*/

void	spriter(t_mlx *mlx)
{
	t_paint_sprite_tools	pst;
	int	i;
	int	j;

	i = -1;
	mlx->sp.order[0] = -1;
	pst.det = mlx->rc.camx * mlx->py.diry - mlx->rc.camy * mlx->py.dirx;
	while (++i < mlx->sp.num)
	{
		if (base_change_to_cam_dir(mlx, &pst, i))
			continue;
		sort_sprite(mlx, i);
	}
	j = -1;
	while (mlx->sp.order[++j] >= 0)
	{
		i = mlx->sp.order[j];
		place_sprite(mlx, &pst, i);
		paint_sprite(mlx, &pst, i);
	}
}
