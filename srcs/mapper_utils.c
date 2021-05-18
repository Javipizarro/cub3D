/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:01:58 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 13:48:30 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here are some side fucions needed while mapping.
*/

#include "../cub3d.h"

/*
**	Notices whether none, one, or more than one player has been found.
**	Stores the player starting position and the direction it faces.
*/

int	player_set(t_mlx *mlx, t_mapping *map, char dir, char **line)
{
	if (map->py_in || dir == 'X')
	{
		if (map->py_in)
			return (msnprt(2, "More than one player on map"));
		return (msnprt(2, "No player on the map"));
	}
	mlx->py.posx = (double)map->i + 0.5;
	mlx->py.posy = (double)map->dimy - 0.5;
	if (dir == 'N' || dir == 'S')
		mlx->py.dirx = 0;
	else if (dir == 'E' || dir == 'W')
		mlx->py.diry = 0;
	if (dir == 'N')
		mlx->py.diry = -1;
	else if (dir == 'S')
		mlx->py.diry = 1;
	else if (dir == 'E')
		mlx->py.dirx = 1;
	else if (dir == 'W')
		mlx->py.dirx = -1;
	map->py_in = dir;
	(*line)[map->i] = '0';
	return (0);
}

/*
**	Mounts the new line in the one string malloc, measures it to return the
**	map-x-dimension. Frees the line and delivers another to be checked.
*/

int	another_line(t_mapping *map, int fd, char **line)
{
	map->buff = map->map;
	map->map = ft_strnewline(map->buff, *line);
	free(map->buff);
	map->buff = NULL;
	free(*line);
	*line = NULL;
	map->dimx = map->dimx * (map->dimx >= map->i)
		+ map->i * (map->i > map->dimx);
	map->gnl = get_next_line(fd, line);
	return (map->gnl);
}

/*
**	Check whether the pointers allocated when mapping are in use,
**	if so, it liberates them, and set them to NULL.
*/

int	free_mapping(t_mapping *map)
{
	if (map->map)
		free(map->map);
	if (map->g_pig)
		free_split(2, map->g_pig);
	map->map = NULL;
	map->g_pig = NULL;
	return (0);
}

/*
**	Builds a copy of the playable map, for testing it.
**	The only difference with the original is that all the lines are
**	map-x-dimension long, in order to have a square like shape that
**	simplify the leak test.
*/

void	guinea_pig_map(t_mlx *mlx, t_mapping *map)
{
	map->i = 0;
	map->g_pig = malloc(sizeof(char *) * (map->dimy + 1));
	if (!map->g_pig)
		mlx->err = msnprt(2, "Guinea Pig Map malloc problem");
	while (!mlx->err && map->i < map->dimy)
	{
		map->g_pig[map->i] = ft_charlloc(sizeof(char) * map->dimx, ' ');
		ft_memcpy(map->g_pig[map->i], mlx->map.map[map->i],
			ft_strlen(mlx->map.map[map->i]));
		map->i++;
	}
	map->g_pig[map->i] = NULL;
}
