/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:39 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 11:39:42 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

int get_color_plane (t_win *win, t_vec3 inter, t_plane *plane, t_vec3 ray)
{
    t_vec3 normal;
    t_vec3 light_dir;
    t_vec3 reflect_dir;
    float light;
    int i;
    float magnitude;
    float brilliance;

    (void)ray; //todetee
    light = win->ambient_light;
    normal = plane->normal;
    vec3_normalize(&normal);
    i = 0;
    brilliance = 0;
    while (i < win->nb_lights)
    {
        light_dir = vec3_sub(win->lights[i], inter);
        vec3_normalize(&light_dir);
        reflect_dir = vec3_sub(inter, vec3_add(normal, vec3_add(normal, vec3_add(inter, light_dir))));
        vec3_normalize(&reflect_dir);
        if (shadowtrace(win, i, inter) > 0)
        {
            magnitude = sqrt(vec3_magnitude(light_dir));
            vec3_normalize(&light_dir);
            if (vec3_dot_prod(normal, light_dir) < 0)
                normal = vec3_mult(normal, -1);
            light = light + ((1 - light) * vec3_dot_prod(normal, light_dir) / magnitude);
        }
        i++;
    }
    return (calculate_light(plane->color, light, brilliance));
}

float dist_plane(t_vec3 pos, t_vec3 dir, t_plane *plane)
{
    float t;
    t_vec3 tmp;

    tmp = vec3_sub(plane->point, pos);
    t = vec3_dot_prod(tmp, plane->normal);
    t = t / vec3_dot_prod(dir, plane->normal);
    return (t);
}

int    new_plane(t_plane **plane)
{
    t_plane *new;

    if (!(new = (t_plane*)malloc(sizeof(t_plane))))
        return (2);
    new->type = 2;
    new->point.x = 0;
    new->point.y = 0;
    new->point.z = 120;
    new->normal.x = 0;
    new->normal.y = 0;
    new->normal.z = 1;
    new->color = 0x00F0FFFF;
    *plane = new;
    return(0);
}
