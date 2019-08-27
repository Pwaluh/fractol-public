/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fratol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:36:51 by judrion           #+#    #+#             */
/*   Updated: 2019/08/27 11:59:08 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH				350
# define HEIGHT				90
# define ITERATION			30
#include "libft.h"
#include <stdio.h>
#include <pthread.h>

typedef struct				s_imaginary
{
	double					c_reel;
	double					c_imaginary;
	double					z_reel;
	double					z_imaginary;
}							t_imaginary;

typedef struct				s_mps
{
	double					x1;
	double					x2;
	double					y1;
	double					y2;
	double					zoom_x;
	double					zoom_y;
}							t_mps;

int							mandlebrot(int indice, int iteration, \
										t_mps *plan);
double						factor(double nb, double min, double max, \
									double factor_size);
#endif
