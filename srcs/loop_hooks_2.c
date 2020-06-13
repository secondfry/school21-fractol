
#include "loop_hooks.h"

void	set_color_mode(int keycode, t_fractol *ftol)
{
	if (ftol->options & OPTION_MANDELBROT_STEPWISE)
		ftol->options -= OPTION_MANDELBROT_STEPWISE;
	if (ftol->options & OPTION_MANDELBROT_GRAYSCALE)
		ftol->options -= OPTION_MANDELBROT_GRAYSCALE;
	if (ftol->options & OPTION_MANDELBROT_COLOR)
		ftol->options -= OPTION_MANDELBROT_COLOR;
	keycode == KEY_A ? ftol->options |= OPTION_MANDELBROT_STEPWISE : 0;
	keycode == KEY_S ? ftol->options |= OPTION_MANDELBROT_GRAYSCALE : 0;
	keycode == KEY_D ? ftol->options |= OPTION_MANDELBROT_COLOR : 0;
	ftol->flags |= FLAG_REDRAW;
}

int		loop_key_hook(int keycode, t_fractol *ftol)
{
	keycode == KEY_ESC ? loop_destroy_hook() : 0;
	//	keycode == KEY_Q ? move_camera(fdf, keycode) : 0;
	//	keycode == KEY_W ? move_camera(fdf, keycode) : 0;
	//	keycode == KEY_E ? move_camera(fdf, keycode) : 0;
	keycode == KEY_A ? set_color_mode(keycode, ftol) : 0;
	keycode == KEY_S ? set_color_mode(keycode, ftol) : 0;
	keycode == KEY_D ? set_color_mode(keycode, ftol) : 0;
	keycode == KEY_F ? ftol->options ^= OPTION_MANDELBROT_ANIMATED : 0;
	//	keycode == KEY_R ? fdf->options ^= OPTION_ENABLE_ROTATION : 0;
	//	keycode == KEY_T ? force_isometric(fdf) : 0;
	//	keycode == KEY_G ? reset_rotation(fdf) : 0;
	//	keycode == KEY_Z ? fdf->options ^= OPTION_ROTATION_X : 0;
	//	keycode == KEY_X ? fdf->options ^= OPTION_ROTATION_Y : 0;
	//	keycode == KEY_C ? fdf->options ^= OPTION_ROTATION_Z : 0;
	return (0);
}

