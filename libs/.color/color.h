/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:49:01 by jpizarro          #+#    #+#             */
/*   Updated: 2021/03/17 18:18:06 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

unsigned int		create_trgb(int t, int r, int g, int b);
unsigned int		get_b(unsigned int trgb);
unsigned int		get_g(unsigned int trgb);
unsigned int		get_r(unsigned int trgb);
unsigned int		get_t(unsigned int trgb);
unsigned int		get_opp(unsigned int trgb);
unsigned int		shader(unsigned int trgb, double shade);

#endif