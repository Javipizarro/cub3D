/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:53:14 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/05 11:02:56 by jpizarro         ###   ########.fr       */
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

void	init_player(t_mlx *mlx)
{
	mlx->py.move[0] = 0;
	mlx->py.move[1] = 0;
	mlx->py.spin = 0;
}

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
	mlx->set.p.ptr = mlx_xpm_file_to_image(mlx->mlx, mlx->set.pathp,
	&mlx->set.p.dimx, &mlx->set.p.dimy);
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
	mlx->set.p.addr = mlx_get_data_addr(mlx->set.p.ptr, &mlx->set.p.bpp,
	&mlx->set.p.lnlen, &mlx->set.p.endian);
	return (0);
}

int	bye(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	final_free(mlx);
	if (!(mlx->err))
		msnprt(1, "Thanks for playing!!!");
	system("leaks cub3D");
	exit(0);
	return (0);
}

int		builder(int ac, t_mlx *mlx)
{
	set_control(mlx);
	init_player(mlx);
	mlx->winw = 800;
	mlx->winh = 600;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->winw, mlx->winh, "RayCasting");
	mlx->err = set_set(mlx);
	if (mlx->err)
	{
		bye(mlx);
		return (2);
	}
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
