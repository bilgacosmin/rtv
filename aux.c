/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:44:57 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/21 08:55:48 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

float	to_radian(float angle)
{
	return (angle * M_PI / 180.0);
}

float	check_t(float t0, float t1)
{
	if (t0 > 0 && t1 > 0)
	{
		if (t0 > t1)
			return (t1);
		return (t0);
	}
	if (t0 > 0)
		return (t0);
	if (t1 > 0)
		return (t1);
	return (-1);
}
