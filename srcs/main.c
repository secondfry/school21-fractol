/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadhesiv <oadhesiv@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:00:03 by oadhesiv          #+#    #+#             */
/*   Updated: 2020/06/01 06:03:56 by oadhesiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_init.h"
#include "loop_hooks.h"

int			main(int argc, char **argv)
{
	t_fractol	ftol;

//	if (argc != 2)
//	{
//		ft_putendl_fd("Provide one valid map file argument, please.", 2);
//		return (EINVAL);
//	}
//	init_pipeline(&ftol);
//	input(&ftol, argv[argc - 1]);
	init_mlx(&ftol);
//	mlx_hook(ftol.win, EVENT_KEY_PRESS, MASK_KEY_PRESS, loop_key_hook, &ftol);
//	mlx_hook(ftol.win, EVENT_DESTROY, MASK_DESTROY, loop_destroy_hook, &ftol);
	mlx_loop_hook(ftol.mlx, loop_hook, &ftol);
	mlx_loop(ftol.mlx);

	return (ft_atoi(argv[argc - 1]));
}
