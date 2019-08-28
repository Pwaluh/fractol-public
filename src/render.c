/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:59:17 by judrion           #+#    #+#             */
/*   Updated: 2019/08/28 14:18:58 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int							render(t_mlx *mlx)
{
	int						i;
	int						j;

	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		if ((j = mandlebrot(i, mlx->iteration, &plane)) == mlx->iteration)
			mlx->img->array[i] = mlx_get_color_value(mlx->ptr, 0x00000000);
		else
			mlx->img->array[i] = mlx_get_color_value(mlx->ptr, 0x00aa2267 * j);
		i = i + 1;
	}
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
