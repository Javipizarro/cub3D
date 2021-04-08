/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hypo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:36:52 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/06 19:41:37 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathft.h"

/*
**	Given the two sides of a right triangle, this returns the hypotesuse lenth.
*/

double	ft_hypo(double side_a, double side_b)
{
	return(ft_sqr(side_a * side_a + side_b * side_b));
}