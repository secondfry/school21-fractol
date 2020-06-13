/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:53:47 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** https://blog.datalore.io/how_to_plot_mandelbrot_set/
** https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
** https://en.wikipedia.org/wiki/Julia_set
** https://en.wikipedia.org/wiki/Tricorn_(mathematics)
** https://en.wikipedia.org/wiki/Burning_Ship_fractal
*/

t_byte		cutoff(
	size_t *iteration,
	double x,
	double y,
	t_ftol_data *data
)
{
	static double	oldx;
	static double	oldy;
	static t_byte	period;

	if (*iteration == 0)
	{
		oldx = 0;
		oldy = 0;
		period = 0;
		return (0);
	}
	if (absdiv(x, oldx) < 0.00001 && absdiv(y, oldy) < 0.00001)
	{
		*iteration = data->final_its;
		return (1);
	}
	period++;
	if (period > 20)
	{
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
	while (x * x + y * y <= 4 && *iteration < data->final_its)
	{
		y = 2 * x * y + data->julia_zi;
		x = x2 - y2 + data->julia_zr;
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
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
	cutoff(iteration, 0, 0, data);
	while (x2 + y2 <= 4 && *iteration < data->final_its)
	{
		y = -2 * x * y + c[1];
		x = x2 - y2 + c[0];
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (cutoff(iteration, x, y, data))
			break ;
	}
	return (x2 + y2);
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
	cutoff(iteration, 0, 0, data);
	while (x2 + y2 <= 4 && *iteration < data->final_its)
	{
		y = dabs(2 * x * y + c[1]);
		x = dabs(x2 - y2 + c[0]);
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (cutoff(iteration, x, y, data))
			break ;
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
	cutoff(iteration, 0, 0, data);
	while (x2 + y2 <= data->horizon && *iteration < data->final_its)
	{
		y = 2 * x * y + c[1];
		x = x2 - y2 + c[0];
		x2 = x * x;
		y2 = y * y;
		*iteration = *iteration + 1;
		if (cutoff(iteration, x, y, data))
			break ;
	}
	return (x2 + y2);
}
