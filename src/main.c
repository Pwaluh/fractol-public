/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:55:07 by judrion           #+#    #+#             */
/*   Updated: 2019/09/23 23:05:27 by judrion          ###   ########.fr       */
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

void						init_plan(t_mlx *mlx)
{
	mlx->plane.x1 = -2.1;
	mlx->plane.x2 = 0.6;
	mlx->plane.y1 = -1.2;
	mlx->plane.y2 = 1.2;
	mlx->plane.power = 2;
	mlx->plane.f_type = MANDLEBROT;
}

t_mlx						*init_mlx(char *type)
{
	t_mlx					*mlx;

	mlx = (t_mlx*)ft_memalloc(sizeof(t_mlx));
	if (mlx == NULL)
		throw_error(NULL, MLX_ALLOCATION_FAILED);
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		throw_error(mlx, MLX_INIT_FAILED);
	mlx->win = mlx_new_window(mlx->ptr, W_WIDTH, W_HEIGHT, "fractol");
	if (mlx->win == WIN_INIT_FAILED)
		throw_error(mlx, WIN_INIT_FAILED);
	mlx->work = 1;
	mlx->iteration = 2;
	mlx->pixel = 10;
	init_plan(mlx);
	if (ft_strcmp(type, "julia") == 0)
		mlx->plane.f_type = JULIA;
	else if (ft_strcmp(type, "multibrot") == 0)
		mlx->plane.power = 3;
	else if (ft_strcmp(type, "mandlebrot") != 0)
		throw_error(mlx, USAGE);
	mlx->color = 1;
	mlx->frequency = 0.1;
	mlx->amplitude = 1;
	return (mlx);
}

void						destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_init(NULL);
	free(mlx);
}

int							main(int argc, char **argv)
{
	t_mlx					*mlx;

	mlx = NULL;
	if (argc != 2)
		throw_error(mlx, USAGE);
	mlx = init_mlx(argv[1]);
	mlx->max_per_thread = (HEIGHT * WIDTH) / MAX_THREADS;
	create_image(mlx);
	mlx->plane.zoom_x = WIDTH / (mlx->plane.x2 - mlx->plane.x1);
	mlx->plane.zoom_y = HEIGHT / (mlx->plane.y2 - mlx->plane.y1);
	mlx_hook(mlx->win, KP, KPMASK, &key_hook, mlx);
	mlx_hook(mlx->win, SCROLLUP_KEY, 0, &mouse_hook_fct, mlx);
	mlx_hook(mlx->win, SCROLLDOWN_KEY, 0, &mouse_hook_fct, mlx);
	mlx_hook(mlx->win, MOTIONNOTIFY, BUTTONMOTIONMASK, &mouse_move, mlx);
	mlx_loop_hook(mlx->ptr, render, mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
