/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:41:33 by judrion           #+#    #+#             */
/*   Updated: 2019/09/13 18:28:18 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					create_thread(t_mlx *mlx)
{
	int					i;

	i = 0;
	mlx->threads = (t_thread*)ft_memalloc(sizeof(t_thread) * MAX_THREADS);
	if (mlx->threads)
	{
		while (i < MAX_THREADS)
		{
			mlx->threads[i].id = i;
			if (pthread_create(&mlx->threads[i].reel_id, NULL, (void*)fractal, (void*)mlx) == - 1)
				return (-1);
			i = i + 1;
		}
	}
	else
		return (-2);
	return (1);
}

static int					get_indice(t_mlx *mlx)
{
	int						i;

	i = 0;
	while (i < MAX_THREADS)
	{
		if (mlx->threads[i].reel_id == pthread_self())
			return (i);
		i = i + 1;
	}
	return (-1);
}

void						fractal(void *p_mlx)
{
	int						i;
	int						limit;
	int						jump;
	int						indice;
	t_mlx					*mlx;

	mlx = (t_mlx*)p_mlx;
	i = 0;
	limit = 0;
	indice = get_indice(mlx) * ((WIDTH * HEIGHT) / MAX_THREADS);
	while (i < (HEIGHT * WIDTH) / MAX_THREADS)
	{
		jump = print_square(indice + i, mlx, set_color(mlx, indice + i));
		if (jump == -1)
			break;
		if (i != limit && i % WIDTH == 0)
		{
			i = limit + (mlx->pixel * WIDTH);
			limit = i;
		}
		else
			i = i + mlx->pixel;
	}
	pthread_exit(NULL);
}

void						wait_thread(t_mlx *mlx)
{
	int						i;

	i = 0;
	while (i < MAX_THREADS)
	{
		pthread_join(mlx->threads[i].reel_id, NULL);
		i = i + 1;
	}
	free(mlx->threads);
}
