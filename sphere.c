/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:49 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 12:06:55 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

int get_color_sphere(t_win *win, t_vec3 inter, t_sphere *sphere, t_vec3 ray)
{
    t_getcolor c;

    c.light = win->ambient_light;
    c.normal = vec3_sub(inter, sphere->center);
    vec3_normalize(&(c.normal));
    c.brilliance = 0;
    c.i = 0;
    while (c.i < win->nb_lights)
    {
        c.light_dir = vec3_sub(win->lights[c.i], inter);
        vec3_normalize(&(c.light_dir));
        c.reflect_dir = vec3_sub(inter, vec3_add(c.normal, vec3_add(c.normal, vec3_add(inter, c.light_dir))));
        vec3_normalize(&(c.reflect_dir));
        if (shadowtrace(win, c.i, inter) > 0)
        {
            c.magnitude = sqrt(vec3_magnitude(c.light_dir));
            if (vec3_dot_prod(ray, c.reflect_dir) > 0.995 && vec3_dot_prod(ray, c.reflect_dir) > c.brilliance)
                c.brilliance = vec3_dot_prod(ray, c.reflect_dir);
            c.light = c.light + ((1 - c.light) * vec3_dot_prod(c.normal, c.light_dir) / c.magnitude);
        }
        c.i++;
    }
    return (calculate_light(sphere->color, c.light, c.brilliance));
}

float dist_sphere(t_vec3 pos, t_vec3 dir, t_sphere *sphere)
{
    float t[6];

    t[2] = (dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z);
    t[3] = 2 * (dir.x * (pos.x - sphere->center.x) + dir.y * (pos.y - sphere->center.y) + dir.z * (pos.z - sphere->center.z));
    t[4] = ((pos.x - sphere->center.x) * (pos.x - sphere->center.x)
            + (pos.y - sphere->center.y) * (pos.y - sphere->center.y)
            + (pos.z - sphere->center.z) * (pos.z - sphere->center.z)) - (sphere->r * sphere->r);
    t[5] = (t[3] * t[3]) - (4 * t[2] * t[4]);
    if (t[5] < 0)
        return(-1.0);
    t[0] = (-t[3] + sqrt(t[5])) / (2 * t[2]);
    t[1] = (-t[3] - sqrt(t[5])) / (2 * t[2]);
    if (t[0] > 0 && t[1] > 0)
    {
        if (t[0] > t[1])
            return (t[1]);
    }
    return (t[0]);
}

int    new_sphere(t_sphere **sphere)
{
    t_sphere *new;

    if (!(new = (t_sphere*)malloc(sizeof(t_sphere))))
        return (2);
    new->type = 1;
    new->center.x = 0;
    new->center.y = 0;
    new->center.z = 0;
    new->dir.x = 0;
    new->dir.y = 0;
    new->dir.z = 1;
    new->r = 1;
    *sphere = new;
    return(0);
}
