/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmapper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:01:18 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/14 23:07:49 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here is where all the .bmp file creation stuff is.
*/

#include "../cub3d.h"

/*
**	Inverts the bytes of an int and stores them in a string.
*/

void	int_to_str(unsigned char *str, int num)
{
	str[0] = (unsigned char)num;
	str[1] = (unsigned char)(num >> 8);
	str[2] = (unsigned char)(num >> 16);
	str[3] = (unsigned char)(num >> 24);
}

/*
**	With the image info, creates the bmp header portion, and writes it to the
**	bmp file.
*/

void	write_bmp_header(t_mlx *mlx, int fd)
{
	unsigned char	bmp_header[14];
	int	bmp_size;

	bmp_size = mlx->winw * mlx->winh * mlx->img.bpp / 8 + 54;
	ft_bzero(bmp_header, 14);
	ft_memcpy(&bmp_header[0], "BM", 2);
	int_to_str(&bmp_header[2], bmp_size);
	int_to_str(&bmp_header[10], 54);
	if (write(fd, bmp_header, 14) < 0)
		mlx->err = 2;
}

/*
**	With the image info, creates the dib header portion, and writes it to the
**	bmp file.
*/

void	write_dib_header(t_mlx *mlx, int fd)
{
	unsigned char	dib_header[40];

	ft_bzero(dib_header, 40);
	int_to_str(&dib_header[0], 40);
	int_to_str(&dib_header[4],mlx->winw);
	int_to_str(&dib_header[8],mlx->winh);
	dib_header[12] = (unsigned char)(1);
	dib_header[14] = (unsigned char)mlx->img.bpp;
	if (write(fd, dib_header, 40) < 0)
		mlx->err = 2;
}

/*
**	Inverts the pixels of the image and stores them into the bmp file.
*/

void	write_pixels_to_bmp(t_mlx *mlx, int fd)
{
	int i;

	i = mlx->winw * mlx->winh;
	while(i-- > 0)
		if (write(fd, &mlx->img.addr[i * mlx->img.bpp / 8],
		mlx->img.bpp / 8) < 0)
		{
			mlx->err = 2;
			return;
		}
}
