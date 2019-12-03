#include "includes/rtv1.h"

t_vec3  get_cylinder_normal(t_cylinder *cylinder, t_vec3 point)
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

int get_color_cylinder (t_win *win, t_vec3 inter, t_cylinder *cylinder, t_vec3 ray)
{
    t_vec3 normal;
    t_vec3 light_dir;
    t_vec3 reflect_dir;
    float light;
    int i;
    float magnitude;
    float brilliance;

    light = win->ambient_light;
    normal = get_cylinder_normal(cylinder, inter);
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
            if (vec3_dot_prod(ray, reflect_dir) > 0.995 && vec3_dot_prod(ray, reflect_dir) > brilliance)
                brilliance = vec3_dot_prod(ray, reflect_dir);
            light = light + ((1 - light) * vec3_dot_prod(normal, light_dir) / magnitude);
        }
        i++;
    }
    return (calculate_light(cylinder->color, light, brilliance));
}

float dist_cylinder(t_vec3 pos, t_vec3 dir, t_cylinder *cylinder)
{
    float t[6]; //t1 t2 a b c det
    t_vec3 c_pos;
    t_vec3 tmp;

    c_pos = vec3_cross_prod(cylinder->axis, dir);
    tmp = vec3_cross_prod(cylinder->axis, vec3_sub(pos, cylinder->point));
    t[2] = vec3_dot_prod(c_pos, c_pos);
    t[3] = vec3_dot_prod(c_pos, vec3_cross_prod(cylinder->axis, vec3_sub(pos, cylinder->point))) * 2;
    t[4] = vec3_dot_prod(tmp, tmp) - (cylinder->r * cylinder->r);
    t[5] = (t[3] * t[3]) - (4 * t[2] * t[4]);
    if (t[5] < 0 || t[2] == 0)
        return(-1.0);
    t[0] = (-t[3] + sqrt(t[5])) / (2 * t[2]);
    t[1] = (-t[3] - sqrt(t[5])) / (2 * t[2]);
    if (t[0] > 0 && t[1] > 0)
    {
        if (t[0] > t[1])
            return (t[1]);
    }
    return (-1);
}

int    new_cylinder(t_cylinder **cylinder)
{
    t_cylinder *new;

    if (!(new = (t_cylinder*)malloc(sizeof(t_cylinder))))
        return (2);
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
    return(0);
}