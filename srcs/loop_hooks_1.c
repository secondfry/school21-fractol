
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
	loop_before_next_update(ftol);
	return (0);
}

#include <math.h>

void	loop_mandelbrot_palette(t_fractol *ftol)
{
	t_byte	major;
	t_byte	minor;
	t_color	color[3];

	if (!(ftol->options & OPTION_MANDELBROT_ANIMATED))
		return;
	ft_memdel((void **)ftol->mandelbrot->animated_palette + 0);
	ft_memdel((void **)ftol->mandelbrot->animated_palette + 1);
	ft_memdel((void **)ftol->mandelbrot->animated_palette + 2);
	ftol->mandelbrot->animated_palette[0] = color_lerp(ftol->mandelbrot->palette[0], ftol->mandelbrot->palette[1], (float)ftol->frame / 255);
	ftol->mandelbrot->animated_palette[1] = color_lerp(ftol->mandelbrot->palette[1], ftol->mandelbrot->palette[2], (float)ftol->frame / 255);
	ftol->mandelbrot->animated_palette[2] = color_lerp(ftol->mandelbrot->palette[2], ftol->mandelbrot->palette[0], (float)ftol->frame / 255);
	color[1] = color_lerp(ftol->mandelbrot->palette[1], ftol->mandelbrot->palette[2], (float)ftol->frame / 255);
	color[2] = color_lerp(ftol->mandelbrot->palette[2], ftol->mandelbrot->palette[0], (float)ftol->frame / 255);
	ftol->frame = ftol->frame + 10;
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
			mandelbrot(ftol, x, y);
			x++;
		}
		y++;
	}
	ftol->flags -= FLAG_REDRAW;
}

void	loop_before_next_update(t_fractol *ftol)
{
	mlx_put_image_to_window(ftol->mlx, ftol->win, ftol->img, 0, 0);
	mlx_do_sync(ftol->mlx);
	if (ftol->options & OPTION_MANDELBROT_ANIMATED)
		ftol->flags |= FLAG_REDRAW;
}
