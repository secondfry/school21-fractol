/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:00:03 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/01 06:03:56 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "mlx_init.h"
#include "mandelbrot.h"
#include "utilities.h"

#include "main.h"

//void 		mandelbrot_3(t_fractol data, __global int *image)
//{
//	double	tmp;
//	double 	x;
//
//	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
//	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
//	data.z_i = 0;
//	data.z_r = 0;
//	data.it = -100;
//	while (data.z_i * data.z_i + data.z_r * data.z_r <= 256 && data.it < data.it_max)
//	{
//		tmp = data.z_r;
//		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
//		data.z_i = 2 * tmp * data.z_i + data.c_i;
//		data.it++;
//	}
//	if(data.z_i * data.z_i + data.z_r * data.z_r != 1)
//		x = (double)data.it - log2(log2(data.z_r * data.z_r + data.z_i * data.z_i)) + 4.0;
//	else
//		x = (double)data.it + 4.0;
//	double3 bla = 256 * (0.5 + 0.5 * cos((3.0 + x * 0.15 + (double3){data.rgb.x, data.rgb.y, data.rgb.z})));
//	if (data.it >= data.it_max)
//		put_pixel_img(data, data.x, data.y, image, 0x000000);
//	else
//		put_pixel_img(data, data.x, data.y, image, (((int) (bla.x)) << 16) | ((int) (bla.y)) << 8 | ((int) (bla.z)));
//}

void		mandelbrot_2_1(t_fractol *ftol, t_ushort sx, t_ushort sy)
{
	float x0 = 3.5f * (float)sx / WIDTH - 2.5f;
	float y0 = -2.f * (float)sy / HEIGHT + 1.f;
	float x = 0;
	float y = 0;
	t_ushort iteration = 0;
	float x2 = 0;
	float y2 = 0;

	float xold = 0;
	float yold = 0;
	t_byte period = 0;

	while (x2 + y2 <= HORIZON && iteration < MAX_ITERATIONS)
	{
		y = 2 * x * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
		iteration++;

		if (absdiv(x, xold) < 0.00001 && absdiv(y, yold) < 0.00001) {
			iteration = MAX_ITERATIONS;    /* Set to max for the color plotting */
			break;       /* We are inside the Mandelbrot set, leave the while loop */
		}

		period++;
		if (period > 20) {
			period = 0;
			xold = x;
			yold = y;
		}
	}

	if (iteration >= MAX_ITERATIONS) {
		ftol->iterationD[sy][sx] = iteration;
	} else {
		// sqrt of inner term removed using log simplification rules.
		double log_zn = log(x2 + y2) / 2;
		double nu = log2(log_zn / log(2));
		// Rearranging the potential function.
		// Dividing log_zn by log(2) instead of log(N = 1<<8)
		// because we want the entire palette to range from the
		// center to radius 2, NOT our bailout radius.
		double iterationD = nu;
		ftol->iterationD[sy][sx] = iterationD;
	}

	ftol->iteration[sy][sx] = iteration;
}

void		mandelbrot_2_2(t_fractol *ftol)
{
//	ft_bzero(ftol->iterationPixels, sizeof(size_t) * (MAX_ITERATIONS + 1));
//
//	for (size_t x = 0; x < WIDTH; x++) {
//		for (size_t y = 0; y < HEIGHT; y++) {
//			t_ushort i = ftol->iteration[y][x];
//			ftol->iterationPixels[i]++;
//		}
//	}
//
//	size_t total = 0;
//	for (size_t i = 0; i < MAX_ITERATIONS + 1; i++)
//	{
//		total += ftol->iterationPixels[i];
//	}
//
//	for (size_t i = 0; i < HEIGHT; i++) {
//		ft_bzero(ftol->hue[i], sizeof(float) * WIDTH);
//	}
//
//	for (size_t x = 0; x < WIDTH; x++) {
//		for (size_t y = 0; y < HEIGHT; y++) {
//			t_ushort iteration = ftol->iteration[y][x];
//			for (t_ushort i = 0; i <= iteration; i++) {
//				ftol->hue[y][x] += (float)ftol->iterationPixels[i] / total; /* Must be floating-point division. */
//			}
//			ftol->hue[y][x] *= ftol->iterationD[y][x];
//		}
//	}
//
//	int color1;
//	int color2;
//	int color;
//
//	int palette[3] = {0xff, 0x77, 0x00};
//	int palette_length = 3;
//
//	for (t_ushort sy = 0; sy < HEIGHT; sy++) {
//		for (t_ushort sx = 0; sx < WIDTH; sx++) {
////			double smth = 1 + ftol->hue[sy][sx] * palette_length + ftol->iterationD[sy][sx];
//			double smth = ftol->hue[sy][sx];
//			color1 = palette[(int)fmod(floor(smth), palette_length)];
//			color2 = palette[(int)fmod(floor(smth) + 1, palette_length)];
//			color = lerp(color1, color2, fmod(smth, 1.f));
//			ftol->img_data[sx + sy * ftol->size_line_int] = color * 0x10101;
//		}
//	}
}


void		init_ftol(t_fractol *ftol)
{
	ftol->iteration = (t_ushort **)malloc(sizeof(t_ushort *) * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		ftol->iteration[i] = (t_ushort *)malloc(sizeof(t_ushort) * WIDTH);
	}
	ftol->iterationD = (double **)malloc(sizeof(double *) * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		ftol->iterationD[i] = (double *)malloc(sizeof(double) * WIDTH);
	}
	ftol->iterationPixels = malloc(sizeof(size_t) * (MAX_ITERATIONS + 1));
	ftol->hue = malloc(sizeof(float *) * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		ftol->hue[i] = malloc(sizeof(float) * WIDTH);
	}

}


int		loop_hook(t_fractol *ftol)
{
	ft_bzero(ftol->img_data, ftol->size_line_char * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		ft_bzero(ftol->iteration[i], sizeof(t_ushort) * WIDTH);
	}

	for (size_t y = 0; y < HEIGHT; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			mandelbrot(ftol, x, y);
		}
	}

//	mandelbrot_2_2(ftol);

	mlx_put_image_to_window(ftol->mlx, ftol->win, ftol->img, 0, 0);
	mlx_do_sync(ftol->mlx);
	return (0);
}

int			main(int argc, char **argv)
{
	t_fractol	ftol;

//	if (argc != 2)
//	{
//		ft_putendl_fd("Provide one valid map file argument, please.", 2);
//		return (EINVAL);
//	}
//	init_pipeline(&ftol);
//	input(&ftol, argv[argc - 1]);
	init_mlx(&ftol);
	init_ftol(&ftol);
//	mlx_hook(ftol.win, EVENT_KEY_PRESS, MASK_KEY_PRESS, loop_key_hook, &ftol);
//	mlx_hook(ftol.win, EVENT_DESTROY, MASK_DESTROY, loop_destroy_hook, &ftol);
	mlx_loop_hook(ftol.mlx, loop_hook, &ftol);
	mlx_loop(ftol.mlx);

	return (ft_atoi(argv[argc - 1]));
}
