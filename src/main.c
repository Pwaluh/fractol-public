/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:55:07 by judrion           #+#    #+#             */
/*   Updated: 2019/09/05 17:31:28 by judrion          ###   ########.fr       */
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
	mlx->work = 1;
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
	else if (keycode == NKPL_KEY)
	{
		mlx->iteration = mlx->iteration + 1;
	}
	else if (keycode == NKMN_KEY && mlx->iteration > 1)
		mlx->iteration = mlx->iteration - 1;
	else if (keycode == 49)
	{
		mlx->plane.x1 = mlx->plane.x1 * 0.9;
		mlx->plane.x2 = mlx->plane.x2 * 0.9;
		mlx->plane.y1 = mlx->plane.y1 * 0.9;
		mlx->plane.y2 = mlx->plane.y2 * 0.9;
	}
	else if (keycode == 37)
		mlx->lock = mlx->lock == 1 ? 0 : 1;
	else if (keycode == 18)
		mlx->plane.f_type = MANDLEBROT;
	else if (keycode == 19)
		mlx->plane.f_type = JULIA;
	else if (keycode == 35)
		mlx->pixel = mlx->pixel == 1 ? 10 : 1;
	else if (keycode == 83)
		mlx->color = mlx->color == 1 ? 0 : 1;
	else
		printf("keycode : %d\n", keycode);
	mlx->work = 1;
	return (0);
}

int							main()
{

	t_mlx					*mlx;

	mlx = init_mlx();
	create_image(mlx);
	mlx->iteration = 10;
	mlx->plane.x1 = -2.1;
	mlx->plane.x2 = 0.6;
	mlx->plane.y1 = -1.2;
	mlx->plane.y2 = 1.2;
	mlx->pixel = 10;
	mlx->plane.f_type = 1;
	mlx->color = 1;

	mlx_hook(mlx->win, KP, KPMASK, &key_hook, mlx);
	mlx_hook(mlx->win, SCROLLUP_KEY, 0, &mouse_hook_fct, mlx);
	mlx_hook(mlx->win, SCROLLDOWN_KEY, 0, &mouse_hook_fct, mlx);
	mlx_hook(mlx->win, MOTIONNOTIFY, BUTTONMOTIONMASK, &mouse_move, mlx);
	mlx_loop_hook(mlx->ptr, render, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
