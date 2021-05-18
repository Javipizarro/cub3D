/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:46:08 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 10:59:11 by jpizarro         ###   ########.fr       */
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
	
	j = 2;
	if (k == 'r')
		while (j)
		{
			i = 0;
			while (elem[j][i])
				if (!(ft_isdigit(elem[j][i++])))
					return (msnprt(2, "Invalid window resolution number"));
			j--;
		}
	else
		while (!(j < 0))
		{
			i = 0;
			while (elem[j][i])
				if (!(ft_isdigit(elem[j][i++])))
					return (msnprt(2, "Invalid color component"));
			j--;
		}
	return (1);
}

/*
**	Gets rid of all the caracters 'c' in 'str'.
**	Returns the new lenth of 'str' or -1 if no changes have been made.
*/

int	erase_char(char *str, char c)
{
	int	i;
	int	j;

	i = ft_charindex(str, c);
	if (i < 0)
		return (i);
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
	int j;
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
		color += comp << (8 * i);
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
		erase_char(elem[i], ' ');
	if (arenum(elem, 'c') == 2)
		return (free_split(2, elem));
	color = compose_color(elem);
	if (color < 0)
		return (free_split(msnprt(2, "Invalid color component"), elem));
	if (place == 'C')
		mlx->set.c = color;
	else
		mlx->set.f = color;
	return(free_split(1, elem));
}


///*
//**	It compose a color in RGB format, from a sting of three digits
//**	separated by ','.
//*/
//
//int get_color(char *rgb_components, int *color)
//{
//	char	**r_g_b;
//	char	i;
//	int		this_comp;
//
//	r_g_b = ft_split(rgb_components, ',');
//	if (arenum(r_g_b, 'c') == 2)
//		return (free_split(2, r_g_b));
//	i = 0;
//	while (i < 3)
//	{
//		this_comp = atoi(r_g_b[i]);
//		if (this_comp > 255)
//		{
//			free (rgb_components);
//			rgb_components = NULL;
//			return (free_split(msnprt(2, "Wrong color component"), r_g_b));
//		}
//		*color += this_comp << (8 * (2 - i++));
//	}
//	return (free_split(1, r_g_b));
//}
//
///*
//**	Gets all the possible pieces after spliting the rgb element, and get them
//**	back into one, to ease the parsing.
//*/
//
//int	recompose_rgb(char **elem, char *rgb_components)
//{
//	int	i;
//	int	j;
//	int	k;
//
//	j = 1;
//	k = 0;
//	while (elem[j])
//	{
//		i = 0;
//		while (elem[j][i] && k <= 12)
//			rgb_components[k++] = elem[j][i++];
//		if (k > 12)
//		{
//			free (rgb_components);
//			rgb_components = NULL;
//			return (2);
//		}
//		j++;
//	}
//	return (1);
//}
//
///*
//**	Manages the color for the ceiling and the floor.
//**	Checks the color format, orders to compose it, and stores it
//**	either for the ceiling or the floor.
//*/
//
//int	colorizer(t_mlx *mlx, char **elem)
//{
//	int		color;
//	char	*rgb_components;
//
//	rgb_components = ft_calloc(sizeof(char), 12);
//	if (!rgb_components)
//		return (msnprt(2, "Error with malloc while colorizer"));
//	if (recompose_rgb(elem, rgb_components) == 2)
//		return(msnprt(2, "Wrong color format"));
//	color = 0;
//	if (ft_wordcount(rgb_components, ',') != 3)
//		return (msnprt(2, "Wrong color format"));
//	if (get_color(rgb_components, &color) == 2)
//		return (2);
//	free (rgb_components);
//	rgb_components = NULL;
//	if (elem[0][0] == 'C')
//		mlx->set.c = color;
//	else
//		mlx->set.f = color;
//	return (1);
//}
//