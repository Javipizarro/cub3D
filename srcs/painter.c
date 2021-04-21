/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:08:41 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/18 11:00:20 by jpizarro         ###   ########.fr       */
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

t_img	*pick_txtr(t_mlx *mlx)
{
	t_img	*txtr;

	if (mlx->rc.face == 'n')
		txtr = &mlx->set.n;
	else if (mlx->rc.face == 's')
		txtr = &mlx->set.s;
	else if (mlx->rc.face == 'e')
		txtr = &mlx->set.e;
	else if (mlx->rc.face == 'w')
		txtr = &mlx->set.w;
	return (txtr);
}

//t_img	*pick_txtr(t_mlx *mlx)
//{
//	t_img img;
//
//	img.ptr = mlx_xpm_file_to_image(mlx->mlx, "./img/eagle.xpm", &img.dimx, &img.dimy);
//	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lnlen, &img.endian);
//	return (&img);
//}


//void	paint_line(t_mlx *mlx)
//{
//	int		i;
//	int		xpmx;
//	int		xpmy;
//	t_img	*txtr;
//
//	i = 0;
//	mlx->rc.color = 0;
//	while (i <= (mlx->winh - mlx->rc.lnh) / 2)
//	{
//		pixel_push(mlx, mlx->rc.line, i);
//		pixel_push(mlx, mlx->rc.line, mlx->winh - i);
//		i++;
//	}
//	txtr = pick_txtr(mlx);
//	xpmx = (int)(txtr->dimx * mlx->rc.rayimp);
//	while (i < (mlx->winh + mlx->rc.lnh) / 2)
//	{
//		xpmy = (int)(txtr->dimy * (2 * i - mlx->winh + mlx->rc.lnh) / (2 * mlx->rc.lnh));
//		//	Verifica si alguna vez estamos imprimiendo fuera de la textura. //////
//		if (xpmy < 0 || xpmy >= txtr->dimy)
//		{
//			printf("xpmy OOR = %i\ndimy = %i, winh = %i, lnh = %i, i = %i, posy = %f, posx = %f, diry = %f, dirx = %f\n", xpmy, txtr->dimy, mlx->winh, mlx->rc.lnh, i, mlx->py.posy, mlx->py.posx, mlx->py.diry, mlx->py.dirx);
//			printf("ESTAMOS FUERA DE LA TEXTURA\n");
//		}
//		////////
//		mlx->rc.color = *(unsigned*)(txtr->addr + (xpmy * txtr->dimx + xpmx) * txtr->bpp / 8);
//		pixel_push(mlx, mlx->rc.line, i);
//		i++;
//	}
//}

void	paint_line(t_mlx *mlx)
{
	int		i;
	int		xpmx;
	int		xpmy;
	t_img	*txtr;
	
	i = 0;
	mlx->rc.color = 0x00cccccc;
	while (i <= (mlx->winh - mlx->rc.lnh) / 2)
	{
		pixel_push(mlx, mlx->rc.line, i);
		i++;
	}
	txtr = pick_txtr(mlx);
	xpmx = (int)(txtr->dimx * mlx->rc.rayimp);
	while (i < (mlx->winh + mlx->rc.lnh) / 2)
	{
		xpmy = (int)(txtr->dimy * (2 * i - mlx->winh + mlx->rc.lnh) / (2 * mlx->rc.lnh));
		//	Verifica si alguna vez estamos imprimiendo fuera de la textura. //////
		if (xpmy < 0 || xpmy >= txtr->dimy)
		{
			printf("xpmy OOR = %i\ndimy = %i, winh = %i, lnh = %i, i = %i, posy = %f, posx = %f, diry = %f, dirx = %f\n", xpmy, txtr->dimy, mlx->winh, mlx->rc.lnh, i, mlx->py.posy, mlx->py.posx, mlx->py.diry, mlx->py.dirx);
			printf("ESTAMOS FUERA DE LA TEXTURA\n");
		}
		////////
		mlx->rc.color = *(unsigned*)(txtr->addr + (xpmy * txtr->dimx + xpmx) * txtr->bpp / 8);
		pixel_push(mlx, mlx->rc.line, i);
		i++;
	}
	mlx->rc.color = 0x00006666;
	while (i < mlx->winh)
	{
		pixel_push(mlx, mlx->rc.line, i);
		i++;
	}
}



int	button_on(t_mlx *mlx)
{
	t_img img;
	int i;
	int j = 0;

	img = mlx->set.e;

//	img.ptr = mlx_xpm_file_to_image(mlx->mlx, "./img/eagle.xpm", &img.dimx, &img.dimy);
//	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lnlen, &img.endian);

	mlx->rc.color = 0x00ff8800;
	while (j < img.dimy)
	{
		i = 0;
		while (i < img.dimx)
		{
			mlx->rc.color = *(unsigned*)(img.addr + (j * img.dimx + i) * img.bpp / 8);

			pixel_push(mlx, i, j);
			i++;
		}
		j++;
	}
//	printf("\n");

//	printf("Holaaaa desde press_button\n");
//	printf("img.dimx = %i, img.dimy = %i, img.bpp = %i, img.lnlen = %i, img.endian = %i\n", img.dimx, img.dimy, img.bpp, img.lnlen, img.endian);
	return (0);
}
