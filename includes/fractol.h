/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fratol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:36:51 by judrion           #+#    #+#             */
/*   Updated: 2019/09/16 15:01:11 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define W_WIDTH			900
# define W_HEIGHT			800
# define WIDTH				900
# define HEIGHT				800
# define ITERATION			4
# define MANDLEBROT			1
# define JULIA				2
# define MAX_THREADS		8
# define USAGE				1
# include "libft.h"
# include "mlx.h"
# include "keycode.h"
# include <stdio.h>
# include <pthread.h>
# include <math.h>
# include <errno.h>
# include <string.h>

typedef struct				s_img
{
	void					*ptr;
	int						*array;
	int						bpp;
	int						endian;
	int						size_line;
}							t_img;

typedef struct				s_thread
{
	int						id;
	pthread_t				reel_id;
}							t_thread;

typedef struct				s_mps
{
	double					x1;
	double					x2;
	double					y1;
	double					y2;
	int						f_type;
	int						power;
	double					z_reel;
	double					z_imaginary;
	pthread_mutex_t			mutex;
	double					zoom_x;
	double					zoom_y;
}							t_mps;

typedef struct				s_mlx
{
	void					*ptr;
	void					*win;
	t_img					*img;
	t_mps					plane;
	int						iteration;
	int						work;
	int						pixel;
	int						lock;
	int						color;
	float					frequency;
	int						amplitude;
	t_thread				*threads;
}							t_mlx;

typedef struct				s_imaginary
{
	double					c_reel;
	double					c_imaginary;
	double					z_reel;
	double					z_imaginary;
}							t_imaginary;

typedef struct				s_v2d
{
	double					x;
	double					y;
}							t_v2d;

int							mandlebrot(int indice, int iteration, \
										t_mps *plan);
double						factor(double nb, double min, double max, \
									double factor_size);
int							render(t_mlx *mlx);
void						create_image(t_mlx *mlx);
void						delete_image(t_mlx *mlx);
void						update_image(t_mlx *mlx);
t_mlx						*init_mlx(char *type);
void						destroy_mlx(t_mlx *mlx);
void						escape(t_mlx *mlx);
int							key_hook(int keycode, t_mlx *mlx);
int							mouse_hook_fct(int keycode, int x, int y,\
											t_mlx *mlx);
t_v2d						*mouse_to_plan(int x, int y, t_mlx *mlx);
double						interpolate(double start, double end,\
										double interpolation);
void						apply_zoom(t_mlx *mlx, double x, double y, \
										double zoom_factor);
int							mouse_move(int x, int y, t_mlx *mlx);
int							create_thread(t_mlx *mlx);
void						fractal(void *mlx);
void						wait_thread(t_mlx *mlx);
int							set_color(t_mlx *mlx, int i);
int							print_square(int i, t_mlx *mlx, int color);
void						update_data(int power, t_imaginary *data);
unsigned int				rgbtohex(int r, int g, int b);
int							color_mix(t_mlx *mlx, int i);
void						throw_error(int errorcode);
#endif
