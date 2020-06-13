
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
}

void	loop_render_hud_2(t_fractol *ftol)
{
	char *tmp;

	if (!(ftol->flags & FLAG_REDRAW))
		return ;
	mlx_string_put(ftol->mlx, ftol->win, 10, 130, 0xFFFFF, "Max Iterations:");
	tmp = ft_itoa(ftol->data->final_iterations);
	mlx_string_put(ftol->mlx, ftol->win, 10, 140, 0xFFFFF, tmp);
	ft_memdel((void**)&tmp);
//	tmp = ft_itoa(ftol->camera_position[1]);
//	mlx_string_put(ftol->mlx, ftol->win, 30, 120, 0xFFFFF, tmp);
//	ft_memdel((void**)&tmp);
//	tmp = ft_itoa(ftol->camera_position[2]);
//	mlx_string_put(ftol->mlx, ftol->win, 30, 130, 0xFFFFF, tmp);
//	ft_memdel((void**)&tmp);
//	mlx_string_put(ftol->mlx, ftol->win, 10, 150, 0xFFFFF, "Rotating:");
//	ftol->options & OPTION_ROTATION_X
//	? mlx_string_put(ftol->mlx, ftol->win, 10, 160, 0xFFFFF, "X") : 0;
//	ftol->options & OPTION_ROTATION_Y
//	? mlx_string_put(ftol->mlx, ftol->win, 30, 160, 0xFFFFF, "Y") : 0;
//	ftol->options & OPTION_ROTATION_Z
//	? mlx_string_put(ftol->mlx, ftol->win, 50, 160, 0xFFFFF, "Z") : 0;
}
