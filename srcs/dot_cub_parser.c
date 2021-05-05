/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_cub_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:32:18 by jpizarro          #+#    #+#             */
/*   Updated: 2021/05/05 19:40:26 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	In this file, the map is checkelemsed and set.
*/

#include "../cub3d.h"

int	free_split(int r, char **elem, int wn)
{
	while (wn--)
	{
//	printf("\n-------------\nliberando: %p\tcontenido: %s\n-----------------\n", elem[wn], elem[wn]);
		free (elem[wn]);
		elem[wn] = NULL;
	}
	
//	printf("\n-------------\nliberando: %p\tprincipal split\n-----------------\n", elem);

	free(elem);
	elem = NULL;
	return (r);
}

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

int parse_element(t_mlx *mlx, char *line)
{
	char		**elem;
	int			wn;

	wn = ft_wordcount(line, ' ');
	elem = ft_split(line, ' ');
/////////////////////////////
//		printf("después del split de parse_element: %i\n", system("leaks cub3D"));
/////////////////////////////

	if (!(checkelems(0xff)) && elem[0][0] >= '0' && elem[0][0] <= '2')
		return (free_split(0, elem, wn));
	if (wn == 3 && !(ft_strncmp(elem[0], "R", 2)) && !(checkelems(0)))
		return (free_split(window_sizer(mlx, elem), elem, wn));
	else if (wn == 2 && ((!(ft_strncmp(elem[0], "NO", 3)) && !(checkelems(1)))
		|| (!(ft_strncmp(elem[0], "SO", 3)) && !(checkelems(2)))
		|| (!(ft_strncmp(elem[0], "EA", 3)) && !(checkelems(3)))
		|| (!(ft_strncmp(elem[0], "WE", 3)) && !(checkelems(4)))
		|| (!(ft_strncmp(elem[0], "S", 2)) && !(checkelems(5)))))
		return (free_split(texturizer(mlx, elem), elem, wn));
	else if (wn == 2 && ((!(ft_strncmp(elem[0], "F", 2)) && !(checkelems(6)))
		|| (!(ft_strncmp(elem[0], "C", 2)) && !(checkelems(7)))))
		return (free_split(colorizer(mlx, elem), elem, wn));
	return (free_split(2, elem, wn));
}

int	elements_parser(t_mlx *mlx, int fd, char **line)
{
	char	gnl;
	char	pe;

	pe = 1;
	while (pe == 1)
	{
/////////////////////////////
//		printf("antes de gnl: %i\n", system("leaks cub3D"));
/////////////////////////////
		gnl = get_next_line(fd, line);
/////////////////////////////
//		printf("después de gnl: %i\n", system("leaks cub3D"));
/////////////////////////////
		if (gnl == -1)
			return (msnprt(2, "Corrupt .cub file"));
		else if (!gnl)
			return (msnprt(2, "Not enough elements on .cub file"));
		if (ft_wordcount(*line, ' '))
/////////////////////////////
//{
//		printf("antes de parse_element: %i\n", system("leaks cub3D"));
/////////////////////////////
			pe = parse_element(mlx, *line);
/////////////////////////////
//		printf("después de parse_element: %i\n", system("leaks cub3D"));
//}
/////////////////////////////

		if (pe)
		{	
			free(*line);
			*line = NULL;
/////////////////////////////
//		printf("dentro del bucle de elements_parser: %i\n", system("leaks cub3D"));
/////////////////////////////
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