/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_leak.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:01:58 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/05 10:00:15 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here is were the map around the player is leak proofed.
*/

#include "../cub3d.h"

/*
**	Checks whether the ortogonal tiles surrounding the player starting
**	position are reachable or walls. If they are reachable, the algorithm
**	restarts on each of them until there are no more, so the map is closed
**	or we exceed the limits of the map so there is a leak.
*/

int	find_leaks(t_mapping *map, int i, int j)
{
	map->g_pig[j][i] = '1';
/////////////////////////////////
//	int k = 0;
//	while (map->g_pig[k])
//		printf("línea de mapa:##%s##\n", map->g_pig[k++]);
//	printf("\n");
/////////////////////////////////
	if (!i || !j || i == map->dimx - 1|| j == map->dimy - 1)
		return (msnprt(2, "The map is open"));
	if (map->g_pig[j - 1][i] != '1' && find_leaks(map, i, j - 1))
		return (2);
	if (map->g_pig[j][i + 1] != '1' && find_leaks(map, i + 1, j))
		return (2);
	if (map->g_pig[j + 1][i] != '1' && find_leaks(map, i, j + 1))
		return (2);
	if (map->g_pig[j][i - 1] != '1' && find_leaks(map, i - 1, j))
		return (2);
	return(0);	
}

/*
**	Builds a copy of the playable map, for testing it.
**	The only difference with the original is that all the lines are
**	map-x-dimension long, in order to have a square like shape that
**	simplify the leak test.
*/

void guinea_pig_map(t_mlx *mlx, t_mapping *map)
{
	map->i = 0;
	map->g_pig = malloc(sizeof(char *) * (map->dimy + 1));
	while (map->i < map->dimy)
	{
		map->g_pig[map->i] = ft_charlloc(sizeof(char) * map->dimx, ' ');
		ft_memcpy(map->g_pig[map->i], mlx->map[map->i],
		ft_strlen(mlx->map[map->i]));
		map->i++;
	}
	map->g_pig[map->i] = NULL;
}

/*
**	Manages the leak tests for the map.
*/

int	map_leaks(t_mlx *mlx, t_mapping *map)
{
	guinea_pig_map(mlx, map);
	if (find_leaks(map, mlx->py.posx, mlx->py.posy))
		return (free_split(2, map->g_pig, map->dimy));
	
//	printf("start pos at %f, %f\n", mlx->py.posx, mlx->py.posy);
//	map->err = wall_cheker(map);
//
	////////////////////////
	int i = 0;
	while (map->g_pig[i])
		printf("línea de mapa:##%s##\n", map->g_pig[i++]);
		printf("NO LEAKS ON MAP\n");
//	printf("start at %i, %i, whit direction %c\n", pos[0], pos[1], map->g_pig[pos[1]][pos[0]]);
//	while (mlx->map[i])
//		printf("línea de mapa:##%s##\n", mlx->map[i++]);
//	printf("dimx = %d\n", map->dimx);
	////////////////////////
	mlx->mapdimy = map->dimy;
	return (free_split(0, map->g_pig, map->dimy));
}
