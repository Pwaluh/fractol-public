/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 22:03:01 by judrion           #+#    #+#             */
/*   Updated: 2019/09/26 11:11:38 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void						throw_error(t_mlx *mlx, int error_code)
{
	if (error_code == USAGE)
	{
		ft_putendl("./fractol [mandlebrot/multibrot/julia]");
		exit(error_code);
	}
	else if (error_code == MLX_ALLOCATION_FAILED)
		ft_putendl("Can't allocate memory for mlx struct");
	else if (error_code == VECTOR2D_ALLOC_FAILED)
	{
		ft_putendl("Can't allocate memory for mouse coord");
		if (mlx->threads != NULL)
			wait_thread(mlx, MAX_THREADS);
	}
	else if (error_code == THREADS_ALLOC_FAILED)
		ft_putendl("Can't allocate memory for threads array");
	else
		throw_error2(mlx, error_code);
	destroy_mlx(mlx);
	exit(error_code);
}

void						throw_error2(t_mlx *mlx, int error_code)
{
	if (error_code == MLX_INIT_FAILED)
	{
		free(mlx);
		exit(error_code);
	}
	else if (error_code == NEW_IMAGE_FAILED)
	{
		ft_putendl("Can't allocate memory for new image");
		mlx_destroy_window(mlx->ptr, mlx->win);
		free(mlx);
		exit(error_code);
	}
	else if (error_code == WIN_INIT_FAILED)
	{
		mlx_init(NULL);
		free(mlx);
		exit(error_code);
	}
}
