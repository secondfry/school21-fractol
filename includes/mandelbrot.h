//
// Created by Rustam Gubaydullin on 12/06/2020.
//

#ifndef MANDELBROT_H
# define MANDELBROT_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "defines.h"
# include "color.h"
# include "utilities.h"

t_byte		mandelbrot_cutoff(
	t_byte init,
	size_t *iteration,
	double x,
	double y,
	t_mandelbrot *mandelbrot
);
double		mandelbrot_escape_time(
	size_t *iteration,
	t_ushort sx,
	t_ushort sy,
	t_mandelbrot *mandelbrot
);
void		mandelbrot(t_fractol *ftol, t_ushort sx, t_ushort sy);

#endif
