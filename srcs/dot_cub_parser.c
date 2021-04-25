/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:32:18 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/25 13:32:05 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	In this file, the map is checked and set.
*/

#include "../cub3d.h"

int	parse_map_line(t_mlx *mlx, char *line)
{
	printf("%s\n", line);
	return (0);
}

int	mapper(t_mlx *mlx, int fd, char **line)
{
	int	r;
	while (ft_wordcount(*line, ' '))
	{
		r = parse_map_line(mlx, *line);
		free(*line);
		*line = NULL;
		if (r)
			return (r);
		r = get_next_line(fd, line);
		if (r == -1)
			return (msnprt(2, "Corrupt .cub file"));
	}
	while (!(ft_wordcount(*line, ' ')) && r == 1)
		r = get_next_line(fd, line);
	if (!r)
		return (0);
	else if (r == 1)
		return (msnprt(2, "Nothing allowed after map on file .cub"));
	return (msnprt(2, "Corrupt .cub file"));
}

char	check(unsigned char pos)
{
	static unsigned char check = 0;

	if (pos == 0xff && check == 0xff)
		return (0);
	if (pos == 0xff)
		return (1);
	if (1 << pos & check)
		return (msnprt(2, "Duplicated element on .cub file"));
	check |= 1 << pos;
	return (0);
}

int parse_element(t_mlx *mlx, char *line)
{
	char		**elem;
	int			wn;

	wn = ft_wordcount(line, ' ');
	elem = ft_split(line, ' ');
	if (!(check(0xff)) && elem[0][0] >= '0' && elem[0][0] <= '2')
		return (0);
	if (wn == 3 && !(ft_strncmp(elem[0], "R", 2)) && !(check(0)))
		return (window_sizer(mlx, elem));
	else if (wn == 2 && ((!(ft_strncmp(elem[0], "NO", 3)) && !(check(1)))
		|| (!(ft_strncmp(elem[0], "SO", 3)) && !(check(2)))
		|| (!(ft_strncmp(elem[0], "EA", 3)) && !(check(3)))
		|| (!(ft_strncmp(elem[0], "WE", 3)) && !(check(4)))
		|| (!(ft_strncmp(elem[0], "S", 2)) && !(check(5)))))
		return (texturizer(mlx, elem));
	else if (wn == 2 && ((!(ft_strncmp(elem[0], "F", 2)) && !(check(6)))
		|| (!(ft_strncmp(elem[0], "C", 2)) && !(check(7)))))
		return (colorizer(mlx, elem));
	return (2);
}

int	elements_parser(t_mlx *mlx, int fd, char **line)
{
	char	gnl;
	char	pe;

	pe = 1;
	while (pe == 1)
	{
		gnl = get_next_line(fd, line);
		if (gnl == -1)
			return (msnprt(2, "Corrupt .cub file"));
		else if (!gnl)
			return (msnprt(2, "Not enough elements on .cub file"));
		if (ft_wordcount(*line, ' '))
			pe = parse_element(mlx, *line);
		if (pe)
		{	
			free(*line);
			*line = NULL;
		}
		if (pe > 1)
			return (pe);
	}
	printf("winw = %i, winh = %i\npathn = %s\npaths = %s\npathe = %s\npathw = %s\npathp = %s\ncolorc = %x\ncolorf = %x\n", mlx->winw, mlx->winh, mlx->set.pathn, mlx->set.paths, mlx->set.pathe, mlx->set.pathw, mlx->set.pathp, mlx->set.c, mlx->set.f);
	return (0);
}

int	dot_cub_parser(t_mlx *mlx, char *cub_path)
{
	int		fd;
	char	*line;
	int		r;

	fd = open(cub_path, O_RDONLY);
	if (fd < 0)
		return (msnprt(2, "Map file does not exist"));
	r = elements_parser(mlx, fd, &line);
	if (r)
		return (r);
	return (mapper(mlx, fd, &line));
}