/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:32:18 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/10 13:18:52 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	In this file, .cub file is parse and its info checked and stored.
*/

#include "../cub3d.h"

/*
**	Keeps record of the elements that have been added.
*/

char	checkelems(unsigned char pos)
{
	static unsigned char checkelems = 0;

	if (pos == 0xff && checkelems == 0xff)
		return (0);
	if (pos == 0xff)
		return (1);
	if (1 << pos & checkelems)
		return (msnprt(2, "Duplicated element on .cub file"));
	checkelems |= 1 << pos;
	return (0);
}

/*
**	Checks for the current element to be correct and not duplicated.
*/

int parse_element(t_mlx *mlx, char *line)
{
	char		**elem;
	int			wn;

	wn = ft_wordcount(line, ' ');
	elem = ft_split(line, ' ');
	if (!elem)
		return (msnprt(2, "Wrong .cub element allocation"));
	if (!(checkelems(0xff)) && *elem && elem[0][0] >= '0' && elem[0][0] <= '2')
		return (free_split(0, elem));
	if (wn == 3 && !(ft_strncmp(elem[0], "R", 2)) && !(checkelems(0)))
		return (free_split(window_sizer(mlx, elem), elem));
	else if (wn == 2 && ((!(ft_strncmp(elem[0], "NO", 3)) && !(checkelems(1)))
		|| (!(ft_strncmp(elem[0], "SO", 3)) && !(checkelems(2)))
		|| (!(ft_strncmp(elem[0], "EA", 3)) && !(checkelems(3)))
		|| (!(ft_strncmp(elem[0], "WE", 3)) && !(checkelems(4)))
		|| (!(ft_strncmp(elem[0], "S", 2)) && !(checkelems(5)))))
		return (free_split(texturizer(mlx, elem), elem));
	else if (wn == 2 && ((!(ft_strncmp(elem[0], "F", 2)) && !(checkelems(6)))
		|| (!(ft_strncmp(elem[0], "C", 2)) && !(checkelems(7)))))
		return (free_split(colorizer(mlx, elem), elem));
	return (free_split(msnprt(2, "Unrecognized line on .cub"), elem));
}

/*
**	Goes over the elements on the .cub file.
*/

void	elements_parser(t_mlx *mlx, int fd, char **line, char *gnl)
{
	char	pe;

	pe = 1;
	while (pe == 1)
	{
		*gnl = get_next_line(fd, line);
		if (*gnl == -1)
			mlx->err = msnprt(2, "Corrupt .cub file");
		else if (!*gnl)
			mlx->err = (msnprt(2, "Not enough elements on .cub file"));
		if (!mlx->err && ft_strnlen(*line, 1))
			pe = parse_element(mlx, *line);
		if (pe)
		{	
			free(*line);
			*line = NULL;
		}
		if (pe > 1)
			mlx->err = 2;
	}
}

/*
**	Checks whether anyting is after the map description on the .cub file.
*/

void	check_eof(t_mlx *mlx, int fd, char **line, char *gnl)
{
	while (*gnl == 1 && !(ft_strnlen(*line, 1)))
	{
		free(*line);
		*line = NULL;
		*gnl = get_next_line(fd, line);
	}
	free(*line);
	*line = NULL;
	if (*gnl < 0)
		mlx->err = msnprt(2, "Corrupt .cub file");
	if (*gnl > 0)
		mlx->err = msnprt(2, "Nothing allowed after map on file .cub");
}

/*
**	Opens the .cub file and calls the different functions to process it
*/

void	dot_cub_parser(t_mlx *mlx, char *cub_path)
{
	int		fd;
	char	*line;
	char	gnl;

	fd = open(cub_path, O_RDONLY);
	mlx->err = 2 * (fd < 0);
	if (mlx->err)
		msnprt(2, "Map file does not exist");
	else
		elements_parser(mlx, fd, &line, &gnl);
	if (!mlx->err)
		mapper(mlx, fd, &line, &gnl);
	if (!mlx->err)
		check_eof(mlx, fd, &line, &gnl);
	if(close(fd))
		mlx->err = msnprt(2, "Problem closing .cub file");
}