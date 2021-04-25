/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:12:48 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/17 19:18:00 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Take the color trgb and get the opposite color preserving the transparency.
*/

#include "color.h"

unsigned int		get_opp(unsigned int trgb)
{
	return (create_trgb(get_t(trgb), 0xFF - get_r(trgb),
	0xFF - get_g(trgb), 0xFF - get_b(trgb)));
}