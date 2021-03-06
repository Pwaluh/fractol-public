/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:41:33 by judrion           #+#    #+#             */
/*   Updated: 2019/09/23 22:21:53 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void						create_thread(t_mlx *mlx)
{
	int					i;

	i = 0;
	mlx->threads = (t_thread*)ft_memalloc(sizeof(t_thread) * MAX_THREADS);
	if (mlx->threads == NULL)
		throw_error(mlx, THREADS_ALLOC_FAILED);
	while (i < MAX_THREADS)
	{
		mlx->threads[i].id = i;
		if (pthread_create(&mlx->threads[i].reel_id, NULL,\
							(void*)fractal, mlx) == -1)
		{
			wait_thread(mlx, i);
			throw_error(mlx, THREAD_ALLOCATION_FAILED);
		}
		i = i + 1;
	}
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

void						fractal(t_mlx *mlx)
{
	int						i;
	int						limit;
	int						jump;
	int						indice;

	i = 0;
	limit = 0;
	indice = get_indice(mlx) * mlx->max_per_thread;
	while (i < mlx->max_per_thread)
	{
		jump = print_square(indice + i, mlx, set_color(mlx, indice + i));
		if (jump == -1)
			break ;
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

void						wait_thread(t_mlx *mlx, int nb_threads)
{
	int						i;

	i = 0;
	while (i < nb_threads)
	{
		pthread_join(mlx->threads[i].reel_id, NULL);
		i = i + 1;
	}
	free(mlx->threads);
	mlx->threads = NULL;
}
