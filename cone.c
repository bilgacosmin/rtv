/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:50:54 by cbilga            #+#    #+#             */
/*   Updated: 2020/02/04 09:25:33 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static void	get_color_shadow(t_getcolor *c, t_vec3 ray)
{
	c->magnitude = sqrt(vec3_magnitude(c->light_dir));
	if (vec3_dot_prod(c->normal, c->light_dir) < 0)
		c->normal = vec3_mult(c->normal, -1);
	if (vec3_dot_prod(ray, c->reflect_dir) > 0.995 &&
		vec3_dot_prod(ray, c->reflect_dir) > c->brilliance)
		c->brilliance = vec3_dot_prod(ray, c->reflect_dir);
	c->light = c->light + ((1 - c->light)
		* vec3_dot_prod(c->normal, c->light_dir) / c->magnitude);
}

t_vec3		get_cone_normal(t_cone *cone, t_vec3 point)
{
	t_vec3 flank;
	t_vec3 tmp;
	t_vec3 normal;

	flank = vec3_sub(cone->point, point);
	tmp = vec3_cross_prod(flank, cone->axis);
	normal = vec3_cross_prod(flank, tmp);
	vec3_normalize(&normal);
	return (normal);
}

int			get_color_cone(t_win *win, t_vec3 inter, t_cone *cone, t_vec3 ray)
{
	t_getcolor c;

	c.light = win->ambient_light;
	c.normal = get_cone_normal(cone, inter);
	c.i = 0;
	c.brilliance = 0;
	while (c.i < win->nb_lights)
	{
		c.light_dir = vec3_sub(win->lights[c.i], inter);
		vec3_normalize(&c.light_dir);
		c.reflect_dir = vec3_sub(inter, vec3_add(c.normal,
			vec3_add(c.normal, vec3_add(inter, c.light_dir))));
		vec3_normalize(&c.reflect_dir);
		if (shadowtrace(win, c.i, inter) > 0)
			get_color_shadow(&c, ray);
		c.i++;
	}
	return (calculate_light(cone->color, c.light, c.brilliance));
}

float		dist_cone(t_vec3 pos, t_vec3 dir, t_cone *cone)
{
	float	t[7];
	t_vec3	c_pos;

	t[6] = cos(cone->angle) * cos(cone->angle);
	c_pos = vec3_sub(cone->point, pos);
	t[2] = vec3_dot_prod(dir, cone->axis);
	t[2] = (t[2] * t[2]) - t[6];
	t[3] = 2 * ((vec3_dot_prod(dir, cone->axis)
		* vec3_dot_prod(c_pos, cone->axis))
		- (vec3_dot_prod(dir, c_pos) * t[6]));
	t[4] = vec3_dot_prod(c_pos, cone->axis);
	t[4] = (t[4] * t[4]) - (vec3_dot_prod(c_pos, vec3_mult(c_pos, t[6])));
	t[5] = (t[3] * t[3]) - (4 * t[2] * t[4]);
	if (t[5] < -0.001 || t[2] == 0)
		return (-1.0);
	t[0] = -(-t[3] + sqrt(t[5])) / (2 * t[2]);
	t[1] = -(-t[3] - sqrt(t[5])) / (2 * t[2]);
	return (check_t(t[0], t[1]));
}

int			new_cone(t_win *win, t_cone **cone)
{
	t_cone *new;

	if (!(new = (t_cone*)malloc(sizeof(t_cone))))
		error_handling(win);
	new->type = 3;
	new->point.x = 0;
	new->point.y = 0;
	new->point.z = 40;
	new->axis.x = -1;
	new->axis.y = -1;
	new->axis.z = 0;
	vec3_normalize(&(new->axis));
	new->angle = M_PI / 13;
	new->color = 0xFF0000FF;
	*cone = new;
	return (0);
}
