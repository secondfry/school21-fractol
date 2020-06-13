
#include <stdlib.h>
#include "mlx.h"

#include "mlx_init.h"

void		init_mlx(t_fractol *ftol)
{
	int bits_per_pixel;
	int size_line;
	int endianess;

	ftol->mlx = mlx_init();
	ft_ptr_check(ftol->mlx, "[main] mlx_init errored.", 0);
	ftol->win = mlx_new_window(ftol->mlx, WIDTH, HEIGHT, TITLE);
	ft_ptr_check(ftol->win, "[main] mlx_new_window errored.", 1, ftol->mlx);
	ftol->img = mlx_new_image(ftol->mlx, WIDTH, HEIGHT);
	if (!ftol->img)
	{
		ft_putstr("[main] mlx_new_image errored.");
		mlx_destroy_window(ftol->mlx, ftol->win);
		ft_memdel(&(ftol->mlx));
		exit(ENOMEM);
	}
	ftol->img_data = (int *)mlx_get_data_addr(
		ftol->img, &bits_per_pixel, &size_line, &endianess);
	ftol->size_line_char = (size_t)size_line;
	ftol->size_line_int = (size_t)(size_line / 4);
}
