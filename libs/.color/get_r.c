/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 04:42:56 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/16 01:48:08 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Takes the int of a trgb color and returns the red component.
*/

unsigned int		get_r(unsigned int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}