
#ifndef COLOR_H
# define COLOR_H

# include "libft.h"
# include "defines.h"

t_color	color_new(t_byte r, t_byte g, t_byte b);
t_color	color_lerp(const t_byte *a, const t_byte *b, double f);
void	color_free(t_color a);

#endif
