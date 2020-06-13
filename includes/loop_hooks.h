/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hooks.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:22:42 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOP_HOOKS_H
# define LOOP_HOOKS_H

# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include "defines.h"
# include "render.h"
# include "color.h"

int		loop_destroy_hook(void);
int		loop_hook(t_fractol *ftol);
int		loop_key_hook(int keycode, t_fractol *ftol);
void	loop_mandelbrot_palette(t_fractol *ftol);
void	loop_fractol(t_fractol *ftol);
void	loop_before_next_update(t_fractol *ftol);
int		loop_mouse_click_hook(int mousecode, int x, int y, t_fractol *ftol);
int		loop_mouse_move_hook(int x, int y, t_fractol *ftol);
void	loop_render_hud_1(t_fractol *ftol);
void	loop_render_hud_2(t_fractol *ftol);
void	loop_render_hud_3(t_fractol *ftol);

#endif
