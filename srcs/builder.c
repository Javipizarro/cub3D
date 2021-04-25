/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:53:14 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/25 13:35:28 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	/////////////////////// CAMBIAR EL T_SET POR 5 T_IMG
	t_set	set;
	
	set.n.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathn, &set.n.dimx, &set.n.dimy);
	set.n.addr = mlx_get_data_addr(set.n.ptr, &set.n.bpp, &set.n.lnlen, &set.n.endian);
	set.s.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.paths, &set.s.dimx, &set.s.dimy);
	set.s.addr = mlx_get_data_addr(set.s.ptr, &set.s.bpp, &set.s.lnlen, &set.s.endian);
	set.e.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathe,  &set.e.dimx, &set.e.dimy);
	set.e.addr = mlx_get_data_addr(set.e.ptr, &set.e.bpp, &set.e.lnlen, &set.e.endian);
	set.w.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathw,  &set.w.dimx, &set.w.dimy);
	set.w.addr = mlx_get_data_addr(set.w.ptr, &set.w.bpp, &set.w.lnlen, &set.w.endian);
	set.p.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathp, &set.p.dimx, &set.p.dimy);
	set.p.addr = mlx_get_data_addr(set.p.ptr, &set.p.bpp, &set.p.lnlen, &set.p.endian);
	mlx->set = set;
}

int	bye(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

int		builder(int ac, t_mlx *mlx)
{
	set_control(mlx);
	set_player(mlx);
	mlx->winw = 800;
	mlx->winh = 600;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->winw, mlx->winh, "RayCasting");
	set_set(mlx);
	mlx->img.ptr = mlx_new_image(mlx->mlx, mlx->winw, mlx->winh);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.lnlen, &mlx->img.endian);
	mlx_do_key_autorepeatoff(mlx->mlx);
	
//	mlx->color = 0x00ffff00;
//	mlx->img = 0;
//	mlx_hook(mlx->win, 2, 1L<<0, press_key, &mlx);
//	mlx_hook(mlx->win, 4, 0L, press_button, &mlx);
//	mlx_hook(mlx->win, 6, 0L, move_mouse, &mlx);
//	mlx_hook(mlx->win, 5, 0L, release_button, &mlx);
//	mlx_hook(mlx->win, 3, 1L<<1, release_key, &mlx);
//	mlx_hook(mlx->win, 17, 0L, prueba, &mlx);

//	img1.ptr = mlx_new_image(mlx->mlx, mlx->winw, mlx->winh);
//	img1.addr = mlx_get_data_addr(img1.ptr, &img1.bpp, &img1.lnlen, &img1.endian);
//	mlx->img = img;
//	mlx->img1 = img1;
	
//	printf("lnlen = %i\n", img.lnlen);
//	pixel_push(&img, 0, 0, 0x00FF0000);
//	mlx_put_image_to_window(mlx->mlx, mlx->win, img.ptr, 0, 0);

	mlx_hook(mlx->win, 2, 1L<<0, key_pressed, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_released, mlx);
	mlx_hook(mlx->win, 17, 0L, bye, mlx);
	mlx_loop_hook(mlx->mlx, play, mlx);
	mlx_loop(mlx->mlx);

	return (0);
}
