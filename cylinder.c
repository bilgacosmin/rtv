/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:51:58 by cbilga            #+#    #+#             */
/*   Updated: 2020/02/04 09:25:57 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static void	get_color_shadow(t_getcolor *c, t_vec3 ray)
{
	c->magnitude = sqrt(vec3_magnitude(c->light_dir));
	vec3_normalize(&(c->light_dir));
	if (vec3_dot_prod(c->normal, c->light_dir) < 0)
		c->normal = vec3_mult(c->normal, -1);
	if (vec3_dot_prod(ray, c->reflect_dir) > 0.995
		&& vec3_dot_prod(ray, c->reflect_dir) > c->brilliance)
		c->brilliance = vec3_dot_prod(ray, c->reflect_dir);
	c->light = c->light + ((1 - c->light)
		* vec3_dot_prod(c->normal, c->light_dir) / c->magnitude);
}

t_vec3		get_cylinder_normal(t_cylinder *cylinder, t_vec3 point)
{
	t_vec3 flank;
	t_vec3 tmp;
	t_vec3 normal;

	flank = vec3_sub(cylinder->point, point);
	tmp = vec3_cross_prod(flank, cylinder->axis);
	normal = vec3_cross_prod(cylinder->axis, tmp);
	vec3_normalize(&normal);
	return (normal);
}

int			get_color_cylinder(t_win *win, t_vec3 inter,
				t_cylinder *cylinder, t_vec3 ray)
{
	t_getcolor c;

	c.light = win->ambient_light;
	c.normal = get_cylinder_normal(cylinder, inter);
	c.i = 0;
	c.brilliance = 0;
	while (c.i < win->nb_lights)
	{
		c.light_dir = vec3_sub(win->lights[c.i], inter);
		vec3_normalize(&(c.light_dir));
		c.reflect_dir = vec3_sub(inter, vec3_add(c.normal,
			vec3_add(c.normal, vec3_add(inter, c.light_dir))));
		vec3_normalize(&(c.reflect_dir));
		if (shadowtrace(win, c.i, inter) > 0)
			get_color_shadow(&c, ray);
		c.i++;
	}
	return (calculate_light(cylinder->color, c.light, c.brilliance));
}

float		dist_cylinder(t_vec3 pos, t_vec3 dir, t_cylinder *cylinder)
{
	float	t[6];
	t_vec3	c_pos;
	t_vec3	tmp;

	c_pos = vec3_cross_prod(cylinder->axis, dir);
	tmp = vec3_cross_prod(cylinder->axis, vec3_sub(pos, cylinder->point));
	t[2] = vec3_dot_prod(c_pos, c_pos);
	t[3] = vec3_dot_prod(c_pos,
		vec3_cross_prod(cylinder->axis,
			vec3_sub(pos, cylinder->point))) * 2;
	t[4] = vec3_dot_prod(tmp, tmp) - (cylinder->r * cylinder->r);
	t[5] = (t[3] * t[3]) - (4 * t[2] * t[4]);
	if (t[5] < 0 || t[2] == 0)
		return (-1.0);
	t[0] = (-t[3] + sqrt(t[5])) / (2 * t[2]);
	t[1] = (-t[3] - sqrt(t[5])) / (2 * t[2]);
	if (t[0] > 0 && t[1] > 0)
	{
		if (t[0] > t[1])
			return (t[1]);
	}
	return (-1);
}

int			new_cylinder(t_win *win, t_cylinder **cylinder)
{
	t_cylinder *new;

	if (!(new = (t_cylinder*)malloc(sizeof(t_cylinder))))
		error_handling(win);
	new->type = 4;
	new->point.x = 1;
	new->point.y = 0;
	new->point.z = 30;
	new->axis.x = 0;
	new->axis.y = -1;
	new->axis.z = 0;
	new->r = 1.56;
	new->color = 0xFFCC00FF;
	*cylinder = new;
	return (0);
}
