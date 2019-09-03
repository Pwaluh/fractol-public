/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:14:50 by judrion           #+#    #+#             */
/*   Updated: 2019/09/03 15:16:58 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int							mouse_move(int x, int y, t_mlx *mlx)
{
	t_v2d					p;

	if (mlx->lock != 1 && x < WIDTH && y < HEIGHT)
	{
		p = mouse_to_plan(x, y, mlx);
		mlx->plane.z_reel = p.x;
		mlx->plane.z_imaginary = p.y;
		mlx->work = 1;
	}
	return (0);
}

t_v2d					mouse_to_plan(int x, int y, t_mlx *mlx)
{
	t_v2d			p;

	p.x = mlx->plane.x1 + factor(x, 0, WIDTH,  mlx->plane.x2 - mlx->plane.x1);
	p.y = mlx->plane.y1 + factor(y, 0, HEIGHT, mlx->plane.y2 - mlx->plane.y1);
	return (p);
}

int							mouse_hook_fct(int keycode, int x, int y, t_mlx *mlx)
{
	t_v2d				p;

	p = mouse_to_plan(x, y, mlx);
	if (keycode == 5)
		applyZoom(mlx, p.x, p.y, 1.05);
	else if (keycode == 4)
		applyZoom(mlx, p.x, p.y, 1 / 1.05);
	mlx->work = 1;
	return (0);
}

double interpolate(double start, double end, double interpolation)
{
	return start + ((end - start) * interpolation);
}

void applyZoom(t_mlx *mlx, double x, double y, double zoomFactor)
{
	double interpolation;

	interpolation = 1.0 / zoomFactor;
	mlx->plane.x1 = interpolate(x, mlx->plane.x1, interpolation);
	mlx->plane.y1 = interpolate(y, mlx->plane.y1, interpolation);
	mlx->plane.x2 = interpolate(x, mlx->plane.x2, interpolation);
	mlx->plane.y2 = interpolate(y, mlx->plane.y2, interpolation);
}
