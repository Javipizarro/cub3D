/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:46:08 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/25 21:09:07 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where the .cub file elements become variables on
**	the mlx structure.
*/

#include "../cub3d.h"

int	arenum(char **elem, char k)
{
	char cnt[2];
	
	cnt[0] = 2;
	if (k == 'r')
		while (cnt[0])
		{
			cnt[1] = 0;
			while (elem[cnt[0]][cnt[1]])
				if (!(ft_isdigit(elem[cnt[0]][cnt[1]++])))
					return (msnprt(2, "Invalid screen resolution"));
			cnt[0]--;
		}
	else
		while (!(cnt[0] < 0))
		{
			cnt[1] = 0;
			while (elem[cnt[0]][cnt[1]])
				if (!(ft_isdigit(elem[cnt[0]][cnt[1]++])))
					return (msnprt(2, "Invalid color component"));
			cnt[0]--;
		}
	return (1);
}

int	window_sizer(t_mlx *mlx, char **elem)
{
	int		maxw;
	int		maxh;
	int		minw;
	int		minh;
	char	i;

	if (arenum(elem, 'r') == 2)
		return (2);
	maxw = 5120;
	maxh = 2880;
	minw = 400;
	minh = 300;
	mlx->winw = ft_atoi(elem[1]);
	mlx->winw = (mlx->winw > maxw) * maxw + (mlx->winw <= maxw) * mlx->winw;
	mlx->winw = (mlx->winw < minw) * minw + (mlx->winw >= minw) * mlx->winw;
	mlx->winh = ft_atoi(elem[2]);
	mlx->winh = (mlx->winh > maxh) * maxh + (mlx->winh <= maxh) * mlx->winh;
	mlx->winh = (mlx->winh < minh) * minh + (mlx->winh >= minh) * mlx->winh;
	return (1);
}

int	texturizer(t_mlx *mlx, char **elem)
{
	int	i;

	i = 0;
	while (elem[1][i])
		i++;
	i -= 4;
	if (!(i > 0 && elem[1][i] == '.' && elem[1][++i] == 'x'
		&& elem[1][++i] == 'p' &&  elem[1][++i] == 'm'))
		return (msnprt(2, "Invalid texture file, only .xpm files are allowed"));
	if (elem[0][0] == 'N')
		mlx->set.pathn = elem[1];
	else if (elem[0][0] == 'S' && elem[0][1] == 'O')
		mlx->set.paths = elem[1];
	else if (elem[0][0] == 'E')
		mlx->set.pathe = elem[1];
	else if (elem[0][0] == 'W')
		mlx->set.pathw = elem[1];
	else if (elem[0][0] == 'S')
		mlx->set.pathp = elem[1];
	return (1);
}

int get_color(char **elem, int *color)
{
	char	**r_g_b;
	char	i;
	int		comp;

	r_g_b = ft_split(elem[1], ',');
	if (arenum(r_g_b, 'c') == 2)
		return (2);
	i = 0;
	while (i < 3)
	{
		comp = atoi(r_g_b[i]);
		if (comp > 255)
			return (msnprt(2, "Wrong color component"));
		*color += comp << (8 * (2 - i++));
	}
	return (1);

}

int	colorizer(t_mlx *mlx, char **elem)
{
	int				color;

	color = 0;
	if (ft_wordcount(elem[1], ',') == 3)
	{
		if (get_color(elem, &color) == 2)
			return (2);
		if (elem[0][0] == 'C')
			mlx->set.c = color;
		else
			mlx->set.f = color;
		return (1);	
	}
	return (msnprt(2, "Wrong color format"));
}
