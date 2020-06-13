/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hooks_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:32:52 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loop_hooks.h"

int		loop_destroy_hook(void)
{
	ft_putendl("Goodbye!");
	exit(0);
}

int		loop_hook(t_fractol *ftol)
{
	loop_mandelbrot_palette(ftol);
	loop_fractol(ftol);
	loop_render_hud_1(ftol);
	loop_render_hud_2(ftol);
	loop_render_hud_3(ftol);
	loop_before_next_update(ftol);
	return (0);
}

void	loop_mandelbrot_palette(t_fractol *ftol)
{
	if (!(ftol->options & OPTION_ANIMATED))
		return ;
	ftol->color_cycle += 1;
	ftol->flags |= FLAG_REDRAW;
}

void	loop_fractol(t_fractol *ftol)
{
	t_ushort x;
	t_ushort y;

	if (!(ftol->flags & FLAG_REDRAW))
		return ;
	ft_bzero(ftol->img_data, ftol->size_line_char * HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render(ftol, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(ftol->mlx, ftol->win, ftol->img, 0, 0);
}

void	loop_before_next_update(t_fractol *ftol)
{
	mlx_do_sync(ftol->mlx);
	if (ftol->options & FLAG_REDRAW)
		ftol->flags -= FLAG_REDRAW;
	if (ftol->options & OPTION_ANIMATED)
		ftol->flags |= FLAG_REDRAW;
}
