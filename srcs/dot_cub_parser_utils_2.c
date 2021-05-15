/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:46:08 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/15 16:42:40 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where the .cub file elements become variables on
**	the mlx structure.
*/

#include "../cub3d.h"

/*
**	Receives the info for the textures, where to use them and the path
**	to the 'xpm' file. Checks for the correct format of the image, and
**	stores it on the corresponding variable of the mlx structure.
*/

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
		mlx->set.pathn = ft_strdup(elem[1]);
	else if (elem[0][0] == 'S' && elem[0][1] == 'O')
		mlx->set.paths = ft_strdup(elem[1]);
	else if (elem[0][0] == 'E')
		mlx->set.pathe = ft_strdup(elem[1]);
	else if (elem[0][0] == 'W')
		mlx->set.pathw = ft_strdup(elem[1]);
	else if (elem[0][0] == 'S')
		mlx->set.pathp = ft_strdup(elem[1]);
	return (1);
}
