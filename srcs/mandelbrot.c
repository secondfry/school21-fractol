//
// Created by Rustam Gubaydullin on 12/06/2020.
//

#include <stdlib.h>
#include <math.h>
#include <color.h>
#include "utilities.h"

#include "mandelbrot.h"

t_byte		mandelbrot_cutoff(
	t_byte init,
	size_t *iteration,
	double x,
	double y
)
{
	static double	oldx;
	static double	oldy;
	static t_byte	period;

	if (init)
	{
		oldx = 0;
		oldy = 0;
		period = 0;
		return (0);
	}
	if (absdiv(x, oldx) < 0.00001 && absdiv(y, oldy) < 0.00001) {
		*iteration = MAX_ITERATIONS;
		return (1);
	}
	period++;
	if (period > 20) {
		period = 0;
		oldx = x;
		oldy = y;
	}
	return (0);
}

double		mandelbrot_escape_time(size_t *iteration, t_ushort sx, t_ushort sy)
{
	double c[2];
	double x;
	double y;
	double x2;
	double y2;

	c[0] = 3.5f * (float)sx / WIDTH - 2.5f;
	c[1] = -2.f * (float)sy / HEIGHT + 1.f;
	x = 0;
	y = 0;
	*iteration = 0;
	x2 = 0;
	y2 = 0;
	mandelbrot_cutoff(1, iteration, 0, 0);
	while (x2 + y2 <= HORIZON && *iteration < MAX_ITERATIONS)
	{
		y = 2 * x * y + c[1];
		x = x2 - y2 + c[0];
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (mandelbrot_cutoff(0, iteration, x, y))
			break;
	}
	return (x2 + y2);
}

int			mandelbrot_stepwise(size_t iteration)
{
	return ((int)(iteration * 0x111111) & 0x00ffffff);
}

int			mandelbrot_grayscale(size_t iteration, double z2)
{
	double log_zn;
	double log_h;
	double smth;

	log_zn = log(z2) / 2;
	log_h = log(HORIZON);
	smth = iteration - log2(log_zn / log_h);
	return ((int)(255 * smth / MAX_ITERATIONS) * 0x10101 & 0x00ffffff);
}

int			mandelbrot_color(size_t iteration, double z2)
{
	double log_zn;
	double log_h;
	double smth;

	log_zn = log(z2) / 2;
	log_h = log(HORIZON);
	smth = pow(iteration - log2(log_zn / log_h), 0.2);

	t_color color1;
	t_color color2;
	t_color color;

	t_color *palette = malloc(sizeof(t_color) * PALETTE);
//	for (size_t i = 0; i < PALETTE; i++) {
//		palette[i] = color_new(255 - i * 255 / PALETTE, 255 - i * 255 / PALETTE, 255 - i * 255 / PALETTE);
//	}
	palette[0] = color_new(255, 0, 0);
	palette[1] = color_new(0, 255, 0);
	palette[2] = color_new(0, 0, 255);

	color1 = palette[(int)fmod(floor(smth), PALETTE)];
	color2 = palette[(int)fmod(floor(smth) + 1, PALETTE)];
	color = color_lerp(color1, color2, fmod(smth, 1.f));
	int ret = color[0] << 16u | color[1] << 8u | color[2];
	color_free(color);
	return (ret);
}

void		mandelbrot(t_fractol *ftol, t_ushort sx, t_ushort sy)
{
	size_t	iteration;
	size_t	z2;

	ftol->options = OPTION_MANDELBROT_COLOR;

	iteration = 0;
	z2 = mandelbrot_escape_time(&iteration, sx, sy);
	if (iteration >= MAX_ITERATIONS)
		ftol->img_data[sx + sy * ftol->size_line_int] = 0x0;
	else if (ftol->options & OPTION_MANDELBROT_STEPWISE)
		ftol->img_data[sx + sy * ftol->size_line_int] = mandelbrot_stepwise(iteration);
	else if (ftol->options & OPTION_MANDELBROT_GRAYSCALE)
		ftol->img_data[sx + sy * ftol->size_line_int] = mandelbrot_grayscale(iteration, z2);
	else if (ftol->options & OPTION_MANDELBROT_COLOR)
		ftol->img_data[sx + sy * ftol->size_line_int] = mandelbrot_color(iteration, z2);
}
