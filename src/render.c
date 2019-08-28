/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:59:17 by judrion           #+#    #+#             */
/*   Updated: 2019/08/28 22:48:46 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						print_square(int i, t_mlx *mlx, int color)
{
	int						x;
	int						y;

	x = 0;
	while (x < PIXEL)
	{
		y = 0;
		while (y < PIXEL)
		{
			if (i + (y * WIDTH) + x >= WIDTH * HEIGHT)
				return (-1);
			mlx->img->array[i + (y * WIDTH) + x] = mlx_get_color_value(mlx->ptr, color);
			y = y + 1;
		}
		x = x + 1;
	}
	return (x * y);
}

int							render(t_mlx *mlx)
{
	int						i;
	int						j;
	int						limit;
	int						jump;
	int						color;

	i = 0;
	limit = 0;
	if (mlx->work == 0)
	{
		usleep(500);
		return (1);
	}
	while (i < (HEIGHT * WIDTH))
	{
		if ((j = mandlebrot(i, mlx->iteration, &mlx->plane)) == mlx->iteration)
			color = 0x00000000;
		else
			color = (0x00aa2267 * j);
		jump = print_square(i, mlx, color);
		if (jump == -1)
			break;
		if (i != limit && i % WIDTH == 0)
		{
			i = limit + (PIXEL * WIDTH);
			limit = i;
		}
		else
			i = i + PIXEL;
	}
	mlx->work = 0;
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->ptr, 0, 0);
	return (1);
}

void						create_image(t_mlx *mlx)
{
	mlx->img = (t_img*)ft_memalloc(sizeof(t_img));
//	if (mlx->img == NULL)
//		throw_error(mlx);
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->img->array = (int*)mlx_get_data_addr(mlx->img->ptr, \
												&mlx->img->bpp,\
												&mlx->img->size_line,\
												&mlx->img->endian);
}

void						delete_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img->ptr);
	//free(mlx->img->array);
	free(mlx->img);
}

/*
void						update_image(t_mlx *mlx)
{
}
*/
