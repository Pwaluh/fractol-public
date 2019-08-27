/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 10:59:17 by judrion           #+#    #+#             */
/*   Updated: 2019/08/27 14:33:04 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
int							render(t_mlx *mlx)
{
	printf("mlx : %p\n", mlx);
	return (1);
}
*/

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
