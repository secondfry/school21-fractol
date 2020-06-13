/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:25:12 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	color_new(t_byte r, t_byte g, t_byte b)
{
	t_color	ret;

	ret = (t_color)malloc(sizeof(t_byte) * 3);
	ret[0] = r;
	ret[1] = g;
	ret[2] = b;
	return (ret);
}

t_color	color_lerp(const t_byte *a, const t_byte *b, double f)
{
	return (color_new(
		a[0] + f * (b[0] - a[0]),
		a[1] + f * (b[1] - a[1]),
		a[2] + f * (b[2] - a[2])));
}

void	color_free(t_color a)
{
	ft_memdel((void **)&a);
}
