/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 08:08:41 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/09 12:39:57 by jpizarro         ###   ########.fr       */
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

void	paint_line(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->rc.color = 0;
	while (i < (mlx->winh - mlx->rc.lnh) / 2)
	{
		pixel_push(mlx, mlx->rc.line, i);
		pixel_push(mlx, mlx->rc.line, mlx->winh - i);
		i++;
	}
	mlx->rc.color = 0x00ffff00 - 0x00555500 * (mlx->rc.face == 'w' || mlx->rc.face == 'e'); 
	while (i <= mlx->winh / 2)
	{
		pixel_push(mlx, mlx->rc.line, i);
		pixel_push(mlx, mlx->rc.line, mlx->winh - i);
		i++;
	}
}
