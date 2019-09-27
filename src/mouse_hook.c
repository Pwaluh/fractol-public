/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:14:50 by judrion           #+#    #+#             */
/*   Updated: 2019/09/13 20:43:38 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int							mouse_move(int x, int y, t_mlx *mlx)
{
	t_v2d					*p;

	if (mlx->plane.f_type == MANDLEBROT)
		return (1);
	if (mlx->lock != 1 && (x > 0 && x < W_WIDTH) && (y > 0 && y < W_HEIGHT))
	{
		p = mouse_to_plan(x, y, mlx);
		mlx->plane.z_reel = p->x;
		mlx->plane.z_imaginary = p->y;
		free(p);
		mlx->plane.zoom_x = WIDTH / (mlx->plane.x2 - mlx->plane.x1);
		mlx->plane.zoom_y = HEIGHT / (mlx->plane.y2 - mlx->plane.y1);
		mlx->work = 1;
	}
	return (0);
}

t_v2d						*mouse_to_plan(int x, int y, t_mlx *mlx)
{
	t_v2d					*p;

	p = (t_v2d*)ft_memalloc(sizeof(t_v2d));
	if (p == NULL)
		throw_error(mlx, VECTOR2D_ALLOC_FAILED);
	if (p)
	{
		p->x = mlx->plane.x1 + factor(x, 0, WIDTH,  \
									mlx->plane.x2 - mlx->plane.x1);
		p->y = mlx->plane.y1 + factor(y, 0, HEIGHT, \
									mlx->plane.y2 - mlx->plane.y1);
	}
	return (p);
}

int							mouse_hook_fct(int keycode, int x, int y,\
											t_mlx *mlx)
{
	t_v2d					*p;

	if (y > 0)
	{
		p = mouse_to_plan(x, y, mlx);
		if (keycode == 5)
			apply_zoom(mlx, p->x, p->y, 1.05);
		else if (keycode == 4)
			apply_zoom(mlx, p->x, p->y, 1 / 1.05);
		mlx->work = 1;
		free(p);
	}
	return (0);
}

double						interpolate(double start, double end, \
										double interpolation)
{
	return (start + ((end - start) * interpolation));
}

void						apply_zoom(t_mlx *mlx, double x, double y,\
										double zoom_factor)
{
	double					interpolation;

	interpolation = 1.0 / zoom_factor;
	mlx->plane.x1 = interpolate(x, mlx->plane.x1, interpolation);
	mlx->plane.y1 = interpolate(y, mlx->plane.y1, interpolation);
	mlx->plane.x2 = interpolate(x, mlx->plane.x2, interpolation);
	mlx->plane.y2 = interpolate(y, mlx->plane.y2, interpolation);
}
