/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:08:41 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/11 08:48:24 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here we receive what needs to be showed, we create it, and push it
**	to the window.
*/

#include "../cub3d.h"

void	pixel_push(t_mlx *mlx, int x, int y)
{
	char	*dest;
//	printf("face = %c\n", mlx->rc.face);
//	printf("x = %i\ty = %i\n", x, y);

	dest = mlx->img.addr + (y * mlx->img.lnlen + x * (mlx->img.bpp / 8));
	*(unsigned int*)dest = mlx->rc.color;
}

//void	pixel_push(t_mlx *mlx, int x, int y)
//{
//	char	*dest;
//	int		colx;
//	int		coly;
//
////	printf("face = %c\n", mlx->rc.face);
////	printf("x = %i\ty = %i\n", x, y);
//	colx = (int)(mlx->set.n.dimx * mlx->rc.rayimp);
//	coly = (int)(mlx->set.n.dimy * y / mlx->winh);
//	dest = mlx->img.addr + (y * mlx->img.lnlen + x * (mlx->img.bpp / 8));
//	*(unsigned*)dest = *(unsigned*)mlx->set.n.ptr + (coly * mlx->set.n.lnlen + colx * (mlx->set.n.bpp / 8));
//}

//int	xpm_paint(int button, int x, int y, t_mlx *mlx)
//{
//	int i;
//	int j;
//
//	printf("hola!!!\n");
//
//	j = (mlx->set.n.dimy / 2 - y) * (mlx->set.n.dimy / 2 > y);
//	while (j < mlx->set.n.dimy && j < mlx->set.n.dimy / 2 + mlx->winh - y)
//	{
//		i = (mlx->set.n.dimx / 2 - x) * (mlx->set.n.dimx / 2 > x);
//		while (i < mlx->set.n.dimx && i < mlx->set.n.dimx / 2 + mlx->winw - x)
//		{
//			mlx->rc.color = *(unsigned int*)(mlx->set.n.addr + (j * mlx->set.n.dimx + i) * mlx->set.n.bpp / 8);
//			pixel_push(mlx, i + x - mlx->set.n.dimx / 2, j + y - mlx->set.n.dimy / 2);
//			i++;
//		}
//		j++;
//	}
//	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.ptr, 0, 0);
//	return (0);
//}


void	paint_line(t_mlx *mlx)
{
	int	i;
	int	xpmx;
	int	xpmy;
//	SEGÚN JUEGAS EL ESCENARIO SE ENCOGE EN LA HORIZONTAL

	i = 0;
	mlx->rc.color = 0;
	while (i <= (mlx->winh - mlx->rc.lnh) / 2)
	{
		pixel_push(mlx, mlx->rc.line, i);
		pixel_push(mlx, mlx->rc.line, mlx->winh - i);
		i++;
	}
	xpmx = (int)(mlx->set.n.dimx * mlx->rc.rayimp);
	while (i < (mlx->winh + mlx->rc.lnh) / 2)
	{
		xpmy = (int)(mlx->set.n.dimy * (2 * i - mlx->winh + mlx->rc.lnh) / (2 * mlx->rc.lnh));
		//	Verifica si alguna vez estamos imprimiendo fuera de la textura.
		if (xpmy < 0 || xpmy >= mlx->set.n.dimy)
			printf("xpmy OOR = %i\ndimy = %i, winh = %i, lnh = %i, i = %i, posy = %f, posx = %f, diry = %f, dirx = %f\n", xpmy, mlx->set.n.dimy, mlx->winh, mlx->rc.lnh, i, mlx->py.posy, mlx->py.posx, mlx->py.diry, mlx->py.dirx);
		xpmy < 0 ? xpmy = abs(xpmy) : xpmy >= mlx->set.n.dimy ? xpmy = mlx->set.n.dimy - 1 : 1;
		mlx->rc.color = *(unsigned*)(mlx->set.n.addr + (xpmy * mlx->set.n.dimx + xpmx) * mlx->set.n.bpp / 8);
		pixel_push(mlx, mlx->rc.line, i);
		i++;
	}
}