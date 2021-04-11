/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:59:22 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/11 08:43:05 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
**	This is the file where everything starts.
*/

#include "../cub3d.h"

void	set_control(t_mlx *mlx)
{
	t_controls	ctr;

	ctr.u = 13;
	ctr.d = 1;
	ctr.l = 0;
	ctr.r = 2;
	ctr.tl = 123;
	ctr.tr = 124;
	ctr.esc = 53;
	ctr.speed = 0.1;
	ctr.turn = 0.05;
	mlx->ctr = ctr;
}

void	set_player(t_mlx *mlx)
{
	t_player py;

	py.posx = 11.5;
	py.posy = 22;
	py.dirx = 0;
	py.diry = -1;
	py.move[0] = 0;
	py.move[1] = 0;
	py.spin = 0;
	mlx->py = py;
}

void	set_set(t_mlx *mlx)
{
	t_set	set;
	
	set.n.ptr = mlx_xpm_file_to_image(mlx->mlx, "./img/eagle.xpm", &set.n.dimx, &set.n.dimy);
	set.n.addr = mlx_get_data_addr(set.n.ptr, &set.n.bpp, &set.n.lnlen, &set.n.endian);
	set.s.ptr = mlx_xpm_file_to_image(mlx->mlx, "./img/eagle.xpm", &set.s.dimx, &set.s.dimy);
	set.s.addr = mlx_get_data_addr(set.s.ptr, &set.s.bpp, &set.s.lnlen, &set.s.endian);
	set.e.ptr = mlx_xpm_file_to_image(mlx->mlx, "./img/eagle.xpm",  &set.e.dimx, &set.e.dimy);
	set.e.addr = mlx_get_data_addr(set.e.ptr, &set.e.bpp, &set.e.lnlen, &set.e.endian);
	set.w.ptr = mlx_xpm_file_to_image(mlx->mlx, "./img/eagle.xpm",  &set.w.dimx, &set.w.dimy);
	set.w.addr = mlx_get_data_addr(set.w.ptr, &set.w.bpp, &set.w.lnlen, &set.w.endian);
	set.s1.ptr = mlx_xpm_file_to_image(mlx->mlx, "./img/greenlight.xpm", &set.s1.dimx, &set.s1.dimy);
	set.s1.addr = mlx_get_data_addr(set.s1.ptr, &set.s1.bpp, &set.s1.lnlen, &set.s1.endian);
	mlx->set = set;
}

int	bye(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
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



int	main(void)
{
	t_mlx		mlx;
//	t_img		img;
//	t_img		img1;

	set_control(&mlx);
	set_set(&mlx);
	set_player(&mlx);
	mlx.winw = 800;
	mlx.winh = 600;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, mlx.winw, mlx.winh, "RayCasting");
	mlx.img.ptr = mlx_new_image(mlx.mlx, mlx.winw, mlx.winh);
	mlx.img.addr = mlx_get_data_addr(mlx.img.ptr, &mlx.img.bpp, &mlx.img.lnlen, &mlx.img.endian);
	mlx_do_key_autorepeatoff(mlx.mlx);
	//raycaster(&mlx);
//	mlx.color = 0x00ffff00;
//	mlx.img = 0;
//	mlx_hook(mlx.win, 2, 1L<<0, press_key, &mlx);
//	mlx_hook(mlx.win, 4, 0L, press_button, &mlx);
//	mlx_hook(mlx.win, 6, 0L, move_mouse, &mlx);
//	mlx_hook(mlx.win, 5, 0L, release_button, &mlx);
//	mlx_hook(mlx.win, 3, 1L<<1, release_key, &mlx);
//	mlx_hook(mlx.win, 17, 0L, prueba, &mlx);

//	img1.ptr = mlx_new_image(mlx.mlx, mlx.winw, mlx.winh);
//	img1.addr = mlx_get_data_addr(img1.ptr, &img1.bpp, &img1.lnlen, &img1.endian);
//	mlx.img = img;
//	mlx.img1 = img1;
	
//	printf("lnlen = %i\n", img.lnlen);
//	pixel_push(&img, 0, 0, 0x00FF0000);
//	mlx_put_image_to_window(mlx.mlx, mlx.win, img.ptr, 0, 0);

	mlx_hook(mlx.win, 2, 1L<<0, key_pressed, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, key_released, &mlx);
	mlx_hook(mlx.win, 17, 0L, bye, &mlx);
	mlx_loop_hook(mlx.mlx, play, &mlx);

/////////////
//	mlx_hook(mlx.win, 4, 0L, xpm_paint, &mlx);
/////////////

	mlx_loop(mlx.mlx);

	return (0);
}