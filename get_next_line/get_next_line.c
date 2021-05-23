/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:46:27 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/15 11:33:28 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Reads a the next line of the file pointed by 'fd' in chunks the size of
**	BUFFER_SIZE.
**	Allocates *line (with malloc(3)) and fills it with the line just read.
**	Returns 1 if there is more lines to read, 0 if EOF has been reached, or -1
**	if an error has ocurred.
**	This version has an undefined behavior if, between two calls, the same file
**	descriptor switches to a different file before EOF has been reached on the
**	first fd.
*/

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*s;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!s)
		s = ft_strdup("");
	else if ((ft_chrpos(s, 10)) && line)
		return (deliver_line(line, &s, 1));
	return (deliver_line(line, &s, build_line(fd, &s)));
}

int	build_line(int fd, char **s)
{
	char		*buff;
	char		*tmp;
	int			r;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	r = read(fd, buff, BUFFER_SIZE);
	while (r > 0)
	{
		tmp = *s;
		buff[r] = 0;
		*s = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = NULL;
		if ((ft_chrpos(buff, 10)))
			break ;
		r = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	buff = NULL;
	return ((r > 0) + r * (r <= 0));
}

int	deliver_line(char **line, char **s, int r)
{
	char	*tmp;
	int		p;

	if (r > 0)
	{
		p = ft_chrpos(*s, 10);
		tmp = *s;
		*line = ft_substr(tmp, 0, p - 1);
		*s = ft_substr(tmp, p, ft_strlen(tmp) - p);
		free(tmp);
		tmp = NULL;
	}
	else if (!r)
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
	}
	return (r);
}

/*
**	Finds the first ocurrence of the character 'c' in the string 'str'.
**	Returns the possition of 'c' in "str" (NOT the index of 'c' in "str"),
**	or 0 if 'c' is not found.
*/

int	ft_chrpos(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return ((i + 1) * (s[i] != 0));
}
