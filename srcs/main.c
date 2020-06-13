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

t_mandelbrot	*init_mandelbrot()
{
	t_mandelbrot	*ret;

	ret = (t_mandelbrot *)malloc(sizeof(t_mandelbrot));
	ret->horizon = DEFAULT_HORIZON;
	ret->log2_log_h = log2(log(ret->horizon));
	if (ret->log2_log_h <= 0)
		ret->log2_log_h = 1;
	ret->palette = (t_color *)malloc(sizeof(t_color) * PALETTE);
	ret->palette[0] = color_new(255, 0, 0);
	ret->palette[1] = color_new(0, 255, 0);
	ret->palette[2] = color_new(0, 0, 255);
	ret->zoom = 5.f / WIDTH;
	ret->kx = ret->zoom;
	ret->ky = -1 * ret->zoom;
	ret->ox = -3.25f;
	ret->oy = ret->zoom * HEIGHT / 2.f;
	ret->max_iterations = MAX_ITERATIONS;
	return (ret);
}

void			init_fractol(t_fractol *ftol)
{
	ftol->options = OPTION_MANDELBROT_COLOR | OPTION_MANDELBROT_ANIMATED;
	ftol->flags = FLAG_REDRAW;
	ftol->mandelbrot = init_mandelbrot();
	ftol->color_cycle = 0;
}

int				main(int argc, char **argv)
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
	init_fractol(&ftol);
	mlx_hook(ftol.win, EVENT_KEY_PRESS, MASK_KEY_PRESS, loop_key_hook, &ftol);
	mlx_hook(ftol.win, EVENT_BUTTON_PRESS, MASK_BUTTON_PRESS, &loop_mouse_click_hook, &ftol);
	mlx_hook(ftol.win, EVENT_MOTION_NOTIFY, MASK_POINTER_MOTION, &loop_mouse_move_hook, &ftol);
	mlx_hook(ftol.win, EVENT_DESTROY, MASK_DESTROY, loop_destroy_hook, &ftol);
	mlx_loop_hook(ftol.mlx, loop_hook, &ftol);
	mlx_loop(ftol.mlx);

	return (ft_atoi(argv[argc - 1]));
}
