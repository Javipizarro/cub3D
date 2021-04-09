/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:58:58 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/07 07:20:47 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Takes the double num as an argument, and returns its absolute value.
*/

#include "mathft.h"

double	ft_fabs(double num)
{
	return(num * (num >= 0) - num * (num < 0));
}