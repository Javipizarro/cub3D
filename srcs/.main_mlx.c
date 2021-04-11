/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:07:11 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/10 21:18:40 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
//#include "../cub3d.h"

#include <stdio.h>
# include <mlx.h>
# include <stdio.h>
//# include "libs/color/color.h"
//# include "libs/libft/libft.h"
//# include "libs/mathft/mathft.h"
# include <math.h>

//	Reading xpm images from files to the program: the same as the one below, but if you press "U", the program
//	shows an xpm image that is preloaded in the draw_xpm function. The way to show this image is by parsing it
//	pixel by pixel, reading the color and painting a pixel on an image that will later be sent to the window.
//	Another way to do this job is through mlx_put_image_to_window, pushing a second image after the main one, for
//	each loop; this last one is commented in the no_event function.

typedef struct s_xpm
{
	void		*ptr;
	char		*path;
	char		*addr;
	int			x_dim;
	int			y_dim;
	int			x_pos;
	int			y_pos;
	int			bpp;
	int			lnlen;
	int			endian;
}			t_xpm;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			lnlen;
	int			endian;
}			t_img;

typedef struct s_shape
{
	char		type;
	int			x;
	int			y;
	int			x_mov;
	int			y_mov;
	int			size;
}			t_shape;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img0;
	t_img		img1;
	t_shape		shape;
	char		img;
	t_xpm		xpm;
	int			x_dim;
	int			y_dim;
	unsigned	color;
	int			x_pos;
	int			y_pos;
}			t_vars;

int	press_key(int key_code, t_vars *vars);
void	change_color(int key_color, t_vars *vars);
int	wasdeq(int key_code, t_vars *vars);
void	draw_xpm(int key_code, t_vars *vars);
//t_xpm	set_xpm(char *path, int x_dim, int y_dim, t_vars *vars);
int	release_key(int key_code, t_vars *vars);
int	window_area(int key_code, t_vars *vars);
int	square_paint(t_vars *vars);
int	circle_paint(t_vars *vars);
int	xpm_paint(t_vars *vars);
void	fix_shape(t_vars *vars);
void	erase_shape(t_vars *vars);
void	pixel_push(t_vars *vars, int x, int y);
void	copy_img(t_vars *vars);



int	press_key(int key_code, t_vars *vars)
{
//	double invsKey = 1 / (double)key_code; // Para ver si da problemas C al dividir por 0 (no los da)
//	printf("Hello from press_key\n");
//	printf("key_code = %i\t", key_code);
//	printf("invKey = %g\n", invsKey);
//	printf("color: %u\n", vars->color);
//	printf("win_ptr = %p\n", vars->win_ptr);

	if ((key_code >= 12 && key_code <= 14) || (key_code >= 0 && key_code <= 2))
		wasdeq(key_code, vars);
	else if (key_code == 53)
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	else if ((key_code >= 18 && key_code <= 23) || key_code == 26 || key_code == 28)
		change_color(key_code, vars);
	else if ((key_code <= 126 && key_code >= 123) || key_code == 49)
		window_area(key_code, vars);
	else if (key_code == 31 || key_code == 32 || key_code == 34 || key_code == 35)
		draw_xpm(key_code, vars);

	return (0);
}

void	change_color(int key_code, t_vars *vars)
{
//	printf("key_code = %i\n", key_code);
	if (key_code == 28)
		vars->color = 0x80ffffff;
	else if (key_code == 18)
		vars->color = 0x80ff0000;
	else if (key_code == 19)
		vars->color = 0x8000ff00;
	else if (key_code == 20)
		vars->color = 0x800000ff;
	else if (key_code == 21)
		vars->color = 0x8000ffff;
	else if (key_code == 23)
		vars->color = 0x80ff00ff;
	else if (key_code == 22)
		vars->color = 0x80ffff00;
	else if (key_code == 26)
		vars->color = 0x80000000;
	if (vars->img == 1 || vars->img == 2)
	{
		copy_img(vars);
		if (vars->shape.type == 's')
			square_paint(vars);
		else if (vars->shape.type == 'c')
			circle_paint(vars);
	}
}

int	wasdeq(int key_code, t_vars *vars)
{

	if (key_code == 12)
	{
		erase_shape(vars);
		return (0);
	}
	if (vars->img == 2)
	{
		if (key_code == 14)
		{
			fix_shape(vars);
			return (0);
		}
		else if (key_code == 13)
			vars->shape.y_mov = -1;
		else if (key_code == 0)
			vars->shape.x_mov = -1;
		else if (key_code == 1)
			vars->shape.y_mov = 1;
		else if (key_code == 2)
			vars->shape.x_mov = 1;
	}
	return (0);
}

void	draw_xpm(int key_code, t_vars *vars)
{
	t_xpm	xpm;
//	int		i;
//	int		j;
//	int		dx;
//	int		dy;

	xpm.ptr = mlx_xpm_file_to_image(vars->mlx_ptr, "./img/eagle.xpm", &xpm.x_dim, &xpm.y_dim);
//	xpm.ptr = mlx_xpm_file_to_image(vars->mlx_ptr, "./img/enemy.xpm", &xpm.x_dim, &xpm.y_dim);
	xpm.addr = mlx_get_data_addr(xpm.ptr, &xpm.bpp, &xpm.lnlen, &xpm.endian);
	vars->xpm = xpm;
//	printf("xpm.ptr = %p\n", xpm.ptr);
//	printf("xpm.bpp = %i\n", xpm.bpp);
//	printf("img0.bpp = %i\n", vars->img0.bpp);
//	printf("img1.bpp = %i\n", vars->img1.bpp);
//	printf("xpm.lnlen = %i\n", xpm.lnlen);
//	printf("xpm.endian = %i\n", xpm.endian);
//	printf("color 120,120 = %x\n", *(int*)(xpm.ptr + 120 * xpm.lnlen + 120 * xpm.bpp));
	if (key_code == 32)
	{
		vars->img = 1;
		xpm_paint(vars);
	}
//	printf("x_pos = %i\n", vars->x_pos);
//	printf("y_pos = %i\n", vars->y_pos);
//	printf("mlx = %p\n", vars->mlx_ptr);
//	printf("win = %p\n", vars->win_ptr);
//	printf("xpm = %p\n", xpm.ptr);
//	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, xpm.ptr, vars->x_pos, vars->y_pos);
}

//t_xpm	*set_xpm(char *path, int x_dim, int y_dim, t_vars *vars)
//{
//	t_xpm		*xpm;
//
//	xpm = mlx_xpm_file_to_image(vars->mlx_ptr, path, &x_dim, &y_dim);
//	xpm.addr = mlx_get_data_addr(xpm.ptr, &xpm.bpp, &xpm.lnlen, &xpm.endian);
//	return (xpm);
//}

int	release_key(int key_code, t_vars *vars)
{
//	printf("Hello from release_key\n");
//	printf("key_code = %i\n", key_code);
	if (key_code == 13)
		vars->shape.y_mov = 0;
	else if (key_code == 0)
		vars->shape.x_mov = 0;
	else if (key_code == 1)
		vars->shape.y_mov = 0;
	else if (key_code == 2)
		vars->shape.x_mov = 0;
	return (0);
}

int	window_area(int key_code, t_vars *vars)
{
	short int	x0;
	short int	x1;
	short int	y0;
	short int	y1;
	short int	i;
	short int	j;

	vars->img = 0;
	x0 = 0 +  (vars->x_dim / 2) * (key_code == 124);
	x1 = vars->x_dim / (1 + (key_code == 123));
	y0 = 0 +  (vars->y_dim / 2) * (key_code == 125);
	y1 = vars->y_dim / (1 + (key_code == 126));

	j = y0;
	while (j < y1)
	{
		i = x0;
		while (i < x1)
		{
			pixel_push(vars, i, j);
			i++;
		}
		j++;
	}
	copy_img(vars);
	return (0);
}

int square_paint(t_vars *vars)
{
	int i;
	int j;

	vars->shape.x += vars->shape.x_mov;
	vars->shape.y += vars->shape.y_mov;
	j = (vars->shape.y - vars->shape.size / 2) * (vars->shape.y >= vars->shape.size / 2 );
	while (j < (vars->shape.y + vars->shape.size / 2) && j < vars->y_dim)
	{
		i = (vars->shape.x - vars->shape.size / 2) * (vars->shape.x >= vars->shape.size / 2 );
		while (i < (vars->shape.x + vars->shape.size / 2) && i < vars->x_dim)
		{
			pixel_push(vars, i, j);
			i++;
		}
		j++;
	}
	return (0);
}

int circle_paint(t_vars *vars)
{
	int i;
	int j;

	vars->shape.x += vars->shape.x_mov;
	vars->shape.y += vars->shape.y_mov;
	j = (vars->shape.y - vars->shape.size / 2) * (vars->shape.y >= vars->shape.size / 2 );
	while (j < (vars->shape.y + vars->shape.size / 2) && j < vars->y_dim)
	{
		i = (vars->shape.x - vars->shape.size / 2) * (vars->shape.x >= vars->shape.size / 2 );
		while (i < (vars->shape.x + vars->shape.size / 2) && i < vars->x_dim)
		{
			if ((i - vars->shape.x) * (i - vars->shape.x) + (j - vars->shape.y) * (j - vars->shape.y) <= (vars->shape.size / 2) * (vars->shape.size / 2))
				pixel_push(vars, i, j);
			i++;
		}
		j++;
	}
	return (0);
}

int	xpm_paint(t_vars *vars)
{
	int i;
	int j;

	j = (vars->xpm.y_dim / 2 - vars->y_pos) * (vars->xpm.y_dim / 2 > vars->y_pos);
	while (j < vars->xpm.y_dim && j < vars->xpm.y_dim / 2 + vars->y_dim - vars->y_pos)
	{
		i = (vars->xpm.x_dim / 2 - vars->x_pos) * (vars->xpm.x_dim / 2 > vars->x_pos);
		while (i < vars->xpm.x_dim && i < vars->xpm.x_dim / 2 + vars->x_dim - vars->x_pos)
		{
			vars->color = *(unsigned int*)(vars->xpm.addr + (j * vars->xpm.x_dim + i) * vars->xpm.bpp / 8);
			pixel_push(vars, i + vars->x_pos - vars->xpm.x_dim / 2, j + vars->y_pos - vars->xpm.y_dim / 2);
			i++;
		}
		j++;
	}
	return (0);
}


void	pixel_push(t_vars *vars, int x, int y)
{
	char	*dst;

	if (vars->img == 0)
	{
		dst = vars->img0.addr + (y * vars->img0.lnlen + x * (vars->img0.bpp / 8));
		*(unsigned int*)dst = vars->color;
	}
	else if (vars->img == 1 || vars->img == 2)
	{
		dst = vars->img1.addr + (y * vars->img1.lnlen + x * (vars->img1.bpp / 8));
		*(unsigned int*)dst = vars->color;
	}
}

void	copy_img(t_vars *vars)
{
	char		*dst;
	int	x;
	int	y;

	y = 0;
	while (y < vars->y_dim)
	{
		x = 0;
		while (x < vars->x_dim)
		{
			dst = vars->img1.addr + (y * vars->img1.lnlen + x * (vars->img1.bpp / 8));
			*(unsigned int*)dst = *(unsigned int*)(vars->img0.addr + (y * vars->img0.lnlen + x * (vars->img0.bpp / 8)));
			x++;
		}
		y++;
	}
}

int	no_event(t_vars *vars)
{
	
//	static int i = 0;
//	printf("Hello form no_event step %i\n", i++);
//	printf("Showing image %i\n", vars->img);
//	if (vars->img == 0)
//		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img0.ptr, 0, 0);
//	else if (vars->img == 1 || vars->img == 2)
	if (vars->img > 0 && (vars->shape.x_mov != 0 || vars->shape.y_mov != 0))
	{
		copy_img(vars);
		if (vars->shape.type == 's')
			square_paint(vars);
		else if (vars->shape.type == 'c')
			circle_paint(vars);
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img1.ptr, 0, 0);
//	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->xpm.ptr, vars->x_pos, vars->y_pos);

	return (0);
}

int press_button(int button_code, int x, int y, t_vars *vars)
{
//	printf("button_code = %i\n", button_code);
	vars->shape.size += 1 * (button_code == 4) - 1 * (button_code == 5);
	if (button_code == 1 || button_code == 2)
	{
		if (vars->img == 1 || vars->img == 2)
			fix_shape(vars);
		if (button_code == 1)
			vars->shape.type = 'c';
		else if (button_code == 2)
			vars->shape.type = 's';
		vars->img = 1;
		vars->shape.x = x;
		vars->shape.y = y;
	}
	copy_img(vars);
	if (vars->shape.type == 's')
		square_paint(vars);
	else if (vars->shape.type == 'c')
		circle_paint(vars);
	return (0);
}

int move_mouse(int x, int y, t_vars *vars)
{
	vars->x_pos = x;
	vars->y_pos = y;
	if (vars->img == 1)
	{
		copy_img(vars);
		vars->shape.x = x;
		vars->shape.y = y;
		if (vars->shape.type == 's')
			square_paint(vars);
		else if (vars->shape.type == 'c')
			circle_paint(vars);
	}
	return (0);
}

int release_button(int button_code, int x, int y, t_vars *vars)
{
	button_code = 0;
	// vars->img = 0;
	vars->img = 2;
	vars->shape.x = x;
	vars->shape.y = y;
	copy_img(vars);
	if (vars->shape.type == 's')
		square_paint(vars);
	else if (vars->shape.type == 'c')
		circle_paint(vars);
//	copy_img(vars);

	return (0);
}

void	fix_shape(t_vars *vars)
{
	vars->img = 0;
	if (vars->shape.type == 's')
		square_paint(vars);
	else if (vars->shape.type == 'c')
		circle_paint(vars);
	copy_img(vars);
}

void	erase_shape(t_vars *vars)
{
	vars->img = 0;
	copy_img(vars);
}

//int	prueba(int info1, int info2, t_vars *vars)
//{
//	printf("EVENT HOOKED!!!!!!");
//	printf("info1 = %x\n", info1);
//	printf("info2 = %x\n", info2);
//	printf("%p", vars);
//	return (0);
//}

void	shape_init(t_vars *vars)
{
	t_shape		shape;
	
	shape.type = 'c';
	shape.size = 24;
	shape.x = 0;
	shape.y = 0;
	shape.x_mov = 0;
	shape.y_mov = 0;
	vars->shape = shape;
}

int	main(void)
{
	t_vars		vars;
	t_img		img0;
	t_img		img1;

	shape_init(&vars);
	vars.x_dim = 800;
	vars.y_dim = 600;
	vars.color = 0x00ffff00;
	vars.img = 0;
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.x_dim, vars.y_dim, "Movement");
	mlx_hook(vars.win_ptr, 2, 1L<<0, press_key, &vars);
	mlx_hook(vars.win_ptr, 4, 0L, press_button, &vars);
	mlx_hook(vars.win_ptr, 6, 0L, move_mouse, &vars);
	mlx_hook(vars.win_ptr, 5, 0L, release_button, &vars);
	mlx_hook(vars.win_ptr, 3, 1L<<1, release_key, &vars);
//	mlx_hook(vars.win_ptr, 17, 0L, prueba, &vars);

	img0.ptr = mlx_new_image(vars.mlx_ptr, vars.x_dim, vars.y_dim);
	img0.addr = mlx_get_data_addr(img0.ptr, &img0.bpp, &img0.lnlen, &img0.endian);
	img1.ptr = mlx_new_image(vars.mlx_ptr, vars.x_dim, vars.y_dim);
	img1.addr = mlx_get_data_addr(img1.ptr, &img1.bpp, &img1.lnlen, &img1.endian);
	vars.img0 = img0;
	vars.img1 = img1;
	
//	printf("lnlen = %i\n", img.lnlen);
//	pixel_push(&img, 0, 0, 0x00FF0000);
//	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, img.ptr, 0, 0);

	mlx_loop_hook(vars.mlx_ptr, no_event, &vars);
	mlx_loop(vars.mlx_ptr);

	return (0);
}

////	Showing motion images to the window and managing with the keyboard.
////	choose a color (1 to 8 keys), and click over the window with the left or right button.
////	Drag the shape where you want, change its color, move it with the wasd keys.
////	Press 'e' to keep it or 'q' to erase it.
////	Adjust it with the WASD keys, and fix it wiht the E.
//
//typedef struct s_img
//{
//	void		*ptr;
//	char		*addr;
//	int	bpp;
//	int	lnlen;
//	int	endian;
//}			t_img;
//
//typedef struct s_shape
//{
//	char		type;
//	int			x;
//	int			y;
//	int			x_mov;
//	int			y_mov;
//	int			size;
//}			t_shape;
//
//typedef struct s_vars
//{
//	void		*mlx_ptr;
//	void		*win_ptr;
//	t_img		img0;
//	t_img		img1;
//	t_shape		shape;
//	char		img;
//	int			x_dim;
//	int			y_dim;
//	unsigned	color;
//}			t_vars;
//
//int	press_key(int key_code, t_vars *vars);
//void	change_color(int key_color, t_vars *vars);
//int	wasdeq(int key_code, t_vars *vars);
//int	release_key(int key_code, t_vars *vars);
//int	window_area(int key_code, t_vars *vars);
//int	square_paint(t_vars *vars);
//int	circle_paint(t_vars *vars);
//void	fix_shape(t_vars *vars);
//void	erase_shape(t_vars *vars);
//void	pixel_push(t_vars *vars, int x, int y);
//void	copy_img(t_vars *vars);
//
//
//
//int	press_key(int key_code, t_vars *vars)
//{
//	if ((key_code >= 12 && key_code <= 14) || (key_code >= 0 && key_code <= 2))
//		wasdeq(key_code, vars);
//	else if (key_code == 53)
//		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
//	else if ((key_code >= 18 && key_code <= 23) || key_code == 26 || key_code == 28)
//		change_color(key_code, vars);
//	else if ((key_code <= 126 && key_code >= 123) || key_code == 49)
//		window_area(key_code, vars);
//	return (0);
//}
//
//void	change_color(int key_code, t_vars *vars)
//{
//	if (key_code == 28)
//		vars->color = 0x00ffffff;
//	else if (key_code == 18)
//		vars->color = 0x00ff0000;
//	else if (key_code == 19)
//		vars->color = 0x0000ff00;
//	else if (key_code == 20)
//		vars->color = 0x000000ff;
//	else if (key_code == 21)
//		vars->color = 0x0000ffff;
//	else if (key_code == 23)
//		vars->color = 0x00ff00ff;
//	else if (key_code == 22)
//		vars->color = 0x00ffff00;
//	else if (key_code == 26)
//		vars->color = 0x00000000;
//	if (vars->img == 1 || vars->img == 2)
//	{
//		copy_img(vars);
//		if (vars->shape.type == 's')
//			square_paint(vars);
//		else if (vars->shape.type == 'c')
//			circle_paint(vars);
//	}
//}
//
//int	wasdeq(int key_code, t_vars *vars)
//{
//
//	if (key_code == 12)
//	{
//		erase_shape(vars);
//		return (0);
//	}
//	if (vars->img == 2)
//	{
//		if (key_code == 14)
//		{
//			fix_shape(vars);
//			return (0);
//		}
//		else if (key_code == 13)
//			vars->shape.y_mov = -1;
//		else if (key_code == 0)
//			vars->shape.x_mov = -1;
//		else if (key_code == 1)
//			vars->shape.y_mov = 1;
//		else if (key_code == 2)
//			vars->shape.x_mov = 1;
//	}
//	return (0);
//}
//
//int	release_key(int key_code, t_vars *vars)
//{
//	if (key_code == 13)
//		vars->shape.y_mov = 0;
//	else if (key_code == 0)
//		vars->shape.x_mov = 0;
//	else if (key_code == 1)
//		vars->shape.y_mov = 0;
//	else if (key_code == 2)
//		vars->shape.x_mov = 0;
//	return (0);
//}
//
//int	window_area(int key_code, t_vars *vars)
//{
//	short int	x0;
//	short int	x1;
//	short int	y0;
//	short int	y1;
//	short int	i;
//	short int	j;
//
//	vars->img = 0;
//	x0 = 0 +  (vars->x_dim / 2) * (key_code == 124);
//	x1 = vars->x_dim / (1 + (key_code == 123));
//	y0 = 0 +  (vars->y_dim / 2) * (key_code == 125);
//	y1 = vars->y_dim / (1 + (key_code == 126));
//
//	j = y0;
//	while (j < y1)
//	{
//		i = x0;
//		while (i < x1)
//		{
//			pixel_push(vars, i, j);
//			i++;
//		}
//		j++;
//	}
//	copy_img(vars);
//	return (0);
//}
//
//int square_paint(t_vars *vars)
//{
//	int i;
//	int j;
//
//	vars->shape.x += vars->shape.x_mov;
//	vars->shape.y += vars->shape.y_mov;
//	j = (vars->shape.y - vars->shape.size / 2) * (vars->shape.y >= vars->shape.size / 2 );
//	while (j < (vars->shape.y + vars->shape.size / 2) && j < vars->y_dim)
//	{
//		i = (vars->shape.x - vars->shape.size / 2) * (vars->shape.x >= vars->shape.size / 2 );
//		while (i < (vars->shape.x + vars->shape.size / 2) && i < vars->x_dim)
//		{
//			pixel_push(vars, i, j);
//			i++;
//		}
//		j++;
//	}
//	return (0);
//}
//
//int circle_paint(t_vars *vars)
//{
//	int i;
//	int j;
//
//	vars->shape.x += vars->shape.x_mov;
//	vars->shape.y += vars->shape.y_mov;
//	j = (vars->shape.y - vars->shape.size / 2) * (vars->shape.y >= vars->shape.size / 2 );
//	while (j < (vars->shape.y + vars->shape.size / 2) && j < vars->y_dim)
//	{
//		i = (vars->shape.x - vars->shape.size / 2) * (vars->shape.x >= vars->shape.size / 2 );
//		while (i < (vars->shape.x + vars->shape.size / 2) && i < vars->x_dim)
//		{
//			if ((i - vars->shape.x) * (i - vars->shape.x) + (j - vars->shape.y) * (j - vars->shape.y) <= (vars->shape.size / 2) * (vars->shape.size / 2))
//				pixel_push(vars, i, j);
//			i++;
//		}
//		j++;
//	}
//	return (0);
//}
//
//void	pixel_push(t_vars *vars, int x, int y)
//{
//	char	*dst;
//
//	if (vars->img == 0)
//	{
//		dst = vars->img0.addr + (y * vars->img0.lnlen + x * (vars->img0.bpp / 8));
//		*(unsigned int*)dst = vars->color;
//	}
//	else if (vars->img == 1 || vars->img == 2)
//	{
//		dst = vars->img1.addr + (y * vars->img1.lnlen + x * (vars->img1.bpp / 8));
//		*(unsigned int*)dst = vars->color;
//	}
//}
//
//void	copy_img(t_vars *vars)
//{
//	char		*dst;
//	int	x;
//	int	y;
//
//	y = 0;
//	while (y < vars->y_dim)
//	{
//		x = 0;
//		while (x < vars->x_dim)
//		{
//			dst = vars->img1.addr + (y * vars->img1.lnlen + x * (vars->img1.bpp / 8));
//			*(unsigned int*)dst = *(unsigned int*)(vars->img0.addr + (y * vars->img0.lnlen + x * (vars->img0.bpp / 8)));
//			x++;
//		}
//		y++;
//	}
//}
//
//int	no_event(t_vars *vars)
//{
//	if (vars->img > 0 && (vars->shape.x_mov != 0 || vars->shape.y_mov != 0))
//	{
//		copy_img(vars);
//		if (vars->shape.type == 's')
//			square_paint(vars);
//		else if (vars->shape.type == 'c')
//			circle_paint(vars);
//	}
//	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img1.ptr, 0, 0);
//
//	return (0);
//}
//
//int press_button(int button_code, int x, int y, t_vars *vars)
//{
//	vars->shape.size += 1 * (button_code == 4) - 1 * (button_code == 5);
//	if (button_code == 1 || button_code == 2)
//	{
//		if (vars->img == 1 || vars->img == 2)
//			fix_shape(vars);
//		if (button_code == 1)
//			vars->shape.type = 'c';
//		else if (button_code == 2)
//			vars->shape.type = 's';
//		vars->img = 1;
//		vars->shape.x = x;
//		vars->shape.y = y;
//	}
//	copy_img(vars);
//	if (vars->shape.type == 's')
//		square_paint(vars);
//	else if (vars->shape.type == 'c')
//		circle_paint(vars);
//	return (0);
//}
//
//int move_mouse(int x, int y, t_vars *vars)
//{
//	if (vars->img == 1)
//	{
//		copy_img(vars);
//		vars->shape.x = x;
//		vars->shape.y = y;
//		if (vars->shape.type == 's')
//			square_paint(vars);
//		else if (vars->shape.type == 'c')
//			circle_paint(vars);
//	}
//	return (0);
//}
//
//int release_button(int button_code, int x, int y, t_vars *vars)
//{
//	button_code = 0;
//	vars->img = 2;
//	vars->shape.x = x;
//	vars->shape.y = y;
//	copy_img(vars);
//	if (vars->shape.type == 's')
//		square_paint(vars);
//	else if (vars->shape.type == 'c')
//		circle_paint(vars);
//	return (0);
//}
//
//void	fix_shape(t_vars *vars)
//{
//	vars->img = 0;
//	if (vars->shape.type == 's')
//		square_paint(vars);
//	else if (vars->shape.type == 'c')
//		circle_paint(vars);
//	copy_img(vars);
//}
//
//void	erase_shape(t_vars *vars)
//{
//	vars->img = 0;
//	copy_img(vars);
//}
//
//void	shape_init(t_vars *vars)
//{
//	t_shape		shape;
//	
//	shape.type = 'c';
//	shape.size = 24;
//	shape.x = 0;
//	shape.y = 0;
//	shape.x_mov = 0;
//	shape.y_mov = 0;
//	vars->shape = shape;
//}
//
//int	main(void)
//{
//	t_vars		vars;
//	t_img		img0;
//	t_img		img1;
//
//	shape_init(&vars);
//	vars.x_dim = 800;
//	vars.y_dim = 600;
//	vars.color = 0;
//	vars.img = 0;
//	vars.mlx_ptr = mlx_init();
//	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.x_dim, vars.y_dim, "Movement");
//	mlx_hook(vars.win_ptr, 2, 1L<<0, press_key, &vars);
//	mlx_hook(vars.win_ptr, 4, 0L, press_button, &vars);
//	mlx_hook(vars.win_ptr, 6, 0L, move_mouse, &vars);
//	mlx_hook(vars.win_ptr, 5, 0L, release_button, &vars);
//	mlx_hook(vars.win_ptr, 3, 1L<<1, release_key, &vars);
//
//	img0.ptr = mlx_new_image(vars.mlx_ptr, vars.x_dim, vars.y_dim);
//	img0.addr = mlx_get_data_addr(img0.ptr, &img0.bpp, &img0.lnlen, &img0.endian);
//	img1.ptr = mlx_new_image(vars.mlx_ptr, vars.x_dim, vars.y_dim);
//	img1.addr = mlx_get_data_addr(img1.ptr, &img1.bpp, &img1.lnlen, &img1.endian);
//	vars.img0 = img0;
//	vars.img1 = img1;
//	
//	mlx_loop_hook(vars.mlx_ptr, no_event, &vars);
//	mlx_loop(vars.mlx_ptr);
//
//	return (0);
//}


////	Sending motion images to the window
////	choose a color (1 to 8 keys), and click over the window.
////	Drag the square where you want it to stay and release the button.
//
//typedef struct s_img
//{
//	void		*ptr;
//	char		*addr;
//	int			bpp;
//	int			lnlen;
//	int			endian;
//}			t_img;
//
//typedef struct s_vars
//{
//	void		*mlx_ptr;
//	void		*win_ptr;
//	t_img		img1;
//	t_img		img2;
//	int			img;
//	int			x_dim;
//	int			y_dim;
//	unsigned	color;
//}			t_vars;
//
//typedef struct s_square
//{
//	int			x0;
//	int			x1;
//	int			y0;
//	int			y1;
//}			t_square;
//
//int	press_key(int key_code, t_vars *vars);
//int	window_area(int key_code, t_vars *vars);
//int	square_paint(t_square sq, t_vars *vars);
//void	pixel_push(t_vars *vars, int x, int y);
//
//
//int	press_key(int key_code, t_vars *vars)
//{
//	if (key_code == 53)
//		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
//	else if (key_code == 28)
//		vars->color = 0x00ffffff;
//	else if (key_code == 18)
//		vars->color = 0x00ff0000;
//	else if (key_code == 19)
//		vars->color = 0x0000ff00;
//	else if (key_code == 20)
//		vars->color = 0x000000ff;
//	else if (key_code == 21)
//		vars->color = 0x0000ffff;
//	else if (key_code == 23)
//		vars->color = 0x00ff00ff;
//	else if (key_code == 22)
//		vars->color = 0x00ffff00;
//	else if (key_code == 26)
//		vars->color = 0x00000000;
//	else if ((key_code <= 126 && key_code >= 123) || key_code == 49)
//		window_area(key_code, vars);
//	return (0);
//}
//int	window_area(int key_code, t_vars *vars)
//{
//	t_square area;
//
//	area.x0 = 0 +  (vars->x_dim / 2) * (key_code == 124);
//	area.x1 = vars->x_dim / (1 + (key_code == 123));
//	area.y0 = 0 +  (vars->y_dim / 2) * (key_code == 125);
//	area.y1 = vars->y_dim / (1 + (key_code == 126));
//	square_paint(area, vars);
//	return (0);
//}
//
//int square_paint(t_square sq, t_vars *vars)
//{
//	int i;
//	int j;
//
//	j = sq.y0;
//	while (j < sq.y1)
//	{
//		i = sq.x0;
//		while (i < sq.x1)
//		{
//			pixel_push(vars, i, j);
//			i++;
//		}
//		j++;
//	}
//	return (0);
//}
//
//void	pixel_push(t_vars *vars, int x, int y)
//{
//	char	*dst;
//
//	if (vars->img == 1)
//	{
//		dst = vars->img1.addr + (y * vars->img1.lnlen + x * (vars->img1.bpp / 8));
//		*(unsigned int*)dst = vars->color;
//	}
//	else if (vars->img == 2)
//	{
//		dst = vars->img2.addr + (y * vars->img2.lnlen + x * (vars->img2.bpp / 8));
//		*(unsigned int*)dst = vars->color;
//	}
//}
//
//void	copy_img(t_vars *vars)
//{
//	char	*dst;
//	int		x;
//	int		y;
//
//	y = 0;
//	while (y < vars->y_dim)
//	{
//		x = 0;
//		while (x < vars->x_dim)
//		{
//			dst = vars->img2.addr + (y * vars->img2.lnlen + x * (vars->img2.bpp / 8));
//			*(unsigned int*)dst = *(unsigned int*)(vars->img1.addr + (y * vars->img1.lnlen + x * (vars->img1.bpp / 8)));
//			x++;
//		}
//		y++;
//	}
//}
//
//int	no_event(t_vars *vars)
//{
//	if (vars->img == 1)
//		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img1.ptr, 0, 0);
//	else if (vars->img == 2)
//		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img2.ptr, 0, 0);
//
//	return (0);
//}
//
//int press_button(int button_code, int x, int y, t_vars *vars)
//{
//	t_square	sq;
//	int size;
//	//	Just for using the variables:
//	size = button_code + x + y + vars->color;
//	vars->img = 2;
//	copy_img(vars);
//	size = 24;
//	sq.x0 = x - size / 2;
//	sq.x1 = sq.x0 + size;
//	sq.y0 = y - size / 2;
//	sq.y1 = sq.y0 + size;
//	square_paint(sq, vars);
//	return (0);
//}
//
//int move_mouse(int x, int y, t_vars *vars)
//{
//	t_square	sq;
//	int			size;
//
//	if (vars->img == 2)
//	{
//		copy_img(vars);
//		size = 24;
//		sq.x0 = x - size / 2;
//		sq.x1 = sq.x0 + size;
//		sq.y0 = y - size / 2;
//		sq.y1 = sq.y0 + size;
//		square_paint(sq, vars);
//	}
//	return (0);
//}
//
//int release_button(int button_code, int x, int y, t_vars *vars)
//{
//	t_square	sq;
//	int			size;
//
//	vars->img = 1;
//	size = 24 * button_code;
//	sq.x0 = x - size / 2;
//	sq.x1 = sq.x0 + size;
//	sq.y0 = y - size / 2;
//	sq.y1 = sq.y0 + size;
//	square_paint(sq, vars);
//	copy_img(vars);
//
//	return (0);
//}
//
//int		main(void)
//{
//	t_vars	vars;
//	t_img	img1;
//	t_img	img2;
//
//	vars.x_dim = 800;
//	vars.y_dim = 600;
//	vars.color = 0;
//	vars.mlx_ptr = mlx_init();
//	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.x_dim, vars.y_dim, "Movement");
//	mlx_hook(vars.win_ptr, 2, 1L<<0, press_key, &vars);
//	mlx_hook(vars.win_ptr, 4, 0L, press_button, &vars);
//	mlx_hook(vars.win_ptr, 6, 0L, move_mouse, &vars);
//	mlx_hook(vars.win_ptr, 5, 0L, release_button, &vars);
//	img1.ptr = mlx_new_image(vars.mlx_ptr, vars.x_dim, vars.y_dim);
//	img1.addr = mlx_get_data_addr(img1.ptr, &img1.bpp, &img1.lnlen, &img1.endian);
//	img2.ptr = mlx_new_image(vars.mlx_ptr, vars.x_dim, vars.y_dim);
//	img2.addr = mlx_get_data_addr(img2.ptr, &img2.bpp, &img2.lnlen, &img2.endian);
//	vars.img1 = img1;
//	vars.img2 = img2;
//	mlx_loop_hook(vars.mlx_ptr, no_event, &vars);
//	mlx_loop(vars.mlx_ptr);
//
//	return (0);
//}


//// Sending static images to the window
//// Choose the color to send (rgb cmyk w) with the letter key, and press a direction arrow or space key to send it.
//
//typedef struct s_img
//{
//	void		*ptr;
//	char		*addr;
//	int			bpp;
//	int			lnlen;
//	int			endian;
//}			t_img;
//
//typedef struct s_vars
//{
//	void		*mlx_ptr;
//	void		*win_ptr;
//	t_img		img;
//	int			x_dim;
//	int			y_dim;
//	unsigned	color;
//}			t_vars;
//
//typedef struct s_square
//{
//	int			x0;
//	int			x1;
//	int			y0;
//	int			y1;
//}			t_square;
//
//int	press_key(int key_code, t_vars *vars);
//int	window_area(int key_code, t_vars *vars);
//int	square_paint(t_square sq, t_vars *vars);
//void	pixel_push(t_vars *vars, int x, int y);
//
//
//int	press_key(int key_code, t_vars *vars)
//{
//	if (key_code == 53)
//		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
//	else if (key_code == 13)
//		vars->color = 0x00ffffff;
//	else if (key_code == 15)
//		vars->color = 0x00ff0000;
//	else if (key_code == 5)
//		vars->color = 0x0000ff00;
//	else if (key_code == 11)
//		vars->color = 0x000000ff;
//	else if (key_code == 8)
//		vars->color = 0x0000ffff;
//	else if (key_code == 46)
//		vars->color = 0x00ff00ff;
//	else if (key_code == 16)
//		vars->color = 0x00ffff00;
//	else if (key_code == 40)
//		vars->color = 0x00000000;
//	else if ((key_code <= 126 && key_code >= 123) || key_code == 49)
//		window_area(key_code, vars);
//	return (0);
//}
//
//
//int	window_area(int key_code, t_vars *vars)
//{
//	t_square area;
//
//	area.x0 = 0 +  (vars->x_dim / 2) * (key_code == 124);
//	area.x1 = vars->x_dim / (1 + (key_code == 123));
//	area.y0 = 0 +  (vars->y_dim / 2) * (key_code == 125);
//	area.y1 = vars->y_dim / (1 + (key_code == 126));
//	square_paint(area, vars);
//	return (0);
//}
//
//int square_paint(t_square sq, t_vars *vars)
//{
//	int i;
//	int j;
//
//	j = sq.y0;
//	while (j < sq.y1)
//	{
//		i = sq.x0;
//		while (i < sq.x1)
//		{
//			pixel_push(vars, i, j);
//			i++;
//		}
//		j++;
//	}
//	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img.ptr, 0, 0);
//	return (0);
//}
//
//void	pixel_push(t_vars *vars, int x, int y)
//{
//	char	*dst;
//
//	dst = vars->img.addr + (y * vars->img.lnlen + x * (vars->img.bpp / 8));
//	*(unsigned int*)dst = vars->color;
//}
//
//int		main(void)
//{
//	t_vars	vars;
//	t_img	img;
//
//	vars.x_dim = 800;
//	vars.y_dim = 600;
//	vars.color = 0;
//	vars.mlx_ptr = mlx_init();
//	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.x_dim, vars.y_dim, "Movement");
//	mlx_hook(vars.win_ptr, 2, 1L<<0, press_key, &vars);
//
//	img.ptr = mlx_new_image(vars.mlx_ptr, vars.x_dim, vars.y_dim);
//	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.lnlen, &img.endian);
//	vars.img = img;
//
//	mlx_loop(vars.mlx_ptr);
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


//// Hook
//
//typedef struct s_vars
//{
//	void	*mlx_ptr;
//	void	*win_ptr;
//}			t_vars;
//
//int destroy_notify(int info1, t_vars *vars);
//
//int		key_hook(int keycode, t_vars *vars)
//{
//	printf("Hello from key_hook!\n");
//	printf("Keycode = %i\n", keycode);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int	mouse_click_hook(int button, int posx, int posy, t_vars *vars)
//{
//	printf("Hello from mouse_hook!\n");
//	printf("button = %i\n", button);
//	printf("posx = %i\n", posx);
//	printf("posy = %i\n", posy);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int press_key(int key_code, int info2, t_vars *vars)
//{
//	printf("Hello from press_key\n");
//	printf("key_code = %i\n", key_code);
//	printf("info2 = %i\n", info2);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	if (key_code == 53)
//		{
//			destroy_notify(key_code, vars);
//			mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
//		}
//	return (0);
//}
//
//int release_key(int key_code, int info2, t_vars *vars)
//{
//	printf("Hello from release_key\n");
//	printf("key_code = %i\n", key_code);
//	printf("info2 = %i\n", info2);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int button_press(int button_code, int pos_x, int pos_y, int info4, //t_vars *vars)
//{
//	printf("Hello from button_press\n");
//	printf("button_code = %i\n", button_code);
//	printf("pos_x = %i\n", pos_x);
//	printf("pos_y = %i\n", pos_y);
//	printf("info4 = %i\n", info4);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//int button_release(int button_code, int pos_x, int pos_y, int //info4, t_vars *vars)
//{
//	printf("Hello from button_release\n");
//	printf("button_code = %i\n", button_code);
//	printf("pos_x = %i\n", pos_x);
//	printf("pos_y = %i\n", pos_y);
//	printf("info4 = %i\n", info4);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int motion_notify(int pos_x, int pos_y, int info3, t_vars *vars)
//{
//	printf("Hello from motion_notify\n");
//	printf("pos_x = %i\n", pos_x);
//	printf("pos_y = %i\n", pos_y);
//	printf("info4 = %i\n", info3);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int destroy_notify(int key_code, t_vars *vars)
//{
//	printf("Hello from destroy_notify\n");
//	printf("key_code = %i\n", key_code);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int enter_window(int pos_x, int pos_y, t_vars *vars)
//{
//	printf("Hello from enter_window\n");
//	printf("pos_x = %i\n", pos_x);
//	printf("pos_y = %i\n", pos_y);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int exit_window(int pos_x, int pos_y, t_vars *vars)
//{
//	printf("Hello from exit_window\n");
//	printf("pos_x = %i\n", pos_x);
//	printf("pos_y = %i\n", pos_y);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int	trying_expose(int info1, int info2, t_vars *vars)
//{
//	printf("Hello from trying_expose\n");
//	printf("pos_x = %i\n", info1);
//	printf("pos_y = %i\n", info2);
//	printf("win_ptr = %p\n", vars->win_ptr);
//	return (0);
//}
//
//int		main(void)
//{
//	t_vars	vars;
//
//	vars.mlx_ptr = mlx_init();
//	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 800, 600, "Hooks");
////	mlx_key_hook(vars.win_ptr, key_hook, &vars);
////	mlx_mouse_hook(vars.win_ptr, mouse_click_hook, &vars);
//	mlx_expose_hook (vars.win_ptr, trying_expose,  &vars);
////	mlx_hook(vars.win_ptr, 2, 1L<<0, press_key, &vars);
////	mlx_hook(vars.win_ptr, 3, 1L<<1, release_key, &vars);
////	mlx_hook(vars.win_ptr, 4, 1L<<2, button_press, &vars);
////	mlx_hook(vars.win_ptr, 5, 1L<<3, button_release, &vars);
////	mlx_hook(vars.win_ptr, 6, 1L<<6, motion_notify, &vars);
////	mlx_hook(vars.win_ptr, 17, 0L, destroy_notify, &vars);
//	mlx_hook(vars.win_ptr, 7, 1L<<4, enter_window, &vars);
//	mlx_hook(vars.win_ptr, 8, 1L<<5, exit_window, &vars);
//	mlx_loop(vars.mlx_ptr);
//
//	return (0);
//}

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
