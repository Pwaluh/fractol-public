/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 20:55:32 by judrion           #+#    #+#             */
/*   Updated: 2019/09/13 21:04:54 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			key_hook2(int keycode, t_mlx *mlx)
{
	if (keycode == 83)
		mlx->color = mlx->color == 1 ? 0 : 1;
	else if (keycode == 18)
		mlx->plane.f_type = MANDLEBROT;
	else if (keycode == 19)
		mlx->plane.f_type = JULIA;
	else if (keycode == 35)
		mlx->pixel = mlx->pixel == 1 ? 10 : 1;
	else if (keycode == 84)
		mlx->color = 2;
	else if (keycode == 14)
		mlx->plane.power = mlx->plane.power == 2 ? 3 : 2;
	else if (keycode == 24)
		mlx->frequency = mlx->frequency * 1.1;
	else if (keycode == 27)
		mlx->frequency = mlx->frequency * 0.9;
	else
		printf("keycode : %d\n", keycode);
	return (0);
}

int					key_hook(int keycode, t_mlx *mlx)
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
	else
		key_hook2(keycode, mlx);
	mlx->work = 1;
	return (0);
}
