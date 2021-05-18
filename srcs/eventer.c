/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 07:58:01 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 18:52:15 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where the inputs received from the user are managed.
*/

#include "../cub3d.h"

/*
**	Calculates the new position and direction of the player, based on
**	the current possition, direction and the movement applied to it.
*/

void	new_player_pos(t_mlx *mlx)
{
	float	dev;

	mlx->py.posx += mlx->py.dirx * mlx->ctr.speed * mlx->py.advance
		* (M_SQRT1_2 + 0.3 * (!mlx->py.sidemove));
	mlx->py.posy += mlx->py.diry * mlx->ctr.speed * mlx->py.advance
		* (M_SQRT1_2 + 0.3 * (!mlx->py.sidemove));
	mlx->py.posx += mlx->py.diry * mlx->ctr.speed * mlx->py.sidemove
		* (M_SQRT1_2 + 0.3 * (!mlx->py.advance));
	mlx->py.posy -= mlx->py.dirx * mlx->ctr.speed * mlx->py.sidemove
		* (M_SQRT1_2 + 0.3 * (!mlx->py.advance));
	mlx->py.dirx = mlx->py.dirx * cos(mlx->ctr.turn * mlx->py.turn)
		- mlx->py.diry * sin(mlx->ctr.turn * mlx->py.turn);
	mlx->py.diry = mlx->py.dirx * sin(mlx->ctr.turn * mlx->py.turn)
		+ mlx->py.diry * cos(mlx->ctr.turn * mlx->py.turn);
	dev = hypot(mlx->py.dirx, mlx->py.diry);
	mlx->py.dirx /= dev;
	mlx->py.diry /= dev;
}

/*
**	Orders to calculate the new player possition, and corrects it based on
**	collisions with walls.
**	It then calls raycaster() to generate the new image and also
**	the mlx_put_image_to_window() to display it.
*/

int	play(t_mlx *mlx)
{
	float	oldx;
	float	oldy;

	oldx = mlx->py.posx;
	oldy = mlx->py.posy;
	new_player_pos(mlx);
	if (!(mlx->map.map[(int)oldy][(int)mlx->py.posx] == '0'
		|| mlx->map.map[(int)oldy][(int)mlx->py.posx] == ' '))
		mlx->py.posx = oldx;
	if (!(mlx->map.map[(int)(mlx->py.posy + 0)][(int)oldx] == '0'
	|| mlx->map.map[(int)(mlx->py.posy + 0)][(int)oldx] == ' '))
		mlx->py.posy = oldy;
	if (!(mlx->map.map[(int)(mlx->py.posy + 0)][(int)mlx->py.posx] == '0'
	|| mlx->map.map[(int)(mlx->py.posy + 0)][(int)mlx->py.posx] == ' '))
	{
		mlx->py.posx = oldx;
		mlx->py.posy = oldy;
	}
	raycaster(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
	return (0);
}

/*
**	When a key is pressed it changes the motion of the player accordingly.
**	If the pressed key is 'ESC', it calls game_over() to exit the program.
*/

int	key_pressed(int key, t_mlx *mlx)
{
	if (key == mlx->ctr.moveforward)
		mlx->py.moveforward = 1;
	if (key == mlx->ctr.movebackward)
		mlx->py.movebackward = 1;
	if (key == mlx->ctr.moveleft)
		mlx->py.moveleft = 1;
	if (key == mlx->ctr.moveright)
		mlx->py.moveright = 1;
	if (key == mlx->ctr.turnleft)
		mlx->py.turnleft = 1;
	if (key == mlx->ctr.turnright)
		mlx->py.turnright = 1;
	if (key == mlx->ctr.esc)
		game_over(mlx);
	mlx->py.advance = mlx->py.moveforward - mlx->py.movebackward;
	mlx->py.sidemove = mlx->py.moveleft - mlx->py.moveright;
	mlx->py.turn = mlx->py.turnright - mlx->py.turnleft;
	return (0);
}

/*
**	When a key is released it changes the motion of the player accordingly.
*/

int	key_released(int key, t_mlx *mlx)
{
	if (key == mlx->ctr.moveforward)
		mlx->py.moveforward = 0;
	if (key == mlx->ctr.movebackward)
		mlx->py.movebackward = 0;
	if (key == mlx->ctr.moveleft)
		mlx->py.moveleft = 0;
	if (key == mlx->ctr.moveright)
		mlx->py.moveright = 0;
	if (key == mlx->ctr.turnleft)
		mlx->py.turnleft = 0;
	if (key == mlx->ctr.turnright)
		mlx->py.turnright = 0;
	mlx->py.advance = mlx->py.moveforward - mlx->py.movebackward;
	mlx->py.sidemove = mlx->py.moveleft - mlx->py.moveright;
	mlx->py.turn = mlx->py.turnright - mlx->py.turnleft;
	return (0);
}
