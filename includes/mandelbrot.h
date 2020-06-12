//
// Created by Rustam Gubaydullin on 12/06/2020.
//

#ifndef MANDELBROT_H
# define MANDELBROT_H

# include "libft.h"
# include "defines.h"

t_byte		mandelbrot_cutoff(
	t_byte init,
	size_t *iteration,
	double x,
	double y
);
double		mandelbrot_escape_time(size_t *iteration, t_ushort sx, t_ushort sy);
void		mandelbrot(t_fractol *ftol, t_ushort sx, t_ushort sy);

#endif
