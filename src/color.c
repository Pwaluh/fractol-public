/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:02:02 by judrion           #+#    #+#             */
/*   Updated: 2019/09/13 19:53:57 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int			rgbtohex(int r, int g, int b)
{
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
}

int						color_mix(t_mlx *mlx, int i)
{
	float	frequency2;
	int		amplitude;
	int		red;
	int		green;
	int		blue;

	frequency2 = 0.3 + mlx->frequency;
	amplitude = 127 + mlx->amplitude;
	red = sin(frequency2 * (float)(i) + 0) * amplitude + 170;
	green = sin(frequency2 * (float)(i) + 2) * amplitude + 34;
	blue = sin(frequency2 * (float)(i) + 4) * amplitude + 103;
	return (rgbtohex(red, green, blue));
}
