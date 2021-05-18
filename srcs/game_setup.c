/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:53:14 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 12:55:46 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	Sets the control keys that are going to be used,
**	and the player's pace to move and turn.
*/

void	set_control(t_mlx *mlx)
{
	mlx->ctr.moveforward = 13;
	mlx->ctr.movebackward = 1;
	mlx->ctr.moveleft = 0;
	mlx->ctr.moveright = 2;
	mlx->ctr.turnleft = 123;
	mlx->ctr.turnright = 124;
	mlx->ctr.esc = 53;
	mlx->ctr.speed = 0.1;
	mlx->ctr.turn = 0.05;
}

/*
**	Sets the player initial state.
*/

void	set_player(t_mlx *mlx)
{
	mlx->py.moveforward = 0;
	mlx->py.movebackward = 0;
	mlx->py.advance = 0;
	mlx->py.moveleft = 0;
	mlx->py.moveright = 0;
	mlx->py.sidemove = 0;
	mlx->py.turnleft = 0;
	mlx->py.turnright = 0;
	mlx->py.turn = 0;
}

/*
**	Sets the textures for the set form the .cub file.
*/

int	set_set(t_mlx *mlx)
{
	mlx->set.n.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathn,
	&mlx->set.n.dimx, &mlx->set.n.dimy);
	mlx->set.s.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.paths,
	&mlx->set.s.dimx, &mlx->set.s.dimy);
	mlx->set.e.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathe,
	&mlx->set.e.dimx, &mlx->set.e.dimy);
	mlx->set.w.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathw,
	&mlx->set.w.dimx, &mlx->set.w.dimy);
	mlx->set.s1.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.paths1,
	&mlx->set.s1.dimx, &mlx->set.s1.dimy);
	if (!(mlx->set.n.ptr && mlx->set.s.ptr && mlx->set.e.ptr && mlx->set.w.ptr))
		return (msnprt(2, "Texture file does not exits."));
	mlx->set.n.addr = mlx_get_data_addr(mlx->set.n.ptr, &mlx->set.n.bpp,
	&mlx->set.n.lnlen, &mlx->set.n.endian);
	mlx->set.s.addr = mlx_get_data_addr(mlx->set.s.ptr, &mlx->set.s.bpp,
	&mlx->set.s.lnlen, &mlx->set.s.endian);
	mlx->set.e.addr = mlx_get_data_addr(mlx->set.e.ptr, &mlx->set.e.bpp,
	&mlx->set.e.lnlen, &mlx->set.e.endian);
	mlx->set.w.addr = mlx_get_data_addr(mlx->set.w.ptr, &mlx->set.w.bpp,
	&mlx->set.w.lnlen, &mlx->set.w.endian);
	mlx->set.s1.addr = mlx_get_data_addr(mlx->set.s1.ptr, &mlx->set.s1.bpp,
	&mlx->set.s1.lnlen, &mlx->set.s1.endian);
	return (0);
}

/*
**	Here is where the lists used to paint the sprites are created
*/

int	prepare_sprites(t_mlx *mlx)
{
	int i;
	int	x;
	int	y;

	mlx->sp.list = malloc(sizeof(t_one_sprite) * mlx->sp.num);
	mlx->sp.order = malloc(sizeof(int) * mlx->sp.num + 1);
	if (!mlx->sp.list || !mlx->sp.order)
		return (msnprt(2, "Error while allocating sprite lists"));
	i = 0;
	y = -1;
	while (mlx->map.map[++y])
	{
		x = -1;
		while (mlx->map.map[y][++x])
		{
			if (mlx->map.map[y][x] == '2')
			{
				mlx->sp.list[i].x = x;
				mlx->sp.list[i].y = y;
				i++;
			}
		}
	}
	return (0);
}

