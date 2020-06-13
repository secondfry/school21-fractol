/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hooks_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:25:51 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hooks.h"

void	set_color_mode(int keycode, t_fractol *ftol)
{
	if (ftol->options & OPTION_STEPWISE)
		ftol->options -= OPTION_STEPWISE;
	if (ftol->options & OPTION_GRAYSCALE)
		ftol->options -= OPTION_GRAYSCALE;
	if (ftol->options & OPTION_COLOR)
		ftol->options -= OPTION_COLOR;
	keycode == KEY_A ? ftol->options |= OPTION_STEPWISE : 0;
	keycode == KEY_S ? ftol->options |= OPTION_GRAYSCALE : 0;
	keycode == KEY_D ? ftol->options |= OPTION_COLOR : 0;
}

void	set_escape_time(int keycode, t_fractol *ftol)
{
	keycode == KEY_Q ? ftol->data->escape_time = mandelbrot_escape_time : 0;
	keycode == KEY_Q ? ftol->data->base_its = MANDELBROT_BASE_ITS : 0;
	keycode == KEY_W ? ftol->data->escape_time = tricorne_escape_time : 0;
	keycode == KEY_W ? ftol->data->base_its = TRICORNE_BASE_ITS : 0;
	keycode == KEY_E ? ftol->data->escape_time = burning_escape_time : 0;
	keycode == KEY_E ? ftol->data->base_its = BURNING_BASE_ITS : 0;
	keycode == KEY_R ? ftol->data->escape_time = julia_escape_time : 0;
	keycode == KEY_R ? ftol->data->base_its = JULIA_BASE_ITS : 0;
	ftol->data->final_its = ftol->data->base_its + ftol->data->zoom_its;
}

int		loop_key_hook(int keycode, t_fractol *ftol)
{
	keycode == KEY_ESC ? loop_destroy_hook() : 0;
	keycode == KEY_Q ? set_escape_time(keycode, ftol) : 0;
	keycode == KEY_W ? set_escape_time(keycode, ftol) : 0;
	keycode == KEY_E ? set_escape_time(keycode, ftol) : 0;
	keycode == KEY_R ? set_escape_time(keycode, ftol) : 0;
	keycode == KEY_A ? set_color_mode(keycode, ftol) : 0;
	keycode == KEY_S ? set_color_mode(keycode, ftol) : 0;
	keycode == KEY_D ? set_color_mode(keycode, ftol) : 0;
	keycode == KEY_F ? ftol->options ^= OPTION_ANIMATED : 0;
	keycode == KEY_T ? ftol->data->zoom_its += 10 : 0;
	keycode == KEY_G ? ftol->data->zoom_its -= 10 : 0;
	ftol->data->zoom_its < 10 ? ftol->data->zoom_its = 10 : 0;
	ftol->data->final_its = ftol->data->base_its + ftol->data->zoom_its;
	ftol->flags |= FLAG_REDRAW;
	return (0);
}
