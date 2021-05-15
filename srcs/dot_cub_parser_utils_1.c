/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:46:08 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/15 17:24:16 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where the .cub file elements become variables on
**	the mlx structure.
*/

#include "../cub3d.h"

/*
**	Checks whether the strings of the array are numbers.
*/

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

/*
**	Stores the indicated size of the mlx window, always within certain limits.
*/

int	window_sizer(t_mlx *mlx, char **elem)
{
	int		maxw;
	int		maxh;
	char	i;

	if (arenum(elem, 'r') == 2)
		return (2);
	maxw = 5120 / 2;
	maxh = 2880 / 2 - 28;
	i = 0;
	while (elem[1][i] == '0')
		i++;
	mlx->winw = ft_atoi(elem[1]);
	mlx->winw = (mlx->winw < 0 || ft_strlen(&elem[1][i]) > 9) * maxw
	+ (mlx->winw > 0) * mlx->winw;
	if (mlx->argc == 2)
		mlx->winw = (mlx->winw > maxw) * maxw + (mlx->winw <= maxw) * mlx->winw;
	i = 0;
	while (elem[2][i] == '0')
		i++;
	mlx->winh = ft_atoi(elem[2]);
	mlx->winh = (mlx->winh < 0 || ft_strlen(&elem[2][i]) > 9) * maxh
	+ (mlx->winh > 0) * mlx->winh;
	if (mlx->argc == 2)
		mlx->winh = (mlx->winh > maxh) * maxh + (mlx->winh <= maxh) * mlx->winh;
	return (1);
}

/*
**	It compose a color in RGB format, from a sting of three digits
**	separated by ','.
*/

int get_color(char *rgb_components, int *color)
{
	char	**r_g_b;
	char	i;
	int		this_comp;

	r_g_b = ft_split(rgb_components, ',');
	if (arenum(r_g_b, 'c') == 2)
		return (free_split(2, r_g_b));
	i = 0;
	while (i < 3)
	{
		this_comp = atoi(r_g_b[i]);
		if (this_comp > 255)
		{
			free (rgb_components);
			rgb_components = NULL;
			return (free_split(msnprt(2, "Wrong color component"), r_g_b));
		}
		*color += this_comp << (8 * (2 - i++));
	}
	return (free_split(1, r_g_b));
}

/*
**	Gets all the possible pieces after spliting the rgb element, and get them
**	back into one, to ease the parsing.
*/

int	recompose_rgb(char **elem, char *rgb_components)
{
	int	i;
	int	j;
	int	k;

	j = 1;
	k = 0;
	while (elem[j])
	{
		i = 0;
		while (elem[j][i] && k <= 12)
			rgb_components[k++] = elem[j][i++];
		if (k > 12)
		{
			free (rgb_components);
			rgb_components = NULL;
			return (2);
		}
		j++;
	}
	return (1);
}

/*
**	Manages the color for the ceiling and the floor.
**	Checks the color format, orders to compose it, and stores it
**	either for the ceiling or the floor.
*/

int	colorizer(t_mlx *mlx, char **elem)
{
	int		color;
	char	*rgb_components;

	rgb_components = ft_calloc(sizeof(char), 12);
	if (!rgb_components)
		return (msnprt(2, "Error with malloc while colorizer"));
	if (recompose_rgb(elem, rgb_components) == 2)
		return(msnprt(2, "Wrong color format"));
	color = 0;
	if (ft_wordcount(rgb_components, ',') != 3)
		return (msnprt(2, "Wrong color format"));
	if (get_color(rgb_components, &color) == 2)
		return (2);
	free (rgb_components);
	rgb_components = NULL;
	if (elem[0][0] == 'C')
		mlx->set.c = color;
	else
		mlx->set.f = color;
	return (1);
}
