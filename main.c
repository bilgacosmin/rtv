/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:54:08 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/16 12:51:51 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

int	main(int argc, char *argv[])
{
	t_win win;

	init_win(&win);
	if (argc >= 2)
		parse(&win, argv[1]);
	else
		parse_objects_empty(&win);
	turn(&win);
	free_window(&win);
	return (0);
}
