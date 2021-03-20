/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 04:56:00 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/16 01:46:46 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Takes the int of a trgb color and returns the blue component.
*/

unsigned int		get_b(unsigned int trgb)
{
	return (trgb & 0xFF);
}