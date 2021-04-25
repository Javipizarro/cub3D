/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 04:22:56 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/16 01:48:49 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Takes the int of a trgb color and returns the transparency component.
*/

unsigned int		get_t(unsigned int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}