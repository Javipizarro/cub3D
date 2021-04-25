/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 06:59:22 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/25 13:11:59 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
**	This is the file where everything starts.
*/

#include "../cub3d.h"

//int	msnprinter(int msn)
//{
//	if (!msn)
//		write(1, "Thanks for playing\n", 19);
//	else if (msn == 1)
//		write(2, "Error\nInvalid number of arguments\n", 34);
//	else if (msn == 2)
//		write(2, "Error\nInvalid map file\n", 23);
//	else if (msn == 3)
//		write(2, "Error\nInvalid option, try '--save' or nothing\n", 46);
//	else if (msn == 4)
//		write(2, "Error\nMap file does not exist\n", 30);
//	else if (msn == 10)
//		write(2, "Error\nCorrupt file .cub\n", 24);
//	else if (msn == 11)
//		write(2, "Error\nNot enough elements on file .cub\n", 39);
//	else if (msn == 12)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 13)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 14)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 15)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 16)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 17)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 18)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 19)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 20)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 21)
//		write(2, "Error\nNot enough elemenst on file .cub\n", 39);
//	else if (msn == 22)
//		write(2, "Error\nNothing allowed after map on file .cub\n", 45);
//	system("leaks a.out");
//	return (0);
//}

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


int	arg_err(int ac, char **av)
{
	int	i;

	if (ac < 2 || ac > 3)
		return (msnprt(2, "Invalid number of arguments"));
	i = 0;
	while (av[1][i])
		i++;
	i -= 4;
	if (!(i > 0 && av[1][i] == '.' && av[1][++i] == 'c'
		&& av[1][++i] == 'u' &&  av[1][++i] == 'b'))
		return (msnprt(2, "Invalid map file"));
	if (ac == 3 && ft_strncmp("--save", av[2], 7))
		return (msnprt(2, "Invalid option, try '--save' or nothing"));
	return (0);
}

/*
**	Checks the argumens.
**	Checks and sets the map.
**	Calls builder to start the game.
*/

int	main(int ac, char **av)
{
	t_mlx	mlx;
	int		err;

	err = arg_err(ac, av);
	if (err)
		return (0);
	err = dot_cub_parser(&mlx, av[1]);
	if (err)
		return (0);
	//err = builder(ac, &mlx);
	//if (err)
	//	return (msnprt(2, "Incorrect textures files"));
	msnprt(1, "Thanks for Playing!!!");
	return (0);
}
