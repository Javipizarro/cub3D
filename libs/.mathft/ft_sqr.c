/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:14:11 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/06 21:06:31 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathft.h"
#include <stdio.h>

/*
**	This function will return the square root of the double 'num'.
**	If 'num' is negative, the fuction will return 0.
*/

double	ft_sqr(double num)
{
	double	sqr;
	int		i;

	if (num <= 0)
		return (0);
	sqr = 1;
	i = 0;
	while (ft_abs(num / sqr - sqr) > 0.000000000000001 && i++ < 50)
		sqr = (num / sqr + sqr) / 2;
	return (sqr);
}
