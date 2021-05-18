/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start_and_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:53:14 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 12:49:17 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	Prepares the minilib and its dependencies for the game
**	to be visualized.
*/

int	mlx_start_and_set_up(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->winw, mlx->winh, "RayCasting");
	mlx->img.ptr = mlx_new_image(mlx->mlx, mlx->winw, mlx->winh);
	mlx->img.addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, &mlx->img.lnlen, &mlx->img.endian);
	set_player(mlx);
	mlx->err = set_set(mlx);
	if (!mlx->err)
		mlx->err = set_rc_constants(mlx);
	if (!mlx->err)
		mlx->err = prepare_sprites(mlx);
	if (mlx->err)
		game_over(mlx);
	return (0);
}

/*
**	Sets and manages everything for the game to respond to the player's input.
*/

void	game_start(t_mlx *mlx)
{
	set_control(mlx);
	mlx_do_key_autorepeatoff(mlx->mlx);
	mlx_hook(mlx->win, 2, 1L<<0, key_pressed, mlx);
	mlx_hook(mlx->win, 3, 1L<<1, key_released, mlx);
	mlx_hook(mlx->win, 17, 0L, game_over, mlx);
	mlx_loop_hook(mlx->mlx, play, mlx);
	mlx_loop(mlx->mlx);
}

/*
**	Saves the initial imgage of the game to a bmp without starting it.
*/

void	bmp_of_game_ini(t_mlx *mlx)
{
	int		fd;

	raycaster(mlx);
	fd = open("cub3D.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 0)
		mlx->err = 2;
	if(!mlx->err)
		write_bmp_header(mlx, fd);
	if(!mlx->err)
		write_dib_header(mlx, fd);
	if(!mlx->err)
		write_pixels_to_bmp(mlx, fd);
	if(!mlx->err)
		mlx->err = close(fd);
	if(mlx->err)
		msnprt(2, "Error while creating bmp has ocurred");
	game_over(mlx);
}

/*
**	Closes the minilib and exits the gamel
*/

int	game_over(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free_mlx(mlx);
	if (!(mlx->err))
		msnprt(1, "Thanks for playing!!!");
/////////
	system("leaks cub3D");
	//////////
	exit(0);
	return (0);
}
