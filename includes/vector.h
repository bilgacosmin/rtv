/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:00:41 by cbilga            #+#    #+#             */
/*   Updated: 2020/02/04 12:06:59 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vec3
{
	float x;
	float y;
	float z;
}				t_vec3;

void			vec3_normalize (t_vec3 *vec);
t_vec3			vec3_cross_prod(t_vec3 v1, t_vec3 v2);
float			vec3_dot_prod(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_mult(t_vec3 v1, float i);
float			vec3_magnitude(t_vec3 v);
t_vec3			vec3_rotation_x(t_vec3 v1, float angle);
t_vec3			vec3_rotation_y(t_vec3 v1, float angle);
t_vec3			vec3_rotation_z(t_vec3 v1, float angle);
#endif
