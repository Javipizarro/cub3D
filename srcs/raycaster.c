/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:02:12 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/11 07:32:20 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here we take the situation of the player in the map, and make visual
**	interactions with the environment.
*/

#include "../cub3d.h"

int	raycaster(t_mlx *mlx)
{
	t_raycast	rc;

//	int	rc.mapw = 24;
//	int rc.maph = 24;
	mlx->winw = 800;
//	mlx->winh = 600;

//int map[5][5] = {
//		{11,12,13,14,15},
//		{21, 0, 0, 0,25},
//		{31, 0, 0, 0,35},
//		{41, 0, 0, 0,45},
//		{51,52,53,54,55}
//	};

int map[24][24] = {
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

//	rc.posy = mlx->py.posy;
//	rc.posx = mlx->py.posx;
//	mlx->py.diry = 0.5;
//	mlx->py.dirx = 0.86602543784439;
	rc.fov = 0.66;
	rc.camy = mlx->py.dirx * rc.fov;
	rc.camx = - mlx->py.diry * rc.fov;
	
	rc.line = 0;
	while (rc.line < mlx->winw)
//	while (rc.line <= mlx->winw)
	{
		rc.mapy = mlx->py.posy;
		rc.mapx = mlx->py.posx;
		rc.camdot = (2 * rc.line + 1) / (double)mlx->winw - 1;
	//	rc.camdot = (2 * i) / (double)mlx->winw - 1;
		rc.rayy = mlx->py.diry + rc.camy * rc.camdot;
		rc.rayx = mlx->py.dirx + rc.camx * rc.camdot;
	//	double	raym = ft_hypo(rc.rayy, rc.rayx);			//	get ray's module
	//	rc.rayy /= rc.raym;							//	corrects rc.rayy as if ray were 1
	//	rc.rayx /= raym;							//	corrects rc.rayx as if ray were 1
		
//		printf("%f\n", rc.camdot);

		rc.incy = 1 / fabs(rc.rayy);
		rc.incx = 1 / fabs(rc.rayx);
		rc.iniy = fabs((mlx->py.posy - rc.mapy) - (rc.rayy > 0)) * rc.incy;
		rc.inix = fabs((mlx->py.posx - rc.mapx) - (rc.rayx > 0)) * rc.incx;

//	printf("rc.rayy = %f\trc.rayx = %f\n", rc.rayy, rc.rayx);
//	printf("rc.incy = %f\trc.incx = %f\trc.iniy = %f\trc.inix = %f\n", rc.incy, rc.incx, rc.iniy, rc.inix);

		while (map[rc.mapy][rc.mapx] == 0)
		{
			if (rc.iniy < rc.inix)
			{
				rc.mapy += (rc.rayy >= 0) - (rc.rayy < 0);
				rc.iniy += rc.incy;
				rc.face = 'h';
			}
			else
			{
				rc.mapx += (rc.rayx >= 0) - (rc.rayx < 0);
				rc.inix += rc.incx;
				rc.face = 'v';
			}
		}

		if (rc.face == 'h')
		{
//			rc.iniy -= rc.incy;
//			rc.color = 0xffff00;
			rc.face = 'n' * (rc.rayy >= 0) + 's' * (rc.rayy < 0);
			rc.dist = fabs((mlx->py.posy - rc.mapy - (rc.rayy < 0)) / rc.rayy);
			rc.rayimp = fabs((rc.rayy > 0) - (mlx->py.posx + rc.rayx * rc.dist - rc.mapx));
		}
		else
		{
//			rc.inix -= rc.incx;
//			rc.color = 0xaaaa00;
			rc.face = 'w' * (rc.rayx >= 0) + 'e' * (rc.rayx < 0);
			rc.dist = fabs((mlx->py.posx - rc.mapx - (rc.rayx < 0)) / rc.rayx);
			rc.rayimp = fabs((rc.rayx < 0) - (mlx->py.posy + rc.rayy * rc.dist - rc.mapy));
		}

//		printf("imp = %f\t", rc.rayimp);

//		if (rc.face == 'h')
//		{
////			rc.iniy -= rc.incy;
////			rc.color = 0xffff00;
//			rc.face = 'n' * (rc.rayy >= 0) + 's' * (rc.rayy < 0);
//			rc.dist = fabs((mlx->py.posy - rc.mapy - (rc.rayy < 0)) / rc.rayy);
//			rc.rayimp = (rc.rayx * rc.rayy < 0) + (rc.dist * rc.rayx) - (int)(rc.dist * rc.rayx);
//		}
//		else
//		{
////			rc.inix -= rc.incx;
////			rc.color = 0xaaaa00;
//			rc.face = 'w' * (rc.rayx >= 0) + 'e' * (rc.rayx < 0);
//			rc.dist = fabs((mlx->py.posx - rc.mapx - (rc.rayx < 0)) / rc.rayx);
//			rc.rayimp = (rc.rayx * rc.rayy < 0) + (rc.dist * rc.rayy) - (int)(rc.dist * rc.rayy);
//		}
		
		rc.lnh = (mlx->winh / rc.dist);
		mlx->rc = rc;

		paint_line(mlx);


//	printf("hit on %i\trc.mapy = %i\trc.mapx = %i\trc.face = %c\n", map[rc.mapy][rc.mapx], rc.mapy, rc.mapx,rc.face);
////	printf("mlx->py.posy = %f\tmlx->py.posx = %f\n", mlx->py.posy, mlx->py.posx);
//	printf("rc.dist = %f\n\n", rc.dist);
////	printf("rc.iniy = %f\trc.inix = %f\n", rc.iniy, rc.inix);
		
	rc.line++;
	}
//	printf("raycast completo\n");
//	printf("mlx->py.posy = %f\tmlx->py.posx = %f\n", mlx->py.posy, mlx->py.posx);
	return (0);
}
