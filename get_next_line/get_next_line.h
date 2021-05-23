/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:48:09 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/15 11:16:55 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		deliver_line(char **line, char **s, int r);
int		build_line(int fd, char **s);
int		ft_chrpos(char const *s, char c);
void	*ft_memcpy(void *dst, void const *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char const *s1);
size_t	ft_strlen(char const *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

#endif
