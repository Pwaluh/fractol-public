/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:55:07 by judrion           #+#    #+#             */
/*   Updated: 2019/08/27 14:33:09 by judrion          ###   ########.fr       */
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

t_mlx						*init_mlx(void)
{
	t_mlx					*mlx;

	mlx = (t_mlx*)ft_memalloc(sizeof(t_mlx));
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "fractol");
	return (mlx);
}

void						destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	free(mlx);
}

void		escape(t_mlx *mlx)
{
	delete_image(mlx);
	destroy_mlx(mlx);
}

int				key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEY)
	{
		escape(mlx);
		exit(0);
	}
	else
		printf("keycode : %d\n", keycode);
	return (0);
}

int							main()
{
	int						i;
	t_mps					plane;
	t_mlx					*mlx;

	mlx = init_mlx();
	create_image(mlx);
	plane.x1 = -2.1;
	plane.x2 = 0.6;
	plane.y1 = -1.2;
	plane.y2 = 1.2;
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		if (mandlebrot(i, ITERATION, &plane) == ITERATION)
			mlx->img->array[i] = mlx_get_color_value(mlx->ptr, 0x00000000);
		else
			mlx->img->array[i] = mlx_get_color_value(mlx->ptr, 0x00aa2267);
		i = i + 1;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->ptr, 0, 0);
	mlx_hook(mlx->win, KP, KPMASK, &key_hook, mlx);
//	mlx_loop_hook(mlx->ptr, loop, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
