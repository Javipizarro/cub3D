/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 07:29:37 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/18 11:03:31 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	Checks whether the ortogonal tiles surrounding the player starting
**	position are reachable or walls. If they are reachable, the algorithm
**	restarts on each of them until there are no more, so the map is closed
**	or we exceed the limits of the map so there is a leak.
*/

int	find_map_leaks(t_mapping *map, unsigned int i, unsigned int j)
{
	map->g_pig[j][i] = '1';
	if (!i || !j || i == map->dimx - 1|| j == map->dimy - 1)
		return (msnprt(2, "The map is open"));
	if (map->g_pig[j - 1][i] != '1' && find_map_leaks(map, i, j - 1))
		return (2);
	if (map->g_pig[j][i + 1] != '1' && find_map_leaks(map, i + 1, j))
		return (2);
	if (map->g_pig[j + 1][i] != '1' && find_map_leaks(map, i, j + 1))
		return (2);
	if (map->g_pig[j][i - 1] != '1' && find_map_leaks(map, i - 1, j))
		return (2);
	return(0);	
}

/*
**	Checks the map for a non-recognized map-tile. Allocates memory for the map
**	and builds it map inside one string, separating each row with a '\n'.
**	Measures the map. And finds the player's start position on the map.
*/

void	parse_map_lines(t_mlx *mlx, int fd, char **line, t_mapping *map)
{
	map->dimy = 0;
	map->dimx = 0;
	map->map = ft_strdup("");
	if (!map->map)
		mlx->err = msnprt(2, "Problem with memory allocation for map->map");
	while (!mlx->err && ft_strnlen(*line, 1) && ++map->dimy)
	{
		map->i = 0;
		while (!mlx->err && (*line)[map->i])
			if (!((((*line)[map->i] >= '0' && (*line)[map->i] <= '2')
				|| (*line)[map->i] == ' ')
				|| (((*line)[map->i] == 'N' || (*line)[map->i] == 'S'
				|| (*line)[map->i] == 'E' || (*line)[map->i] == 'W')
				&&  (!(player_set(mlx, map, (*line)[map->i], line))))))
				mlx->err = msnprt(2, "Invalid map configuration");
			else if ((*line)[map->i++] == '2')
				mlx->sp.num++;
		if (!mlx->err && another_line(map, fd, line) < 0)
			mlx->err = msnprt(2, "Corrupt .cub file");
	}
	if (!mlx->err && !map->py_in)
		mlx->err = player_set(mlx, map, 'X', line);
	mlx->map.dimy = map->dimy;
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
	if (!mem)
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

void	mapper(t_mlx *mlx, int fd, char **line, char *gnl)
{
	t_mapping map;
	
	map.map = NULL;
	map.g_pig = NULL;
	map.py_in = 0;
	map.gnl = *gnl;
	parse_map_lines(mlx, fd, line, &map);
	if (!mlx->err)
		mlx->map.map = map_builder(&map, '\n');
	if (!mlx->err)
		guinea_pig_map(mlx, &map);
	if (!mlx->err)
		mlx->err = find_map_leaks(&map, mlx->py.posx, mlx->py.posy);
	if (mlx->err && line && *line)
	{
		free (*line);
		*line = NULL;
	}
	*gnl = map.gnl;
	free_mapping(&map);
}
