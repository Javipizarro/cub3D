/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_trgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 04:09:10 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/16 01:45:57 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Takes the trgb component of a color and creates the int that represent
**  that color in the trgb system.
*/


unsigned int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}