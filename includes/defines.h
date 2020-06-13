/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:04:51 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/07 07:23:11 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "libft.h"

# define WIDTH 1280
# define HEIGHT 720
# define TITLE "fract-ol"
# define M_LN2_F 0.693147180559945309417232121458176568f
# define M_PI_F 3.14159265358979323846264338327950288f
# define M_PI_2F 1.57079632679489661923132169163975144f
# define M_PI_4F 0.785398163397448309615660845819875721f
# define M_SQRT2_F 1.41421356237309504880168872420969808f
# define M_SQRT1_2_F 0.707106781186547524400844362104849039f
# define SSIZE_T_MAX ((0ul - 1ul) >> 1ul)
# define SSIZE_T_MIN (SSIZE_T_MAX + 1ul)

# define PALETTE 3
# define DEFAULT_HORIZON (1u << 24u)
# define MANDELBROT_BASE_ITERATIONS 50
# define TRICORNE_BASE_ITERATIONS 150
# define BURNING_BASE_ITERATIONS 14
# define JULIA_BASE_ITERATIONS 250
# define ZOOM_ITERATIONS 50

# define EINVAL 22

typedef t_byte	*t_color;

typedef int			(*t_mlx_hook)();

typedef struct		s_ftol_data
{
	double			log2_log_h;
	t_color			*palette;
	double			horizon;
	double			zoom;
	double			kx;
	double			ky;
	double			ox;
	double			oy;
	size_t			base_iterations;
	size_t			zoom_iterations;
	size_t			final_iterations;
	double			(*escape_time)(size_t *, t_ushort, t_ushort, struct s_ftol_data *);
	double			julia_zr;
	double			julia_zi;
}					t_ftol_data;

typedef struct		s_fractol
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*img_data;
	size_t			size_line_int;
	size_t			size_line_char;
	t_byte			options;
	t_byte			flags;
	t_ftol_data		*data;
	double			color_cycle;
}					t_fractol;

# define OPTION_STEPWISE	(1u << 0u)
# define OPTION_GRAYSCALE	(1u << 1u)
# define OPTION_COLOR		(1u << 2u)
# define OPTION_ANIMATED	(1u << 3u)

# define FLAG_REDRAW					(1u << 0u)

# define EVENT_KEY_PRESS						2
# define EVENT_KEY_RELEASE						3
# define EVENT_BUTTON_PRESS						4
# define EVENT_BUTTON_RELEASE					5
# define EVENT_MOTION_NOTIFY					6
# define EVENT_EXPOSE							12
# define EVENT_DESTROY							17

/*
** https://refspecs.linuxfoundation.org/LSB_1.3.0/gLSB/gLSB/libx11-ddefs.html
*/
# define MASK_KEY_PRESS							1ul << 0u
# define MASK_KEY_RELEASE						1ul << 1u
# define MASK_BUTTON_PRESS						1ul << 2u
# define MASK_BUTTON_RELEASE					1ul << 3u
# define MASK_POINTER_MOTION					1ul << 6u
# define MASK_EXPOSE							1ul << 15u
# define MASK_DESTROY							1ul << 17u

# ifdef __APPLE__
#  define KEY_A									0
#  define KEY_S									1
#  define KEY_D									2
#  define KEY_F									3
#  define KEY_G									5
#  define KEY_Q									12
#  define KEY_W									13
#  define KEY_E									14
#  define KEY_R									15
#  define KEY_T									17
#  define KEY_Z									6
#  define KEY_X									7
#  define KEY_C									8
#  define KEY_ESC								53
# else
#  define KEY_A									97
#  define KEY_C									99
#  define KEY_D									100
#  define KEY_E									101
#  define KEY_F									102
#  define KEY_G									103
#  define KEY_H									104
#  define KEY_Q									113
#  define KEY_R									114
#  define KEY_S									115
#  define KEY_T									116
#  define KEY_W									119
#  define KEY_X									120
#  define KEY_Z									122
#  define KEY_ESC								65307
# endif

# define MOUSE_1								1
# define MOUSE_2								2
# define MOUSE_WHEEL_OUT							5
# define MOUSE_WHEEL_IN						4

#endif
