#include "includes/rtv1.h"

int get_color_sphere(t_win *win, t_vec3 inter, t_sphere *sphere, t_vec3 ray)
{
    t_vec3 normal;
    t_vec3 light_dir;
    t_vec3 reflect_dir;
    float light;
    int i;
    float magnitude;
    float brilliance;

    light = win->ambient_light;
    normal = vec3_sub(inter, sphere->center);
    vec3_normalize(&normal);
    brilliance = 0;
    i = 0;
    while (i < win->nb_lights)
    {
        light_dir = vec3_sub(win->lights[i], inter);
        vec3_normalize(&light_dir);
        reflect_dir = vec3_sub(inter, vec3_add(normal, vec3_add(normal, vec3_add(inter, light_dir))));
        vec3_normalize(&reflect_dir);
        if (shadowtrace(win, i, inter) > 0)
        {
            magnitude = sqrt(vec3_magnitude(light_dir));
            if (vec3_dot_prod(ray, reflect_dir) > 0.995 && vec3_dot_prod(ray, reflect_dir) > brilliance)
                brilliance = vec3_dot_prod(ray, reflect_dir);
            light = light + ((1 - light) * vec3_dot_prod(normal, light_dir) / magnitude);
        }
        i++;
    }
    return (calculate_light(sphere->color, light, brilliance));
}

float dist_sphere(t_vec3 pos, t_vec3 dir, t_sphere *sphere)
{
    float t[6]; //t1 t2 a b c det

    //printf("DIST SPHERE\n Camera pos %f %f %f\n",pos.x, pos.y, pos.z);
    //printf("Ray direction %f %f %f\n", dir.x, dir.y, dir.z);
    //printf("Sphere position %f %f %f\n", sphere->center.x, sphere->center.y, sphere->center.x);
    //sleep(100);
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