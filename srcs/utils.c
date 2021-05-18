/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 12:55:19 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/17 03:18:05 by jpizarro         ###   ########.fr       */
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
	mlx->map.map = NULL;
	mlx->rc.wall_dist = NULL;
	mlx->set.pathn = NULL;
	mlx->set.paths = NULL;
	mlx->set.pathe = NULL;
	mlx->set.pathw = NULL;
	mlx->set.paths1 = NULL;
	mlx->sp.num = 0;
	mlx->sp.list = NULL;
	mlx->sp.order = NULL;
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
		free (split[i]);
		split[i] = NULL;
		i++;
	}
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
	if (mlx->rc.wall_dist)
		free(mlx->rc.wall_dist);
	if (mlx->map.map)
		free_split(0, mlx->map.map);
	if (mlx->set.pathn)
		free(mlx->set.pathn);
	if (mlx->set.paths)
		free(mlx->set.paths);
	if (mlx->set.pathe)
		free(mlx->set.pathe);
	if (mlx->set.pathw)
		free(mlx->set.pathw);
	if (mlx->set.paths1)
		free(mlx->set.paths1);
	if (mlx->sp.list)
		free(mlx->sp.list);
	if (mlx->sp.order)
		free(mlx->sp.order);
	fresh_mlx_vars(mlx);
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
