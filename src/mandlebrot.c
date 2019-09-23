/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandlebrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:55:12 by judrion           #+#    #+#             */
/*   Updated: 2019/09/13 20:25:33 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void					init_data(t_imaginary *data, t_mps *plan, int i)
{
	int						x;
	int						y;

	x = i % WIDTH;
	y = i / WIDTH;
	if (plan->f_type == JULIA)
	{
		data->c_reel = plan->z_reel;
		data->c_imaginary = plan->z_imaginary;
		data->z_reel = plan->x1 + factor(x, 0, WIDTH, plan->x2 - plan->x1);
		data->z_imaginary = plan->y1 \
							+ factor(y, 0, HEIGHT, plan->y2 - plan->y1);
	}
	else if (plan->f_type == MANDLEBROT)
	{
		data->c_reel = plan->x1 + factor(x, 0, WIDTH, plan->x2 - plan->x1);
		data->c_imaginary = plan->y1 \
							+ factor(y, 0, HEIGHT, plan->y2 - plan->y1);
		data->z_reel = 0;
		data->z_imaginary = 0;
	}
}

int							mandlebrot(int indice, int iteration,
										t_mps *plan)
{
	t_imaginary				data;
	int						i;

	init_data(&data, plan, indice);
	i = 0;
	while (i < iteration && data.z_reel * data.z_reel \
			+ data.z_imaginary * data.z_imaginary < 4.0)
	{
		update_data(plan->power, &data);
		i = i + 1;
	}
	return (i);
}

void						update_data(int power, t_imaginary *data)
{
	double					tmp;

	tmp = data->z_reel;
	if (power == 2)
	{
		data->z_reel = data->z_reel * data->z_reel \
					- data->z_imaginary * data->z_imaginary \
					+ data->c_reel;
		data->z_imaginary = 2.0 * data->z_imaginary * tmp \
						+ data->c_imaginary;
	}
	else
	{
		data->z_reel = (data->z_reel * data->z_reel * data->z_reel) \
					- 3 * ((data->z_reel) \
					* (data->z_imaginary * data->z_imaginary)) \
					+ data->c_reel;
		data->z_imaginary = -(data->z_imaginary \
						* data->z_imaginary * data->z_imaginary) \
						+ 3 * ((tmp * tmp) * data->z_imaginary) \
						+ data->c_imaginary;
	}
}
