/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:46:08 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 19:57:54 by jpizarro         ###   ########.fr       */
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
	short int	i;
	short int	j;

	j = 3;
	if (k == 'r')
	{
		while (--j)
		{
			i = 0;
			while (elem[j][i])
				if (!(ft_isdigit(elem[j][i++])))
					return (msnprt(2, "Invalid window resolution number"));
		}
	}
	else
	{
		while (!(--j < 0))
		{
			i = 0;
			while (elem[j][i])
				if (!(ft_isdigit(elem[j][i++])))
					return (msnprt(2, "Invalid color component"));
		}
	}
	return (1);
}

/*
**	Gets rid of all the caracters 'c' in 'str'.
**	Returns the new lenth of 'str' or -1 if has been an error.
*/

int	erase_char(char *str, char c)
{
	int	i;
	int	j;

	if (!str)
		return (-1);
	i = ft_charindex(str, c);
	if (i < 0)
		return (ft_strlen(str));
	j = i;
	while (str[j])
		if (str[j++] != c)
			str[i++] = str[j - 1];
	str[i] = 0;
	return (i);
}

/*
**	Composes an RGB format color from a split of three components on strings.
*/

int	compose_color(char **rgb)
{
	int	i;
	int	j;
	int	comp;
	int	color;

	i = 3;
	color = 0;
	while (i--)
	{
		j = 0;
		while (rgb[i][j] == '0')
			j++;
		comp = atoi(rgb[i]);
		if (ft_strlen(&rgb[i][j]) >= 4 || comp > 255)
			return (-1);
		color += comp << (8 * (2 - i));
	}
	return (color);
}

/*
**	
*/

int	colorizer(t_mlx *mlx, char place, char **elem)
{
	int	i;
	int	color;

	i = 3;
	while (i--)
		if (erase_char(elem[i], ' ') < 0)
			return (free_split(msnprt(2, "Color component missing"), elem));
	if (arenum(elem, 'c') == 2)
		return (free_split(2, elem));
	color = compose_color(elem);
	if (color < 0)
		return (free_split(msnprt(2, "Invalid color component"), elem));
	if (place == 'C')
		mlx->set.c = color;
	else
		mlx->set.f = color;
	return (free_split(1, elem));
}
