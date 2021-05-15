/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:59:22 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/15 10:28:56 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This is the file where everything starts.
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
	if (argc == 3 && ft_strncmp("--save", argv[2], 7))
		return (msnprt(2, "Invalid option, try '--save' or nothing"));
	return (0);
}

/*
**	Manages the secuence of functions to correctly start and exit cub3D
**	Orders to check the argumens.
**	Orders to check and set the map.
**	Orders to check, start and finish the game.
**	Orders to free the used pointers.
*/

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	fresh_mlx_vars(&mlx);
	mlx.err = arg_err(argc, argv);
	mlx.argc = argc;
	if (!mlx.err)
		dot_cub_parser(&mlx, argv[1]);
	if (!mlx.err)
		start_and_set_up_mlx(&mlx);
	if (!mlx.err && argc == 2)
		start_game(&mlx);
	else if (!mlx.err && argc == 3)
		initial_pic_to_bmp(&mlx);
	free_mlx(&mlx);
	return (0);
}
