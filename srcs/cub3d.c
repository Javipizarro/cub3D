/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:59:22 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/09 22:35:21 by jpizarro         ###   ########.fr       */
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
	ctr.speed = 0.4;
	ctr.turn = 0.05;
	mlx->ctr = ctr;
}

void	set_player(t_mlx *mlx)
{
	t_player py;

	py.posy = 3;
	py.posx = 3;
	py.diry = 1;
	py.dirx = 0;
	py.move[0] = 0;
	py.move[1] = 0;
	py.spin = 0;
	mlx->py = py;
}

int	bye(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

int	main(void)
{
	t_mlx		mlx;
//	t_img		img;
//	t_img		img1;

	set_control(&mlx);
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
	mlx_hook(mlx.win, 17, 0L, bye, &mlx);
	mlx_hook(mlx.win, 3, 1L<<1, key_released, &mlx);
	mlx_loop_hook(mlx.mlx, play, &mlx);


	mlx_loop(mlx.mlx);

	return (0);
}