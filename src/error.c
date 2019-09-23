/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 22:03:01 by judrion           #+#    #+#             */
/*   Updated: 2019/09/23 22:45:41 by judrion          ###   ########.fr       */
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
	else if (error_code == NEW_IMAGE_FAILED)
	{
		ft_putendl("Can't allocate memory for new image");
		mlx_destroy_window(mlx->ptr, mlx->win);
		free(mlx);
		exit(error_code);
	}
	else if (error_code == THREADS_ALLOC_FAILED)
		ft_putendl("Can't allocate memory for threads array");
	destroy_mlx(mlx);
	exit(error_code);
}
