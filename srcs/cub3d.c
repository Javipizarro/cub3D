/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:59:22 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/05 09:59:13 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where everything starts and ends.
*/

#include "../cub3d.h"

/*
**	Initiates to NULL the mlx pointers that are needed to allocate
*/

void	mlx_ptr_to_null(t_mlx *mlx)
{
	mlx->set.pathn = NULL;
	mlx->set.paths = NULL;
	mlx->set.pathe = NULL;
	mlx->set.pathw = NULL;
	mlx->set.pathp = NULL;
	mlx->map = NULL;
}

/*
**	Check whether the mlx pointers are in use, if so, it liberates
**	and set them to NULL.
*/

int final_free(t_mlx *mlx)
{
/////////////////////////////
//		printf("en final_free: %i\n", system("leaks debug"));
/////////////////////////////

	if (mlx->set.pathn)
		free (mlx->set.pathn);
	if (mlx->set.paths)
		free (mlx->set.paths);
	if (mlx->set.pathe)
		free (mlx->set.pathe);
	if (mlx->set.pathw)
		free (mlx->set.pathw);
	if (mlx->set.pathp)
		free (mlx->set.pathp);
	if (mlx->map)
		free_split(0, mlx->map, mlx->mapdimy);
	mlx_ptr_to_null(mlx);
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

/*
**	Checks whether the progam has been iniciated with the correct arguments.
*/

int	arg_err(int argc, char **argv)
{
	int	i;

	if (argc < 2 || argc > 3)
		return (msnprt(2, "Invalid number of arguments"));
	i = 0;
	while (argv[1][i])
		i++;
	i -= 4;
	if (!(i > 0 && argv[1][i] == '.' && argv[1][++i] == 'c'
		&& argv[1][++i] == 'u' &&  argv[1][++i] == 'b'))
		return (msnprt(2, "Invalid map file"));
	if (argc == 3 && ft_strncmp("--sargve", argv[2], 7))
		return (msnprt(2, "Invalid option, try '--sargve' or nothing"));
	return (0);
}

/*
**	Manages the secuece of functions to correctly start and exit cub3D
**	Orders to check the argumens.
**	Orders to check and set the map.
**	Orders to check, start and finish the game.
**	Orders to free the used pointers.
**	Thanks for playing.
*/

int	real_main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.err = arg_err(argc, argv);
	if (mlx.err)
		return (0);
	mlx_ptr_to_null(&mlx);
	mlx.err = dot_cub_parser(&mlx, argv[1]);
	if (mlx.err)
		return (final_free(&mlx));
	builder(argc, &mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	real_main(argc, argv);

	if (argv[0][2] == 'c')
		printf("%i\n", system("leaks cub3D"));
	else
		printf("%i\n", system("leaks debug"));
	return (0);
}