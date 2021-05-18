/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:02:12 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 18:37:19 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here we take the situation of the player in the map, and make visual
**	interactions with the environment.
*/

#include "../cub3d.h"

/*
**	Sets the raycasting constants.
*/

int	set_rc_constants(t_mlx *mlx)
{
	mlx->rc.fov = 0.66;
	mlx->rc.wall_dist = malloc(sizeof(double) * mlx->winw);
	if (!(mlx->rc.wall_dist))
		return (msnprt(2, "mlx->rc.wall_dist malloc went wrong"));
	return (0);
}

/*
**	These two calculates what is related to the ray impact with the wall.
**	Such as distance, orientation of the face of impact
*/

void	ray_impact_part_one(t_mlx *mlx)
{
	mlx->rc.incy = 1 / fabs(mlx->rc.rayy);
	mlx->rc.incx = 1 / fabs(mlx->rc.rayx);
	mlx->rc.iniy = fabs((mlx->py.posy - mlx->rc.mapy)
			- (mlx->rc.rayy > 0)) * mlx->rc.incy;
	mlx->rc.inix = fabs((mlx->py.posx - mlx->rc.mapx)
			- (mlx->rc.rayx > 0)) * mlx->rc.incx;
	while (mlx->map.map[mlx->rc.mapy][mlx->rc.mapx] != '1')
	{
		if (mlx->rc.iniy < mlx->rc.inix)
		{
			mlx->rc.mapy += (mlx->rc.rayy >= 0) - (mlx->rc.rayy < 0);
			mlx->rc.iniy += mlx->rc.incy;
			mlx->rc.face = 'h';
		}
		else
		{
			mlx->rc.mapx += (mlx->rc.rayx >= 0) - (mlx->rc.rayx < 0);
			mlx->rc.inix += mlx->rc.incx;
			mlx->rc.face = 'v';
		}
	}
}

void	ray_impact_part_two(t_mlx *mlx)
{
	if (mlx->rc.face == 'h')
	{
		mlx->rc.face = 'n' * (mlx->rc.rayy >= 0) + 's' * (mlx->rc.rayy < 0);
		mlx->rc.wall_dist[mlx->rc.line] = fabs((mlx->py.posy - mlx->rc.mapy
					- (mlx->rc.rayy < 0)) / mlx->rc.rayy);
		mlx->rc.rayimp = fabs((mlx->rc.rayy > 0) - (mlx->py.posx + mlx->rc.rayx
					* mlx->rc.wall_dist[mlx->rc.line] - mlx->rc.mapx));
	}
	else
	{
		mlx->rc.face = 'w' * (mlx->rc.rayx >= 0) + 'e' * (mlx->rc.rayx < 0);
		mlx->rc.wall_dist[mlx->rc.line] = fabs((mlx->py.posx - mlx->rc.mapx
					- (mlx->rc.rayx < 0)) / mlx->rc.rayx);
		mlx->rc.rayimp = fabs((mlx->rc.rayx < 0) - (mlx->py.posy + mlx->rc.rayy
					* mlx->rc.wall_dist[mlx->rc.line] - mlx->rc.mapy));
	}
	if (mlx->rc.wall_dist[mlx->rc.line] > mlx->rc.max_dist)
		mlx->rc.max_dist = mlx->rc.wall_dist[mlx->rc.line];
}

/*
**	Coordinates the whole creation of the new image to show on the window.
*/

void	raycaster(t_mlx *mlx)
{
	mlx->rc.camy = mlx->py.dirx * mlx->rc.fov;
	mlx->rc.camx = -mlx->py.diry * mlx->rc.fov;
	mlx->rc.line = 0;
	mlx->rc.max_dist = 0;
	while (mlx->rc.line < mlx->winw)
	{
		mlx->rc.mapy = mlx->py.posy;
		mlx->rc.mapx = mlx->py.posx;
		mlx->rc.camdot = (2 * mlx->rc.line + 1) / (double)mlx->winw - 1;
		mlx->rc.rayy = mlx->py.diry + mlx->rc.camy * mlx->rc.camdot;
		mlx->rc.rayx = mlx->py.dirx + mlx->rc.camx * mlx->rc.camdot;
		ray_impact_part_one(mlx);
		ray_impact_part_two(mlx);
		mlx->rc.lnh = (mlx->winh / mlx->rc.wall_dist[mlx->rc.line]);
		paint_line(mlx);
		mlx->rc.line++;
	}
	spriter(mlx);
}
