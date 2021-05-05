/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 07:29:37 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/05 10:58:03 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	Notices whether none, one, or more than one player has been found.
**	Stores the player starting position and the direction it faces.
*/

int	player_set(t_mlx *mlx, t_mapping *map, char dir, char **line)
{
	if (map->py_in || dir == 'X')
	{
		free(*line);
		*line = NULL;
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
	return(0);
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
	map->err = get_next_line(fd, line);
	if (map->err == -1)
		return (msnprt(2, "Corrupt .cub file"));
	return (map->err);
}

/*
**	Checks the map for a non-recognized map-tile. Allocates memory for the map
**	and builds it map inside one string, separating each row with a '\n'.
**	Measures the map. And finds the player's start position on the map.
*/

int	parse_map_lines(t_mlx *mlx, int fd, char **line, t_mapping *map)
{
	map->dimy = 0;
	map->dimx = 0;
	map->map = ft_strdup("");
	while (ft_wordcount(*line, ' ') && ++map->dimy)
	{
		map->i = 0;
		while ((*line)[map->i])
			if (!((((*line)[map->i] >= '0' && (*line)[map->i] <= '2')
				|| (*line)[map->i] == ' ')
				|| (((*line)[map->i] == 'N' || (*line)[map->i] == 'S'
				|| (*line)[map->i] == 'E' || (*line)[map->i] == 'W')
				&&  (!(player_set(mlx, map, (*line)[map->i], line))))))
				return (msnprt(2, "Invalid map configuration"));
			else
				map->i++;
		if (another_line(map, fd, line) == 2)
			return (2);
	}
	if (!map->py_in)
		player_set(mlx, map, 'X', line);
	return (map->err);
}

/*
**	Builds the playable version of the map.
**	Allocates wiht malloc an array of pointers to each line of the map, plus
**	one to NULL. Allocates a malloc for each of these pointers, and stores
**	the corresponding map line on them.
*/

char	**map_builder(t_mapping *map, char c)
{
	char	**mem;
	size_t	var[3];

	mem = malloc(sizeof(char *) * (map->dimy + 1));
	if (!map->map || !mem)
		return (NULL);
	var[1] = 0;
	var[2] = 0;
	while (var[1] < map->dimy)
	{
		while (map->map[var[2]] == c)
			var[2]++;
		var[0] = 0;
		while (map->map[var[2] + var[0]] != c && map->map[var[2] + var[0]])
			var[0]++;
		mem[var[1]] = malloc(sizeof(char) * (var[0] + 1));
		if (!mem[var[1]])
			return (NULL);
		ft_memcpy(mem[var[1]], map->map + var[2], var[0]);
		mem[var[1]++][var[0]] = 0;
		var[2] += var[0];
	}
	mem[var[1]] = NULL;
	return (mem);
}

/*
**	Receives the last part of the .cub file.
**	Manages to check if the map has been delivered in a correct format
**	and whether it is the last info of the .cub file.
**	Then it orders to build and leak-proofs the map final version.
*/

int	mapper(t_mlx *mlx, int fd, char **line)
{
	t_mapping map;
	
	map.py_in = 0;
	map.err = parse_map_lines(mlx, fd, line, &map);
	if (map.err == 2)
		return (2);
	while (!(ft_wordcount(*line, ' ')) && map.err == 1)
	{
		free(*line);
		*line = NULL;
		map.err = get_next_line(fd, line);
	}
		free(*line);
		*line = NULL;
	if (map.err < 0)
		return (msnprt(2, "Corrupt .cub file"));
	if (map.err > 0)
		return (msnprt(2, "Nothing allowed after map on file .cub"));
	mlx->map = map_builder(&map, '\n');
	if (map_leaks(mlx, &map))
		return (2);
	return (0);
}
