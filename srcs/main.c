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

#include "main.h"

void		init_mlx(t_fractol *ftol)
{
	ftol->mlx = mlx_init();
	ft_ptr_check(ftol->mlx, "[main] mlx_init errored.", 0);
	ftol->win = mlx_new_window(ftol->mlx, WIDTH, HEIGHT, TITLE);
	ft_ptr_check(ftol->win, "[main] mlx_new_window errored.", 1, ftol->mlx);
}

void		init_mlx_image(t_fractol *ftol)
{
	int bits_per_pixel;
	int size_line;
	int endianess;

	ftol->img = mlx_new_image(ftol->mlx, WIDTH, HEIGHT);
	if (!ftol->img)
	{
		ft_putstr("[main] mlx_new_image errored.");
		mlx_destroy_window(ftol->mlx, ftol->win);
		ft_memdel(&(ftol->mlx));
		exit(ENOMEM);
	}
	ftol->img_data = (int *)mlx_get_data_addr(
		ftol->img, &bits_per_pixel, &size_line, &endianess);
	ftol->iteration = (t_ushort **)malloc(sizeof(t_ushort *) * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		ftol->iteration[i] = (t_ushort *)malloc(sizeof(t_ushort) * WIDTH);
	}
	ftol->size_line_char = (size_t)size_line;
	ftol->size_line_int = (size_t)(size_line / 4);
}

//void		init_pipeline(t_fractol *ftol)
//{
//	ftol->flags = FLAG_INVALIDATE_LOCAL_NORMALIZATION
//				 | FLAG_INVALIDATE_LOCAL_SCALE | FLAG_INVALIDATE_LOCAL_ROTATION
//				 | FLAG_INVALIDATE_LOCAL_TRANSLATION | FLAG_INVALIDATE_WORLD_TRANSLATION
//				 | FLAG_INVALIDATE_WORLD_PROJECTION | FLAG_REDRAW;
//	ftol->options = OPTION_ENABLE_PERSPECTIVE | OPTION_ROTATION_X;
//	ftol->camera_position = vector_new(0, 0, 1000.f, 1);
//	ftol->camera_rotation = vector_new(0, 0, 0, 1);
//	ftol->matrix_local_normalization = matrix_new_identity();
//	ftol->matrix_local_scale = matrix_new_identity();
//	ftol->matrix_local_rotation = matrix_new_identity();
//	ftol->matrix_local_translation = matrix_new_identity();
//	ftol->matrix_world_translation = matrix_new_identity();
//	ftol->matrix_world_rotation = matrix_new_identity();
//	ftol->matrix_world_projection = matrix_new_identity();
//	ftol->matrix_world_projection_properties = vector_new(
//		90.0f, WIDTH / (float)HEIGHT, 0.1f, 100.0f);
//	ftol->matrix_view = matrix_new_identity();
//	ftol->point_count = 0;
//	ft_bzero(&(ftol->frame), sizeof(size_t) * 3);
//}

int lerp(int a, int b, float f)
{
	int step = (a + (int)(f * (float)(b - a)));
	return step * 0x10101;
}

float absdiv(float a, float b) {
	float c = a - b;
	return c < 0 ? -c : c;
}

void		mandelbrot(t_fractol *ftol, t_ushort sx, t_ushort sy)
{
	float x0 = 3.5f * (float)sx / WIDTH - 2.5f;
	float y0 = -2.f * (float)sy / HEIGHT + 1.f;
	float x = 0;
	float y = 0;
	float iteration = 0;
	float max_iteration = 1000;
	float x2 = 0;
	float y2 = 0;
	float log_zn;
	float nu;
	int color1;
	int color2;
	int color;

	int palette[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	int palette_length = 16;

	float xold = 0;
	float yold = 0;
	t_byte period = 0;

	while (x2 + y2 <= (1 << 22) && iteration < max_iteration)
	{
		y = 2 * x * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
		iteration++;

		if (absdiv(x, xold) < 0.001 && absdiv(y, yold) < 0.001) {
			iteration = max_iteration;    /* Set to max for the color plotting */
			break;       /* We are inside the Mandelbrot set, leave the while loop */
		}

		period++;
		if (period > 20) {
			period = 0;
			xold = x;
			yold = y;
		}
	}
//	while (x * x + y * y <= (1 << 16) && iteration < max_iteration) {
//		xtemp := x×x - y×y + x0
//		y := 2×x×y + y0
//		x := xtemp
//		iteration++;
//	}

	// Used to avoid floating point issues with points inside the set.
	if (iteration < max_iteration)
	{
		// sqrt of inner term removed using log simplification rules.
		log_zn = logf(x * x + y * y) / 2;
		nu = logf(log_zn / M_LN2_F) / M_LN2_F;
		// Rearranging the potential function.
		// Dividing log_zn by log(2) instead of log(N = 1<<8)
		// because we want the entire palette to range from the
		// center to radius 2, NOT our bailout radius.
		iteration += 1 - nu;
	}

	color1 = palette[(int)fmod(floorf(iteration), palette_length)];
	color2 = palette[(int)fmod(floorf(iteration) + 1, palette_length)];
	// iteration % 1 = fractional part of iteration.

	color = lerp(color1, color2, fmodf(iteration, 1.f));
	ftol->img_data[sx + sy * ftol->size_line_int] = color;
}

void 		mandelbrot_3(t_fractol data, __global int *image)
{
	double	tmp;
	double 	x;

	data.c_r = data.x * data.zoom + data.mve_horiz + data.horiz;
	data.c_i = data.y * data.zoom + data.mve_vertic + data.vertic;
	data.z_i = 0;
	data.z_r = 0;
	data.it = -100;
	while (data.z_i * data.z_i + data.z_r * data.z_r <= 256 && data.it < data.it_max)
	{
		tmp = data.z_r;
		data.z_r = tmp * tmp - data.z_i * data.z_i + data.c_r;
		data.z_i = 2 * tmp * data.z_i + data.c_i;
		data.it++;
	}
	if(data.z_i * data.z_i + data.z_r * data.z_r != 1)
		x = (double)data.it - log2(log2(data.z_r * data.z_r + data.z_i * data.z_i)) + 4.0;
	else
		x = (double)data.it + 4.0;
	double3 bla = 256 * (0.5 + 0.5 * cos((3.0 + x * 0.15 + (double3){data.rgb.x, data.rgb.y, data.rgb.z})));
	if (data.it >= data.it_max)
		put_pixel_img(data, data.x, data.y, image, 0x000000);
	else
		put_pixel_img(data, data.x, data.y, image, (((int) (bla.x)) << 16) | ((int) (bla.y)) << 8 | ((int) (bla.z)));
}

void		mandelbrot_2_1(t_fractol *ftol, t_ushort sx, t_ushort sy)
{
	float x0 = 3.5f * (float)sx / WIDTH - 2.5f;
	float y0 = -2.f * (float)sy / HEIGHT + 1.f;
	float x = 0;
	float y = 0;
	t_ushort iteration = 0;
	t_ushort max_iteration = 100;
	float x2 = 0;
	float y2 = 0;

	while (x2 + y2 <= 4 && iteration < max_iteration)
	{
		y = 2 * x * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
		iteration++;
	}

	ftol->iteration[sy][sx] = iteration;
}

void		mandelbrot_2_2(t_fractol *ftol)
{
	t_ushort max_iteration = 100;

	size_t *NumIterationsPerPixel = malloc(sizeof(size_t) * max_iteration);
	ft_bzero(NumIterationsPerPixel, sizeof(size_t) * max_iteration);

	for (size_t x = 0; x < WIDTH; x++) {
		for (size_t y = 0; y < HEIGHT; y++) {
			t_ushort i = ftol->iteration[y][x];
			NumIterationsPerPixel[i]++;
		}
	}

	size_t total = 0;
	for (size_t i = 0; i < max_iteration; i++)
	{
		total += NumIterationsPerPixel[i];
	}

	float **hue = malloc(sizeof(float *) * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		hue[i] = malloc(sizeof(float) * WIDTH);
		ft_bzero(hue[i], sizeof(float) * WIDTH);
	}

	for (size_t x = 0; x < WIDTH; x++) {
		for (size_t y = 0; y < HEIGHT; y++) {
			t_ushort iteration = ftol->iteration[y][x];
			for (t_ushort i = 0; i <= iteration; i++) {
				hue[y][x] += (float)NumIterationsPerPixel[i] / total; /* Must be floating-point division. */
			}
		}
	}

	int color1;
	int color2;
	int color;

	int palette[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
	int palette_length = 16;

	for (t_ushort sx = 0; sx < WIDTH; sx++) {
		for (t_ushort sy = 0; sy < HEIGHT; sy++) {
			color1 = palette[(int)fmod(floor(hue[sy][sx]), palette_length)];
			color2 = palette[(int)fmod(floor(hue[sy][sx]) + 1, palette_length)];
			color = lerp(color1, color2, fmod(hue[sy][sx], 1.f));
			ftol->img_data[sx + sy * ftol->size_line_int] = color;
		}
	}
}

int		loop_hook(t_fractol *ftol)
{
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
	init_mlx_image(&ftol);
//	mlx_hook(ftol.win, EVENT_KEY_PRESS, MASK_KEY_PRESS, loop_key_hook, &ftol);
//	mlx_hook(ftol.win, EVENT_DESTROY, MASK_DESTROY, loop_destroy_hook, &ftol);
	mlx_loop_hook(ftol.mlx, loop_hook, &ftol);
	mlx_loop(ftol.mlx);

	return (ft_atoi(argv[argc - 1]));
}
