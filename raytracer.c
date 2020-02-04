/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:44 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/21 13:02:33 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

float			collision(t_win *win, int i, t_vec3 pos, t_vec3 ray)
{
	float t;

	t = 0;
	if (((t_sphere*)(win->objects[i]))->type == 1)
		t = dist_sphere(pos, ray, (t_sphere*)(win->objects[i]));
	if (((t_plane*)(win->objects[i]))->type == 2)
		t = dist_plane(pos, ray, (t_plane*)(win->objects[i]));
	if (((t_cone*)(win->objects[i]))->type == 3)
		t = dist_cone(pos, ray, (t_cone*)(win->objects[i]));
	if (((t_cylinder*)(win->objects[i]))->type == 4)
		t = dist_cylinder(pos, ray, (t_cylinder*)(win->objects[i]));
	return (t);
}

unsigned int	get_color(t_win *win, int obj, t_vec3 ray, float t)
{
	t_vec3	inter;
	int		color;

	win->depth++;
	inter.x = win->camera.position.x + (ray.x * t);
	inter.y = win->camera.position.y + (ray.y * t);
	inter.z = win->camera.position.z + (ray.z * t);
	if (((t_sphere*)win->objects[obj])->type == 1)
		color = get_color_sphere(win, inter, (t_sphere*)win->objects[obj], ray);
	if (((t_plane*)win->objects[obj])->type == 2)
		color = get_color_plane(win, inter, (t_plane*)win->objects[obj]);
	if (((t_cone*)win->objects[obj])->type == 3)
		color = get_color_cone(win, inter, (t_cone*)win->objects[obj], ray);
	if (((t_cylinder*)win->objects[obj])->type == 4)
		color = get_color_cylinder(win, inter,
			(t_cylinder*)win->objects[obj], ray);
	win->depth--;
	return (color);
}

int				raytrace(t_win *win, t_vec3 pos, t_vec3 ray)
{
	float	t;
	float	tmp;
	int		pick;
	int		i;

	t = 1000001.0;
	i = 0;
	pick = -1;
	if (win->depth >= win->max_depth)
		return (-1);
	while (i < win->nb_obj)
	{
		tmp = collision(win, i, pos, ray);
		if (tmp > 0 && tmp < t)
		{
			t = tmp;
			pick = i;
		}
		i++;
	}
	if (t > 1000000)
		return (0x000000FF);
	else
		return (get_color(win, pick, ray, t));
	return (t);
}

int				shadowtrace(t_win *win, int light, t_vec3 inter)
{
	t_vec3	ray;
	t_vec3	norm_ray;
	int		i;

	i = 0;
	ray = vec3_sub(win->lights[light], inter);
	norm_ray = ray;
	vec3_normalize(&norm_ray);
	inter = vec3_add(vec3_mult(ray, 0.0001), inter);
	while (i < win->nb_obj)
	{
		if (collision(win, i, inter, norm_ray) > 0
			&& collision(win, i, inter, norm_ray) < vec3_magnitude(ray))
		{
			return (-1);
		}
		i++;
	}
	return (1);
}
