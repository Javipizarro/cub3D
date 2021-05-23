/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:53:48 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/15 10:47:35 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Computes the length of the string 's'.
*/

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
**	Copies 'n' bytes from memory area 'src' to memory area 'dst'. If 'dst' and
**	'src' overlap, behavior is undefined. Returns the original value of 'dst'.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (dst == src || !n)
		return (dst);
	if (dst != 0 || src != 0)
	{
		s = src;
		d = dst;
		while (n-- > 0)
			*(d++) = *(s++);
		return (dst);
	}
	return (0);
}

/*
**	Allocates sufficient memory for a copy of the string s1, does the copy,
**	and returns a pointer to it. The pointer may subsequently be used as an
**	argument to the function free(3).
*/

char	*ft_strdup(char const *s1)
{
	char	*s;

	s = malloc(ft_strlen(s1) + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, ft_strlen(s1) + 1);
	return (s);
}

/*
**	Allocates (with malloc(3)) and returns a new string, which is the
**	result of the concatenation of ’s1’ and ’s2’.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc(len1 + len2 + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, len1);
	ft_memcpy(s + len1, s2, len2);
	s[len1 + len2] = 0;
	return (s);
}

/*
**	Allocates (with malloc(3)) and returns a substring from the string 's'
**	or NULL if the allocation fails. The substring begins at index 'start'
**	and is of maximum size 'len'.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len + 1);
	str[len] = 0;
	return (str);
}
