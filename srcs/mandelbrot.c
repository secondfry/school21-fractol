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
	if (absdiv(x, oldx) < 0.001 && absdiv(y, oldy) < 0.001) {
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

double		mandelbrot_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_mandelbrot *mandelbrot
)
{
	double c[2];
	double x;
	double y;
	double x2;
	double y2;

	c[0] = sx * mandelbrot->kx + mandelbrot->ox;
	c[1] = sy * mandelbrot->ky + mandelbrot->oy;
	x = 0;
	y = 0;
	*iteration = 0;
	x2 = 0;
	y2 = 0;
	mandelbrot_cutoff(1, iteration, 0, 0);
	while (x2 + y2 <= mandelbrot->horizon && *iteration < MAX_ITERATIONS)
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

int			mandelbrot_grayscale(size_t iteration, t_fractol *ftol, double z2)
{
	double log_zn;
	double smth;

	log_zn = log(z2) / 2;
	if (log_zn <= 0)
		log_zn = 1;
	smth = iteration - log2(log_zn) + ftol->mandelbrot->log2_log_h;
	return ((int)(255 * smth / MAX_ITERATIONS) * 0x10101 & 0x00ffffff);
}

int			mandelbrot_color(size_t iteration, t_fractol *ftol, double z2)
{
	double	log_zn;
	double	smth;
	t_byte	c[3];

	log_zn = log(z2) / 2;
	if (log_zn <= 0)
		log_zn = 1;
	smth = iteration - log2(log_zn) + ftol->mandelbrot->log2_log_h;

	t_color color1;
	t_color color2;
	double	f;

	if (ftol->options & OPTION_MANDELBROT_ANIMATED)
	{
		color1 = ftol->mandelbrot->animated_palette[(int)smth % PALETTE];
		color2 = ftol->mandelbrot->animated_palette[((int)smth + 1) % PALETTE];
	} else {
		color1 = ftol->mandelbrot->palette[(int)smth % PALETTE];
		color2 = ftol->mandelbrot->palette[((int)smth + 1) % PALETTE];
	}

	f = fmod(smth, 1.f);
	c[0] = color1[0] + f * (color2[0] - color1[0]);
	c[1] = color1[1] + f * (color2[1] - color1[1]);
	c[2] = color1[2] + f * (color2[2] - color1[2]);
	int ret = c[0] << 16u | c[1] << 8u | c[2];
	return (ret);
}

void		mandelbrot(t_fractol *ftol, t_ushort sx, t_ushort sy)
{
	size_t	iteration;
	size_t	z2;

	iteration = 0;
	z2 = mandelbrot_escape_time(&iteration, sx, sy, ftol->mandelbrot);
	if (iteration >= MAX_ITERATIONS)
		ftol->img_data[sx + sy * ftol->size_line_int] = 0x0;
	else if (ftol->options & OPTION_MANDELBROT_STEPWISE)
		ftol->img_data[sx + sy * ftol->size_line_int] = mandelbrot_stepwise(iteration);
	else if (ftol->options & OPTION_MANDELBROT_GRAYSCALE)
		ftol->img_data[sx + sy * ftol->size_line_int] = mandelbrot_grayscale(iteration, ftol, z2);
	else if (ftol->options & OPTION_MANDELBROT_COLOR)
		ftol->img_data[sx + sy * ftol->size_line_int] = mandelbrot_color(iteration, ftol, z2);
}
