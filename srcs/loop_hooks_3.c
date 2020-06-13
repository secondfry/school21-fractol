
#include "loop_hooks.h"

void	loop_render_hud_1(t_fractol *ftol)
{
	if (!(ftol->flags & FLAG_REDRAW))
		return ;
	mlx_string_put(ftol->mlx, ftol->win, 10, 20, 0xFFFFF,
		"Q: Mandelbrot");
	mlx_string_put(ftol->mlx, ftol->win, 10, 30, 0xFFFFF,
		"W: Tricorne");
	mlx_string_put(ftol->mlx, ftol->win, 10, 40, 0xFFFFF,
		"E: Burning Ship");
	mlx_string_put(ftol->mlx, ftol->win, 10, 50, 0xFFFFF,
		"R: Julia");
	mlx_string_put(ftol->mlx, ftol->win, 10, 70, 0xFFFFF,
		"A: Stepwise");
	mlx_string_put(ftol->mlx, ftol->win, 10, 80, 0xFFFFF,
		"S: Grayscale");
	mlx_string_put(ftol->mlx, ftol->win, 10, 90, 0xFFFFF,
		"D: Color");
	mlx_string_put(ftol->mlx, ftol->win, 10, 110, 0xFFFFF,
		"F: Animate Color (requires Color mode)");
	mlx_string_put(ftol->mlx, ftol->win, 10, 180, 0xFFFFF,
		"Mouse Wheel: Zoom");
	mlx_string_put(ftol->mlx, ftol->win, 10, 190, 0xFFFFF,
		"Mouse Click and Move: Julia Transform");
}

void	loop_render_hud_2(t_fractol *ftol)
{
	char *tmp;

	if (!(ftol->flags & FLAG_REDRAW))
		return ;
	mlx_string_put(ftol->mlx, ftol->win, 10, 130, 0xFFFFF, "Max Iterations:");
	mlx_string_put(ftol->mlx, ftol->win, 10, 140, 0xFFFFF, "          Zoom:");
	mlx_string_put(ftol->mlx, ftol->win, 10, 150, 0xFFFFF, "      Offset X:");
	mlx_string_put(ftol->mlx, ftol->win, 10, 160, 0xFFFFF, "             Y:");
	tmp = ft_itoa(ftol->data->final_iterations);
	mlx_string_put(ftol->mlx, ftol->win, 120, 130, 0xFFFFF, tmp);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa((int)(ftol->data->zoom * 10000));
	if ((int)(ftol->data->zoom * 1000000) < 1)
		mlx_string_put(ftol->mlx, ftol->win, 120, 140, 0xFFFFF, "jal y menya net printf");
	else if ((int)(ftol->data->zoom * 100000) < 1)
		mlx_string_put(ftol->mlx, ftol->win, 120, 140, 0xFFFFF, "?????");
	else if ((int)(ftol->data->zoom * 10000) < 1)
		mlx_string_put(ftol->mlx, ftol->win, 120, 140, 0xFFFFF, "?");
	else
		mlx_string_put(ftol->mlx, ftol->win, 120, 140, 0xFFFFF, tmp);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa((int)(ftol->data->ox * 10000));
	mlx_string_put(ftol->mlx, ftol->win, 120, 150, 0xFFFFF, tmp);
	ft_memdel((void**)&tmp);
	tmp = ft_itoa((int)(ftol->data->oy * 10000));
	mlx_string_put(ftol->mlx, ftol->win, 120, 160, 0xFFFFF, tmp);
	ft_memdel((void**)&tmp);
}
