/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:10:10 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/13 16:43:05 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

double	absdiv(double a, double b)
{
	return (dabs(a - b));
}

double	dabs(double v)
{
	return (v < 0 ? -v : v);
}
