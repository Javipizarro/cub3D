/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:32:18 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/16 19:52:18 by jpizarro         ###   ########.fr       */
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
		return 2;
//		return (msnprt(2, "Duplicated element on .cub file"));
	checkelems |= 1 << pos;
	return (0);
}

/*
**	Checks for the current element to be correct and not duplicated.
*/

int parse_element(t_mlx *mlx, char *line)
{
	if (!checkelems(0xff) && *line
	&& ((line[0] >= '0' && line[0] <= '2') || line[0] == ' '))
		return (0);
	if (!checkelems(0xff))
		printf("NO DEBERÍA APARECER\n");

	if ((!ft_strncmp(line, "NO ", 3) && !checkelems(0))
	|| (!ft_strncmp(line, "SO ", 3) && !checkelems(1))
	|| (!ft_strncmp(line, "EA ", 3) && !checkelems(2))
	|| (!ft_strncmp(line, "WE ", 3) && !checkelems(3))
	|| (!ft_strncmp(line, "S ", 2) && !checkelems(4)))
		return(texturizer(mlx, line));
	else if ((!ft_strncmp(line, "R ", 2))&& !checkelems(5)
	&& ft_wordcount(line, ' ') == 3)
		return(window_sizer(mlx, ft_split(line, ' ')));
//	else if (((!ft_strncmp(line, "F ", 2) && !checkelems(6))
//	|| (!ft_strncmp(line, "C ", 2) && !checkelems(7)))
//	&&	ft_wordcount(line, ',') == 3)
	else if ((!ft_strncmp(line, "F ", 2) && !checkelems(6))
	|| (!ft_strncmp(line, "C ", 2) && !checkelems(7)))
		return(colorizer(mlx, line[0], ft_split(&line[2], ',')));
	return (msnprt(2, "Reached unvalid line for an element on .cub"));
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
	int len;

	len = 0;
	while (*gnl == 1 && !len)
	{
		free(*line);
		*line = NULL;
		*gnl = get_next_line(fd, line);
		len = ft_strlen(*line);
	}
	free(*line);
	*line = NULL;
	if (*gnl < 0)
		mlx->err = msnprt(2, "Corrupt .cub file");
	if (*gnl || len)
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
	if (close(fd))
		mlx->err = msnprt(2, "Problem closing .cub file");
}