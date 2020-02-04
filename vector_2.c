/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:01:55 by cbilga            #+#    #+#             */
/*   Updated: 2020/02/04 08:19:47 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vector.h"
#include <math.h>

void	vec3_normalize(t_vec3 *vec)
{
	float magnitude;

	magnitude = vec3_magnitude(*vec);
	vec->x = vec->x / magnitude;
	vec->y = vec->y / magnitude;
	vec->z = vec->z / magnitude;
}

t_vec3	vec3_cross_prod(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v3;

	v3.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v3);
}

t_vec3	vec3_rotation_x(t_vec3 v1, float angle)
{
	t_vec3 v2;

	v2.x = v1.x;
	v2.y = v1.y * cos(angle) - v1.z * sin(angle);
	v2.z = v1.y * sin(angle) + v1.z * cos(angle);
	return (v2);
}

t_vec3	vec3_rotation_y(t_vec3 v1, float angle)
{
	t_vec3 v2;

	v2.x = v1.x * cos(angle) + v1.z * sin(angle);
	v2.y = v1.y;
	v2.z = -(v1.x * sin(angle)) + v1.z * cos(angle);
	return (v2);
}

t_vec3	vec3_rotation_z(t_vec3 v1, float angle)
{
	t_vec3 v2;

	v2.x = v1.x * cos(angle) - v1.y * sin(angle);
	v2.y = v1.x * sin(angle) + v1.y * cos(angle);
	v2.z = v1.z;
	return (v2);
}
