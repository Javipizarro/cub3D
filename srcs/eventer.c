/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 07:58:01 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/18 11:36:28 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where the inputs received from the user are managed.
*/

#include "../cub3d.h"

int	play(t_mlx *mlx)
{
	float	dev;
//	float	oldx;
//	float	oldy;

//	oldx = mlx->py.posx;
//	oldy = mlx->py.posy;
	mlx->py.posx += mlx->py.dirx * mlx->ctr.speed * mlx->py.move[0] * (0.7 + 0.3 * (!mlx->py.move[1]));
	mlx->py.posy += mlx->py.diry * mlx->ctr.speed * mlx->py.move[0] * (0.7 + 0.3 * (!mlx->py.move[1]));
	mlx->py.posx += mlx->py.diry * mlx->ctr.speed * mlx->py.move[1] * (0.7 + 0.3 * (!mlx->py.move[0]));
	mlx->py.posy -= mlx->py.dirx * mlx->ctr.speed * mlx->py.move[1] * (0.7 + 0.3 * (!mlx->py.move[0]));
//////////// Manejo de colisiones contra las paredes, a espera de poder almacenar el mapa	
//	if ((int)oldx != (int)mlx->py.posx && map[(int)oldy][(int)mlx->py.posx])
//		mlx->py.posx = oldx;
//	if ((int)oldy != (int)mlx->py.posy && map[(int)mlx->py.posy][(int)oldx])
//		mlx->py.posy = oldy;
	mlx->py.dirx = mlx->py.dirx * cos(mlx->ctr.turn * mlx->py.spin) - mlx->py.diry * sin(mlx->ctr.turn * mlx->py.spin);
	mlx->py.diry = mlx->py.dirx * sin(mlx->ctr.turn * mlx->py.spin) + mlx->py.diry * cos(mlx->ctr.turn * mlx->py.spin);
	dev = hypot(mlx->py.dirx, mlx->py.diry);
	mlx->py.dirx /= dev;
	mlx->py.diry /= dev;
//	printf("|dir| = %f", sqrtf(mlx->py.dirx * mlx->py.dirx + mlx->py.diry * mlx->py.diry));
	raycaster(mlx);
//	if (mlx->button)
//		button_on(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
	return (0);
}

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == mlx->ctr.u || key == mlx->ctr.d)
		mlx->py.move[0] = (key == mlx->ctr.u) - (key == mlx->ctr.d);
	else if (key == mlx->ctr.r || key == mlx->ctr.l)
		mlx->py.move[1] = (key == mlx->ctr.l) - (key == mlx->ctr.r);
	else if (key == mlx->ctr.tl || key == mlx->ctr.tr)
		mlx->py.spin = - (key == mlx->ctr.tl) + (key == mlx->ctr.tr);
	else if (key == mlx->ctr.esc)
		bye(mlx);
	return (0);
}

int	key_released(int key, t_mlx *mlx)
{
	if (key == mlx->ctr.u || key == mlx->ctr.d)
		mlx->py.move[0] = 0;
	else if (key == mlx->ctr.r || key == mlx->ctr.l)
		mlx->py.move[1] = 0;
	else if (key == mlx->ctr.tl || key == mlx->ctr.tr)
		mlx->py.spin = 0;
	return (0);
}
