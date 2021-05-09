/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 12:55:19 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/09 22:27:27 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	The functions that are needed for diverse part of the program are here
*/

#include "../cub3d.h"

/*
**	Initiates to NULL the mlx pointers and vars that need it
*/

void	fresh_mlx_vars(t_mlx *mlx)
{
	mlx->set.pathn = NULL;
	mlx->set.paths = NULL;
	mlx->set.pathe = NULL;
	mlx->set.pathw = NULL;
	mlx->set.pathp = NULL;
	mlx->rc.dist = NULL;
	mlx->rc.sps = NULL;
	mlx->map.map = NULL;
	mlx->map.sp_num = 0;
}

/*
**	Undoes what split does, and returns ret
*/

int	free_split(int ret, char **split)
{
	int	i;
	
	i = 0;
	while (split[i])
	{
//	printf("\n-------------\nliberando: %p\tcontenido: %s\n-----------------\n", elem[wn], elem[wn]);
		free (split[i]);
		split[i] = NULL;
		i++;
	}
	
//	printf("\n-------------\nliberando: %p\tprincipal split\n-----------------\n", elem);

	free(split);
	split = NULL;
	return (ret);
}

/*
**	Check whether the mlx pointers are in use, if so, it liberates
**	and set them to NULL.
*/

int free_mlx(t_mlx *mlx)
{
/////////////////////////////
//		printf("en free_mlx: %i\n", system("leaks debug"));
/////////////////////////////

	if (mlx->set.pathn)
		free(mlx->set.pathn);
	if (mlx->set.paths)
		free(mlx->set.paths);
	if (mlx->set.pathe)
		free(mlx->set.pathe);
	if (mlx->set.pathw)
		free(mlx->set.pathw);
	if (mlx->set.pathp)
		free(mlx->set.pathp);
	if (mlx->rc.dist)
		free(mlx->rc.dist);
	if (mlx->map.map)
		free(mlx->rc.sps);
	if (mlx->map.map)
		free_split(0, mlx->map.map);
	fresh_mlx_vars(mlx);
	return (0);
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
**	Receives the mesages to prompt on the console through the apprpiate
**	fd and returns the fd it has used.
*/

int	msnprt(int fd, char *msn)
{
	if (fd != 1 && fd != 2)
		write (2, "Error\nfd incorrect for msnprinter()\n", 36);
	if (fd == 2)
		write (2, "Error\n", 6);
	write (fd, msn, ft_strlen(msn));
	write (fd, "\n", 1);
	return (fd);
}

