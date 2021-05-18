/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:46:08 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/16 09:54:10 by jpizarro         ###   ########.fr       */
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

int	texturizer(t_mlx *mlx, char *line)
{
	char *path;
	int	i;

	i = ft_charindex(line, ' ');
	while (line[i] == ' ')
		i++;
	path = &line[i];
	i = ft_strlen(path);
	while (path[--i] == ' ')
		path[i] = 0;
	if (i < 5 || ft_strncmp(&path[i - 3], ".xpm", 4))
		return (msnprt(2, "Invalid texture file, only .xpm files are allowed"));
	if (!ft_strncmp(line, "NO", 2))
		mlx->set.pathn = ft_strdup(path);
	else if (!ft_strncmp(line, "SO", 2))
		mlx->set.paths = ft_strdup(path);
	else if (!ft_strncmp(line, "EA", 2))
		mlx->set.pathe = ft_strdup(path);
	else if (!ft_strncmp(line, "WE", 2))
		mlx->set.pathw = ft_strdup(path);
	else if (!ft_strncmp(line, "S ", 2))
		mlx->set.paths1 = ft_strdup(path);
	return (1);
}

/*
**	Stores the indicated size of the mlx window, always within certain limits.
*/

int	window_sizer(t_mlx *mlx, char **elem)
{
	int		maxw;
	int		maxh;
	int		i;

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
	return (free_split(1, elem));
}

///*
//**	Stores the windows size within the limits if it is for a game-play window.
//*/
//
//void	store_window_dimensions(t_mlx *mlx, int maxw, int maxh, char **elem)
//{
//	int		i;
//
//	i = 0;
//	while (elem[1][i] == '0')
//		i++;
//	mlx->winw = ft_atoi(elem[1]);
//	mlx->winw = (mlx->winw < 0 || ft_strlen(&elem[1][i]) > 9) * maxw
//	+ (mlx->winw > 0) * mlx->winw;
//	if (mlx->argc == 2)
//		mlx->winw = (mlx->winw > maxw) * maxw + (mlx->winw <= maxw) * mlx->winw;
//	i = 0;
//	while (elem[2][i] == '0')
//		i++;
//	mlx->winh = ft_atoi(elem[2]);
//	mlx->winh = (mlx->winh < 0 || ft_strlen(&elem[2][i]) > 9) * maxh
//	+ (mlx->winh > 0) * mlx->winh;
//	if (mlx->argc == 2)
//		mlx->winh = (mlx->winh > maxh) * maxh + (mlx->winh <= maxh) * mlx->winh;
//}
//
///*
//**	Parses the R element sets the max limits for a game-play window size
//**	and	orders to store it.
//*/
//
//int	window_sizer(t_mlx *mlx, char *line)
//{
//	int		maxw;
//	int		maxh;
//	char	**elem;
//
//	if (ft_wordcount(line, ' ') != 3)
//		return (msnprt(2, "Wrong resolution format."));
//	elem = ft_split(line, ' ');
//	if (arenum(elem, 'r') == 2)
//		return (2);
//	maxw = 5120 / 2;
//	maxh = 2880 / 2 - 28;
//	store_window_dimensions(mlx, maxw, maxh, elem);
//	return(free_split(1, elem));
//}
