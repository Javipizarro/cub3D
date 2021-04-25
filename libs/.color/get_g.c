/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_g.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 04:56:00 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/16 01:47:28 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Takes the int of a trgb color and returns the green component.
*/

unsigned int		get_g(unsigned int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}