/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hooks_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:32:23 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/14 19:44:51 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hooks.h"

void	calculate_offset(t_ftol_data *data, int mx, int my)
{
	data->ox += (double)mx * (data->kx - data->zoom);
#ifdef MLX_MACOS_METAL
	data->oy += (double)(HEIGHT - my) * (data->ky + data->zoom);
#else
	data->oy += (double)my * (data->ky + data->zoom);
#endif
	data->kx = data->zoom;
	data->ky = -1 * data->zoom;
}

int		loop_mouse_click_hook(int mousecode, int x, int y, t_fractol *ftol)
{
	mousecode == MOUSE_WHEEL_OUT ? ftol->data->zoom *= 1.1 : 0;
	mousecode == MOUSE_WHEEL_OUT ? ftol->data->zoom_its-- : 0;
	mousecode == MOUSE_WHEEL_IN ? ftol->data->zoom *= 0.9 : 0;
	mousecode == MOUSE_WHEEL_IN ? ftol->data->zoom_its++ : 0;
	ftol->data->zoom_its < 10 ? ftol->data->zoom_its = 10 : 0;
	ftol->data->final_its = ftol->data->base_its + ftol->data->zoom_its;
	calculate_offset(ftol->data, x, y);
	ftol->flags |= FLAG_REDRAW;
	return (0);
}

int		loop_mouse_move_hook(int x, int y, t_fractol *ftol)
{
	ftol->data->julia_zr = 2.f * x / WIDTH - 1;
	ftol->data->julia_zi = 2.f * y / HEIGHT - 1;
	return (0);
}
