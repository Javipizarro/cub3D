/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .map_leak_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:01:58 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/28 12:53:36 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here is were the map around the player is leak proofed.
*/

#include "../cub3d.h"

int	find_wall(t_mapping *map)
{
	map->loop = 0;
	while (map->g_pig[map->j][map->i] == '1')
		map->j--;
	while (map->g_pig[map->j][map->i] != '1'
	&& map->g_pig[map->j][map->i] != ' ')
		map->j--;
	if (map->g_pig[map->j][map->i] == ' ')
		return (free_split(msnprt(2, "Open map."), map->g_pig, map->dimy));
	map->j++;
	map->loopi = map->i;
	map->loopj = map->j;
	move(map, 'R');
	return (0);
}

void move(t_mapping *map, char dir)
{
	char		buff;

	buff = map->diri;
	if (dir == 'F')
	{
		map->i += map->diri;
		map->j += map->dirj;
	}
	else if (dir == 'R')
	{
		map->diri = -map->dirj;
		map->dirj = buff;
		map->loop--;
	}
	else if (dir == 'L')
	{
		map->diri = map->dirj;
		map->dirj = -buff;
		map->loop++;
	}
}

int	wall_checker(t_mapping *map)
{
	if (find_wall(map))
		return(2);
	while (map->j + map->dirj != map->loopj || map->i + map->diri != map->loopi)
	{
		if (map->g_pig[map->j + map->dirj][map->i + map->diri] == ' ')
			return (free_split(msnprt(2, "Open map."), map->g_pig, map->dimy));
		if (map->g_pig[map->j - map->diri][map->i + map->dirj] != '1')
			move(map, 'L');
		else if (map->g_pig[map->j + map->dirj][map->i + map->diri] != '1')
			move(map, 'F');
		else
			move(map, 'R');
	}
		move(map, 'F');
	map->g_pig[map->j + map->dirj][map->i + map->diri] = '0');

	if (map->loop > 0)
		return (wall_checker(map));
	return (0);
}

void guinea_pig_map(t_mlx *mlx, t_mapping *map)
{
	map->i = 0;
	map->g_pig = malloc(sizeof(char *) * (map->dimy + 3));
	map->g_pig[map->i++] = ft_charlloc(sizeof(char) * map->dimx + 2, ' ');
	while (map->i <= map->dimy)
	{
		map->g_pig[map->i] = ft_charlloc(sizeof(char) * map->dimx + 2, ' ');
		ft_memcpy(&map->g_pig[map->i][1], mlx->rc.map[map->i - 1],
		ft_strlen(mlx->rc.map[map->i++ - 1]));
	}
	map->g_pig[map->i++] = ft_charlloc(sizeof(char) * map->dimx + 2, ' ');
	map->g_pig[map->i] = NULL;
}

int	map_leaks(t_mlx *mlx, t_mapping *map)
{
	map->i = 1 + mlx->py.posx;
	map->j = 1 + mlx->py.posy;
	printf("start pos at %f, %f\n", mlx->py.posx, mlx->py.posy);
	guinea_pig_map(mlx, map);
	map->err = wall_cheker(map);

	////////////////////////
	int i = 0;
	while (map->g_pig[i])
		printf("línea de mapa:##%s##\n", map->g_pig[i++]);
	printf("start at %i, %i, whit direction %c\n", pos[0], pos[1], map->g_pig[pos[1]][pos[0]]);
	////////////////////////

	return (free_split(0, map->g_pig, map->dimy + 3));
}
