/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:58 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/13 17:16:59 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"
#include <math.h>

t_vec3 vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec3 vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return(result);
}

t_vec3 vec3_mult(t_vec3 v1, float i)
{
	t_vec3 result;

	result.x = v1.x * i;
	result.y = v1.y * i;
	result.z = v1.z * i;
	return(result);
}

float vec3_magnitude(t_vec3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

float vec3_dot_prod(t_vec3 v1, t_vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

void vec3_normalize(t_vec3 *vec)
{
	float magnitude;

	magnitude = vec3_magnitude(*vec);
	vec->x = vec->x / magnitude;
	vec->y = vec->y / magnitude;
	vec->z = vec->z / magnitude;
}

t_vec3 vec3_cross_prod(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v3;

	v3.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (v3);
}

t_vec3 vec3_rotation_x(t_vec3 v1, float angle)
{
	t_vec3 v2;

	v2.x = v1.x;
	v2.y = v1.y * cos(angle) - v1.z * sin(angle);
	v2.z = v1.y * sin(angle) + v1.z * cos(angle);
	return (v2);
}

t_vec3 vec3_rotation_y(t_vec3 v1, float angle)
{
	t_vec3 v2;

	v2.x = v1.x * cos(angle) + v1.z * sin(angle);
	v2.y = v1.y;
	v2.z = -(v1.x * sin(angle)) + v1.z * cos(angle);
	return (v2);
}

t_vec3 vec3_rotation_z(t_vec3 v1, float angle)
{
	t_vec3 v2;

	v2.x = v1.x * cos(angle) - v1.y * sin(angle); 
	v2.y = v1.x * sin(angle) + v1.y * cos(angle);
	v2.z = v1.z;
	return (v2);
}