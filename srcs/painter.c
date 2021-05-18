/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:08:41 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 20:32:40 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here we receive what needs to be showed, we create it, and push it
**	to the window.
*/

#include "../cub3d.h"

/*
**	Receives a position x and y, and a color mlx->color, and 'paints'
**	a pixel on the mlx->img according to the information.
*/

void	pixel_push(t_mlx *mlx, int x, int y)
{
	char	*dest;

	dest = mlx->img.addr + (y * mlx->img.lnlen + x * (mlx->img.bpp / 8));
	*(unsigned int *)dest = mlx->rc.color;
}

/*
**	According to the direction the wall showed is facing, this selects
**	the corresponding texture.
*/

t_img	*pick_txtr(t_mlx *mlx)
{
	t_img	*txtr;

	if (mlx->rc.face == 'n')
		txtr = &mlx->set.n;
	else if (mlx->rc.face == 's')
		txtr = &mlx->set.s;
	else if (mlx->rc.face == 'e')
		txtr = &mlx->set.e;
	else
		txtr = &mlx->set.w;
	return (txtr);
}

/*
**	Paint a vertical line with the ceilling color, the wall texture
**	and the floor color.
*/

void	paint_line(t_mlx *mlx)
{
	int		i;
	int		xpmx;
	int		xpmy;
	t_img	*txtr;

	i = 0;
	mlx->rc.color = mlx->set.c;
	while (i <= (mlx->winh - mlx->rc.lnh) / 2)
		pixel_push(mlx, mlx->rc.line, i++);
	txtr = pick_txtr(mlx);
	xpmx = (int)(txtr->dimx * mlx->rc.rayimp);
	while (i < (mlx->winh + mlx->rc.lnh) / 2 && i < mlx->winh)
	{
		xpmy = (int )(txtr->dimy * (2 * i - mlx->winh + mlx->rc.lnh)
				/ (2 * mlx->rc.lnh));
		mlx->rc.color = *(unsigned *)(txtr->addr + (xpmy * txtr->dimx + xpmx)
				* txtr->bpp / 8);
		pixel_push(mlx, mlx->rc.line, i);
		i++;
	}
	mlx->rc.color = mlx->set.f;
	while (i < mlx->winh)
		pixel_push(mlx, mlx->rc.line, i++);
}
