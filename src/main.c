/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:55:07 by judrion           #+#    #+#             */
/*   Updated: 2019/08/27 12:00:02 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double						factor(double nb, double min, double max, \
									double factor_size)
{
	int		sign;

	sign = nb < 0 ? -1 : 1;
	nb = nb * sign;
	if (sign == -1)
		nb = nb / min * factor_size;
	else
		nb = nb / max * factor_size;
	return (nb);
}

int							main()
{
	int						i;
	t_mps					plane;
	char					tab[10] = {'a', 'b', 'c', 'd', 'e', 'f', '-', '+', '*', '^'};

	plane.x1 = -2.1;
	plane.x2 = 0.6;
	plane.y1 = -1.2;
	plane.y2 = 1.2;
	i = 1;
	while (i <= HEIGHT * WIDTH)
	{
		if (mandlebrot(i, ITERATION, &plane) == ITERATION)
			printf("-");
		else
			printf("%c", tab[i % 10]);
		if (i != 0 && i % WIDTH == 0)
			printf("\n");
		i = i + 1;
	}
}
