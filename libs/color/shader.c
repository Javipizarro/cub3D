/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:07:15 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/16 19:02:56 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/*
**	Take the color trgb and darkens it from 0 to 1,
**	according to the double 'shade'.
*/

unsigned int		shader(unsigned int trgb, double shade)
{
	if (shade >= 0 && shade <= 1)
	{
		return (create_trgb(get_t(trgb), shade * get_r(trgb),
		shade * get_g(trgb), shade * get_b(trgb)));
	}
	return (trgb);
}
