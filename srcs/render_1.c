/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:51:50 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int			color_stepwise(size_t iteration)
{
	return ((int)(iteration * 0x111111) & 0x00ffffff);
}

int			color_grayscale(size_t iteration, t_fractol *ftol, double z2)
{
	double	log_zn;
	double	smth;

	log_zn = log(z2) / 2;
	if (log_zn <= 0)
		log_zn = 1;
	smth = iteration - log2(log_zn) + ftol->data->log2_log_h;
	return ((int)(255 * smth / ftol->data->final_its) * 0x10101 & 0x00ffffff);
}

int			color_color(size_t iteration, t_fractol *ftol, double z2)
{
	double	log_zn;
	double	smth;
	t_byte	c[3];
	t_color	color[2];
	double	f;

	log_zn = log(z2) / 2;
	if (log_zn <= 0)
		log_zn = 1;
	smth = iteration - log2(log_zn) + ftol->data->log2_log_h;
	if (ftol->options & OPTION_ANIMATED)
		smth += ftol->color_cycle;
	smth = pow(smth, 0.45);
	color[0] = ftol->data->palette[(int)smth % PALETTE];
	color[1] = ftol->data->palette[((int)smth + 1) % PALETTE];
	f = fmod(smth, 1.f);
	c[0] = color[0][0] + f * (color[1][0] - color[0][0]);
	c[1] = color[0][1] + f * (color[1][1] - color[0][1]);
	c[2] = color[0][2] + f * (color[1][2] - color[0][2]);
	return (c[0] << 16u | c[1] << 8u | c[2]);
}

void		render(t_fractol *ftol, t_ushort sx, t_ushort sy)
{
	size_t	iteration;
	size_t	z2;

	iteration = 0;
	z2 = ftol->data->escape_time(&iteration, sx, sy, ftol->data);
	if (iteration >= ftol->data->final_its)
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
