//
// Created by Rustam Gubaydullin on 12/06/2020.
//

#include <stdlib.h>
#include "libft.h"
#include "loop_hooks.h"

int		loop_destroy_hook(void)
{
	ft_putendl("Goodbye!");
	exit(0);
}

int		loop_hook(t_fractol *ftol)
{
	if (!(ftol->flags & FLAG_REDRAW))
		return (0);

	ft_bzero(ftol->img_data, ftol->size_line_char * HEIGHT);
	for (size_t i = 0; i < HEIGHT; i++) {
		ft_bzero(ftol->iteration[i], sizeof(t_ushort) * WIDTH);
	}

	for (size_t y = 0; y < HEIGHT; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			mandelbrot(ftol, x, y);
		}
	}

	//	mandelbrot_2_2(ftol);

	mlx_put_image_to_window(ftol->mlx, ftol->win, ftol->img, 0, 0);
	mlx_do_sync(ftol->mlx);
	return (0);

	loop_calculate_matrix_local_normalization(fdf);
	loop_calculate_matrix_local_scale(fdf);
	loop_calculate_matrix_local_rotation(fdf);
	loop_calculate_matrix_world_translation(fdf);
	loop_calculate_matrix_world_rotation(fdf);
	loop_calculate_matrix_world_projection(fdf);
	loop_calculate_matrix_view(fdf);
	loop_fill_image(fdf);
	loop_put_image(fdf);
	loop_render_hud_1(fdf);
	loop_render_hud_2(fdf);
	loop_before_next_update(fdf);
	return (0);
}
