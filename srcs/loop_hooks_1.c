
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
	loop_before_next_update(ftol);
	return (0);
}

void	loop_mandelbrot_palette(t_fractol *ftol)
{
	if (!(ftol->options & OPTION_ANIMATED))
		return;
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

void	calculate_offset(t_ftol_data *mandelbrot, int mouseX, int mouseY)
{
	mandelbrot->ox += (double)mouseX * (mandelbrot->kx - mandelbrot->zoom);
	mandelbrot->oy += (double)(HEIGHT - mouseY) * (mandelbrot->ky + mandelbrot->zoom);
	mandelbrot->kx = mandelbrot->zoom;
	mandelbrot->ky = -1 * mandelbrot->zoom;
}

int		loop_mouse_click_hook(int mousecode, int x, int y, t_fractol *ftol)
{
	mousecode == MOUSE_WHEEL_OUT ? ftol->data->zoom *= 1.1 : 0;
	mousecode == MOUSE_WHEEL_OUT ? ftol->data->zoom_iterations-- : 0;
	mousecode == MOUSE_WHEEL_IN ? ftol->data->zoom *= 0.9 : 0;
	mousecode == MOUSE_WHEEL_IN ? ftol->data->zoom_iterations++ : 0;
	ftol->data->zoom_iterations < 10 ? ftol->data->zoom_iterations = 10 : 0;
	ftol->data->final_iterations = ftol->data->base_iterations + ftol->data->zoom_iterations;
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
