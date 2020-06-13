//
// Created by Rustam Gubaydullin on 12/06/2020.
//

#ifndef RENDER_H
# define RENDER_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "defines.h"
# include "color.h"
# include "utilities.h"

t_byte		cutoff(
	t_byte init,
	size_t *iteration,
	double x,
	double y,
	t_ftol_data *data
);
double		julia_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
);
double		tricorne_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
);
double		burning_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
);
double		mandelbrot_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_ftol_data *data
);
void		render(t_fractol *ftol, t_ushort sx, t_ushort sy);

#endif
