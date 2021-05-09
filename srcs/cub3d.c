/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:59:22 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/09 22:28:47 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where everything starts and ends.
*/

#include "../cub3d.h"

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

	fresh_mlx_vars(&mlx);
	mlx.err = arg_err(argc, argv);
	if (!mlx.err)
		dot_cub_parser(&mlx, argv[1]);
	if (!mlx.err)
		builder(argc, &mlx);
	free_mlx(&mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	real_main(argc, argv);
	if (argv[0][2] == 'c')
		system("leaks cub3D");
	else
		system("leaks debug");
	return (0);
}