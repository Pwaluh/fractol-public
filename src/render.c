/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:59:17 by judrion           #+#    #+#             */
/*   Updated: 2019/09/23 22:56:35 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						print_square(int i, t_mlx *mlx, int color)
{
	int						x;
	int						y;

	x = 0;
	y = 0;
	if (i >= 0)
	{
		while (x < mlx->pixel)
		{
			y = 0;
			while (y < mlx->pixel)
			{
				if (i + (y * WIDTH) + x >= WIDTH * HEIGHT)
					return (-1);
				mlx->img->array[i + (y * WIDTH) + x] = \
								mlx_get_color_value(mlx->ptr, color);
				y = y + 1;
			}
			x = x + 1;
		}
	}
	return (x * y);
}

int						set_color(t_mlx *mlx, int i)
{
	int				color;
	int				j;

	if ((j = mandlebrot(i, mlx->iteration, &mlx->plane)) == mlx->iteration)
		color = 0x00000000;
	else
	{
		if (mlx->color == 0)
			color = color_mix(mlx, j);
		else if (mlx->color == 2)
			color = j * 255 / mlx->iteration;
		else
			color = (0x00aa2267 * j);
	}
	return (color);
}

int						render(t_mlx *mlx)
{
	if (mlx->work == 0)
	{
		usleep(500);
		return (1);
	}
	else
	{
		create_thread(mlx);
		wait_thread(mlx, MAX_THREADS);
		mlx_clear_window(mlx->ptr, mlx->win);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->ptr,\
				(W_WIDTH / 2) - (WIDTH / 2),\
				(W_HEIGHT / 2) - (HEIGHT / 2));
		mlx->work = 0;
	}
	return (1);
}

void					create_image(t_mlx *mlx)
{
	mlx->img = (t_img*)ft_memalloc(sizeof(t_img));
	if (mlx->img == NULL)
		throw_error(mlx, NEW_IMAGE_FAILED);
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->img->array = (int*)mlx_get_data_addr(mlx->img->ptr, \
												&mlx->img->bpp,\
												&mlx->img->size_line,\
												&mlx->img->endian);
}

void					delete_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img->ptr);
	free(mlx->img);
}
