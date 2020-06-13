//
// Created by Rustam Gubaydullin on 12/06/2020.
//

#include "render.h"

t_byte		cutoff(
	t_byte init,
	size_t *iteration,
	double x,
	double y,
	t_ftol_data *data
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
	if (absdiv(x, oldx) < 0.0001 && absdiv(y, oldy) < 0.0001) {
		*iteration = data->final_iterations;
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

double		julia_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
)
{
	double x;
	double y;
	double x2;
	double y2;

	x = (double)sx * data->kx + data->ox;
	y = (double)sy * data->ky + data->oy;
	*iteration = 0;
	x2 = x * x;
	y2 = y * y;
	cutoff(1, iteration, 0, 0, data);
	while (x * x + y * y <= 4 && *iteration < data->final_iterations)
	{
		y = 2 * x * y + data->julia_zi;
		x = x2 - y2 + data->julia_zr;
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (cutoff(0, iteration, x, y, data))
			break;
	}
	return (x2 + y2);
}

double		tricorne_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
)
{
	double c[2];
	double x;
	double y;
	double x2;
	double y2;

	c[0] = sx * data->kx + data->ox;
	c[1] = sy * data->ky + data->oy;
	x = c[0];
	y = c[1];
	*iteration = 0;
	x2 = x * x;
	y2 = y * y;
	cutoff(1, iteration, 0, 0, data);
	while (x2 + y2 <= 4 && *iteration < data->final_iterations)
	{
		y = -2 * x * y + c[1];
		x = x2 - y2 + c[0];
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (cutoff(0, iteration, x, y, data))
			break;
	}
	return (x2 + y2);
}

double dabs(double v) {
	return v < 0 ? -v : v;
}

double		burning_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
)
{
	double c[2];
	double x;
	double y;
	double x2;
	double y2;

	c[0] = sx * data->kx + data->ox;
	c[1] = sy * data->ky + data->oy;
	x = c[0];
	y = c[1];
	*iteration = 0;
	x2 = x * x;
	y2 = y * y;
	cutoff(1, iteration, 0, 0, data);
	while (x2 + y2 <= 4 && *iteration < data->final_iterations)
	{
		y = dabs(2 * x * y + c[1]);
		x = dabs(x2 - y2 + c[0]);
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (cutoff(0, iteration, x, y, data))
			break;
	}
	return (x2 + y2);
}

double		mandelbrot_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
)
{
	double c[2];
	double x;
	double y;
	double x2;
	double y2;

	c[0] = sx * data->kx + data->ox;
	c[1] = sy * data->ky + data->oy;
	x = 0;
	y = 0;
	*iteration = 0;
	x2 = x * x;
	y2 = y * y;
	cutoff(1, iteration, 0, 0, data);
	while (x2 + y2 <= data->horizon && *iteration < data->final_iterations)
	{
		y = 2 * x * y + c[1];
		x = x2 - y2 + c[0];
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (cutoff(0, iteration, x, y, data))
			break;
	}
	return (x2 + y2);
}

int			color_stepwise(size_t iteration)
{
	return ((int)(iteration * 0x111111) & 0x00ffffff);
}

int			color_grayscale(size_t iteration, t_fractol *ftol, double z2)
{
	double log_zn;
	double smth;

	log_zn = log(z2) / 2;
	if (log_zn <= 0)
		log_zn = 1;
	smth = iteration - log2(log_zn) + ftol->data->log2_log_h;
	return ((int)(255 * smth / ftol->data->final_iterations) * 0x10101 & 0x00ffffff);
}

int			color_color(size_t iteration, t_fractol *ftol, double z2)
{
	double	log_zn;
	double	smth;
	t_byte	c[3];

	log_zn = log(z2) / 2;
	if (log_zn <= 0)
		log_zn = 1;
	smth = iteration - log2(log_zn) + ftol->data->log2_log_h;

	t_color color1;
	t_color color2;
	double	f;

	if (ftol->options & OPTION_ANIMATED)
	{
		smth += ftol->color_cycle;
	}

	smth = pow(smth, 0.45);

	color1 = ftol->data->palette[(int)smth % PALETTE];
	color2 = ftol->data->palette[((int)smth + 1) % PALETTE];

	f = fmod(smth, 1.f);
	c[0] = color1[0] + f * (color2[0] - color1[0]);
	c[1] = color1[1] + f * (color2[1] - color1[1]);
	c[2] = color1[2] + f * (color2[2] - color1[2]);
	int ret = c[0] << 16u | c[1] << 8u | c[2];
	return (ret);
}

void		render(t_fractol *ftol, t_ushort sx, t_ushort sy)
{
	size_t	iteration;
	size_t	z2;

	iteration = 0;
	z2 = ftol->data->escape_time(&iteration, sx, sy, ftol->data);
	if (iteration >= ftol->data->final_iterations)
		ftol->img_data[sx + sy * ftol->size_line_int] = 0x0;
	else if (ftol->options & OPTION_STEPWISE)
		ftol->img_data[sx + sy * ftol->size_line_int] =
			color_stepwise(iteration);
	else if (ftol->options & OPTION_GRAYSCALE)
		ftol->img_data[sx + sy * ftol->size_line_int] =
			color_grayscale(iteration, ftol, z2);
	else if (ftol->options & OPTION_COLOR)
		ftol->img_data[sx + sy * ftol->size_line_int] =
			color_color(iteration, ftol, z2);
}
