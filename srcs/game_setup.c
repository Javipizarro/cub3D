/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:53:14 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/13 18:33:04 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	Sets the control keys that are going to be used,
**	and the player's pace to move and turn.
*/

void	set_control(t_mlx *mlx)
{
	mlx->ctr.u = 13;
	mlx->ctr.d = 1;
	mlx->ctr.l = 0;
	mlx->ctr.r = 2;
	mlx->ctr.tl = 123;
	mlx->ctr.tr = 124;
	mlx->ctr.esc = 53;
	mlx->ctr.speed = 0.1;
	mlx->ctr.turn = 0.05;
}

/*
**	Sets the player initial state.
*/

void	init_player(t_mlx *mlx)
{
	mlx->py.move[0] = 0;
	mlx->py.move[1] = 0;
	mlx->py.spin = 0;
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
	mlx->set.sp.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathp,
	&mlx->set.sp.dimx, &mlx->set.sp.dimy);
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
	mlx->set.sp.addr = mlx_get_data_addr(mlx->set.sp.ptr, &mlx->set.sp.bpp,
	&mlx->set.sp.lnlen, &mlx->set.sp.endian);
	return (0);
}
