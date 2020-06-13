/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:51:49 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "defines.h"
# include "color.h"
# include "utilities.h"

t_byte		cutoff(
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
