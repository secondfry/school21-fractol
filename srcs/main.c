/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:41:36 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_ftol_data	*init_data(void)
{
	t_ftol_data	*ret;

	ret = (t_ftol_data *)malloc(sizeof(t_ftol_data));
	ret->horizon = DEFAULT_HORIZON;
	ret->log2_log_h = log2(log(ret->horizon));
	if (ret->log2_log_h <= 0)
		ret->log2_log_h = 1;
	ret->palette = (t_color *)malloc(sizeof(t_color) * PALETTE);
	ret->palette[0] = color_new(255, 130, 0);
	ret->palette[1] = color_new(255, 255, 255);
	ret->palette[2] = color_new(0, 6, 92);
	ret->zoom = 5.f / WIDTH;
	ret->kx = ret->zoom;
	ret->ky = -1 * ret->zoom;
	ret->ox = -3.25f;
	ret->oy = ret->zoom * HEIGHT / 2.f;
	ret->base_its = MANDELBROT_BASE_ITS;
	ret->zoom_its = ZOOM_ITERATIONS;
	ret->final_its = ret->base_its + ret->zoom_its;
	ret->escape_time = mandelbrot_escape_time;
	ret->julia_zr = -0.4;
	ret->julia_zi = 0.6;
	return (ret);
}

void		init_fractol(t_fractol *ftol)
{
	ftol->options = OPTION_COLOR | OPTION_ANIMATED;
	ftol->flags = FLAG_REDRAW;
	ftol->data = init_data();
	ftol->color_cycle = 0;
}

void		print_usage(char *name)
{
	ft_putstr("Usage: ");
	ft_putstr(name);
	ft_putendl(" (mandelbrot|julia|burning_ship|tricorne)");
}

void		input(t_fractol *ftol, char **argv)
{
	if (ft_strequ(argv[1], "mandelbrot"))
		ftol->data->escape_time = mandelbrot_escape_time;
	else if (ft_strequ(argv[1], "julia"))
		ftol->data->escape_time = julia_escape_time;
	else if (ft_strequ(argv[1], "burning_ship"))
		ftol->data->escape_time = burning_escape_time;
	else if (ft_strequ(argv[1], "tricorne"))
		ftol->data->escape_time = tricorne_escape_time;
	else
	{
		print_usage(argv[0]);
		exit(EINVAL);
	}
}

int			main(int argc, char **argv)
{
	t_fractol	ftol;

	if (argc != 2)
	{
		print_usage(argv[0]);
		return (EINVAL);
	}
	init_fractol(&ftol);
	input(&ftol, argv);
	init_mlx(&ftol);
	mlx_hook(ftol.win, EVENT_KEY_PRESS, MASK_KEY_PRESS,
		loop_key_hook, &ftol);
	mlx_hook(ftol.win, EVENT_BUTTON_PRESS, MASK_BUTTON_PRESS,
		&loop_mouse_click_hook, &ftol);
	mlx_hook(ftol.win, EVENT_MOTION_NOTIFY, MASK_POINTER_MOTION,
		&loop_mouse_move_hook, &ftol);
	mlx_hook(ftol.win, EVENT_DESTROY, MASK_DESTROY,
		loop_destroy_hook, &ftol);
	mlx_loop_hook(ftol.mlx, loop_hook, &ftol);
	mlx_loop(ftol.mlx);
	return (0);
}
