/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:40:13 by judrion           #+#    #+#             */
/*   Updated: 2019/08/31 12:45:36 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

{
	double interpolation;

	interpolation = 1.0 / zoomFactor;
	master->x1 = interpolate(coord.x, master->x1, interpolation);
	master->y1 = interpolate(coord.y, master->y1, interpolation);
	master->x2 = interpolate(coord.x, master->x2, interpolation);
	master->y2 = interpolate(coord.y, master->y2, interpolation);
}

double interpolate(double start, double end, double interpolation)
{
	return start + ((end - start) * interpolation);
}
