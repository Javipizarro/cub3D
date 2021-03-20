/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:07:11 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/20 17:29:21 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../cub3d.h"

#include <stdio.h>

//// My main
//
//int		main (void)
//{
//	t_mlxvars	mlx;
//	unsigned int	trgb;
//
//	if (!(mlx.mlx = mlx_init()))
//		return (1);
//
//	trgb = 0x00ff2266;
//	printf("trgb is: %x\nopp is : %x\n", trgb, get_opp(trgb));
//	printf("trgb is: %x\n", trgb);
//
//	return (0);
//}

//// Hooking into Loops
//
//int		main(void)
//{
//	void	*mlx_ptr;
//
//	mlx_ptr = mlx_init();
//	mlx_loop(mlx_ptr);
//	
//	return(0);
//}


//// Hooking into events
//
//typedef struct s_vars
//{
//	void	*mlx_ptr;
//	void	*win_ptr;
//}			t_vars;
//
//int		close(int keycode, t_vars *vars)
//{
//	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
//	printf("Windows Destroyed!\n");
//}
//
//int		main(void)
//{
//	t_vars	vars;
//
//	vars.mlx_ptr = mlx_init();
//	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 800, 600, "Hook & Destroy");
//	mlx_hook(vars.win_ptr, 4, 1L<<2, close, &vars);
//	mlx_loop(vars.mlx_ptr);
//
//	return (0);
//}


// Hook

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_vars;

int		key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!\n");
	printf("Keycode = %i\n", keycode);
	printf("win_ptr = %p\n", vars->win_ptr);
	return (0);
}

int	mouse_click_hook(int button, int posx, int posy, t_vars *vars)
{
	printf("Hello from mouse_hook!\n");
	printf("button = %i\n", button);
	printf("posx = %i\n", posx);
	printf("posy = %i\n", posy);
	printf("win_ptr = %p\n", vars->win_ptr);
	return (0);
}

int event_hook(int info1, int info2, int info3, int info4, t_vars *vars)
{
	printf("Hello from event_hook\n");
	printf("info1 = %i\n", info1);
	printf("info2 = %i\n", info2);
	printf("info3 = %i\n", info3);
	printf("info4 = %i\n", info4);
	printf("win_ptr = %p\n", vars->win_ptr);
	return (0);
}

int release_key_hook(int info1, int info2, t_vars *vars)
{
	printf("Hello from release_key_hook\n");
	printf("info1 = %i\n", info1);
	printf("info2 = %i\n", info2);
	printf("win_ptr = %p\n", vars->win_ptr);
	return (0);
}

int press_key_hook(int info1, int info2, t_vars *vars)
{
	printf("Hello from press_key_hook\n");
	printf("info1 = %i\n", info1);
	printf("info2 = %i\n", info2);
	printf("win_ptr = %p\n", vars->win_ptr);
	return (0);
}

int		main(void)
{
	t_vars	vars;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 800, 600, "Hooks");
	mlx_key_hook(vars.win_ptr, key_hook, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_click_hook, &vars);
//	mlx_hook(vars.win_ptr, 5, 1L<<3, event_hook, &vars);
//	mlx_hook(vars.win_ptr, 3, 1L<<1, release_key_hook, &vars);
//	mlx_hook(vars.win_ptr, 2, 1L<<0, press_key_hook, &vars);
	mlx_loop(vars.mlx_ptr);

	return (0);
}

//// Aquí programa completo para pintar en pantalla un pixel
//
//typedef struct s_data
//{
//	void	*img;
//	char	*addr;
//	int		bpp;
//	int		lnlen;
//	int		endian;	
//}			t_data;
//
//void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
//{
//	char	*dst;
//
//	dst = data->addr + (y * data->lnlen + x * (data->bpp / 8));
//	*(unsigned int*)dst = color;
//}
//
//int		main(void)
//{
//	void	*mlx_ptr;
//	void	*win_ptr;
//	t_data	img;
//
//	mlx_ptr = mlx_init();
//	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "cub3D");
//	img.img = mlx_new_image(mlx_ptr, 800, 600);
//	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.lnlen, &img.endian);
//	printf("lnlen = %i\n", img.lnlen);
//	my_mlx_pixel_put(&img, 0, 0, 0x00FF0000);
//	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
//	mlx_loop(mlx_ptr);
//}


//int		main(void)
//{
//	void	*mlx;
//	t_data	img;
//
//	mlx = mlx_inint();
//	img.img = mlx_new_image(mlx, 600, 400);
//
//	/*
//	** After creating an image, we can call 'mlx_get_data_addr_', we pass
//	** 'bits_per_pixel', 'line_length', and 'endian' by reference. These will
//	** then be set accordingly for the *current* data address.
//	*/
//
//	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.lnlen, &img.endian);
//	/*
//	** We should calculate the memory offset using the line length (lnlen)
//	** set by mlx_get_data_addr.
//	**
//	** int	offset = (y * line_length + x * (bits_per_pixel / 8));
//	*/
//	return (0);
//}
//
//void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
//{
//	char	*dst;
//
//	dst = data->addr + (y * data->lnlen + x * (data->bpp / 8));
//	*(unsigned int*)dst = color;
//}


//int		main(void)
//{
//	void	*img_ptr;
//	void	*mlx_ptr;
//
//	mlx_ptr = mlx_init();
//	img_ptr = mlx_new_image(mlx_ptr, 600, 400);
//
//	return(0);
//}


//int		main(void)
//{
//	void	*mlx_ptr;	// holds the location of our current MLX instance
//	void	*win_ptr;	//  pointer to the window we have just created.
//
//	mlx_ptr = mlx_init(); 
//	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Ptr1");
//	mlx_loop(mlx_ptr);
//
//	return (0);
//}
