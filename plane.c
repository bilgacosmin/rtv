/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:39 by cbilga            #+#    #+#             */
/*   Updated: 2020/02/04 09:31:44 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static void	get_color_shadow(t_getcolor *c)
{
	c->magnitude = sqrt(vec3_magnitude(c->light_dir));
	vec3_normalize(&(c->light_dir));
	if (vec3_dot_prod(c->normal, c->light_dir) < 0)
		c->normal = vec3_mult(c->normal, -1);
	c->light = c->light + ((1 - c->light)
		* vec3_dot_prod(c->normal, c->light_dir) / c->magnitude);
}

int			get_color_plane(t_win *win, t_vec3 inter, t_plane *plane)
{
	t_getcolor c;

	c.light = win->ambient_light;
	c.normal = plane->normal;
	vec3_normalize(&(c.normal));
	c.i = 0;
	c.brilliance = 0;
	while (c.i < win->nb_lights)
	{
		c.light_dir = vec3_sub(win->lights[c.i], inter);
		vec3_normalize(&(c.light_dir));
		c.reflect_dir = vec3_sub(inter,
			vec3_add(c.normal, vec3_add(c.normal,
				vec3_add(inter, c.light_dir))));
		vec3_normalize(&(c.reflect_dir));
		if (shadowtrace(win, c.i, inter) > 0)
			get_color_shadow(&c);
		c.i++;
	}
	return (calculate_light(plane->color, c.light, c.brilliance));
}

float		dist_plane(t_vec3 pos, t_vec3 dir, t_plane *plane)
{
	float	t;
	t_vec3	tmp;

	tmp = vec3_sub(plane->point, pos);
	t = vec3_dot_prod(tmp, plane->normal);
	t = t / vec3_dot_prod(dir, plane->normal);
	return (t);
}

int			new_plane(t_win *win, t_plane **plane)
{
	t_plane *new;

	if (!(new = (t_plane*)malloc(sizeof(t_plane))))
		error_handling(win);
	new->type = 2;
	new->point.x = 0;
	new->point.y = 0;
	new->point.z = 120;
	new->normal.x = 0;
	new->normal.y = 0;
	new->normal.z = 1;
	new->color = 0x00F0FFFF;
	*plane = new;
	return (0);
}
