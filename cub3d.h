/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:56:25 by jpizarro          #+#    #+#             */
/*   Updated: 2021/04/06 10:17:25 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include "libs/color/color.h"
# include "libs/libft/libft.h"
# include "libs/mathft/mathft.h"

typedef struct	s_mlxvars
{
	void	*mlx;
}				t_mlxvars;
// in the color.h header:
//unsigned int		create_trgb(int t, int r, int g, int b);
//unsigned int		get_b(unsigned int trgb);
//unsigned int		get_g(unsigned int trgb);
//unsigned int		get_r(unsigned int trgb);
//unsigned int		get_t(unsigned int trgb);
//unsigned int		get_opp(unsigned int trgb);
//unsigned int		shader(unsigned int trgb, double shade);

#endif