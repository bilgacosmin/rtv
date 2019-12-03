#include "includes/rtv1.h"

t_vec3  get_cone_normal(t_cone *cone, t_vec3 point) //TO TEST
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

int get_color_cone (t_win *win, t_vec3 inter, t_cone *cone, t_vec3 ray)
{
    t_vec3 normal;
    t_vec3 light_dir;
    t_vec3 reflect_dir;
    float light;
    int i;
    float magnitude;
    float brilliance;

    light = win->ambient_light;
    normal = get_cone_normal(cone, inter);
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
            if (vec3_dot_prod(normal, light_dir) < 0)
                normal = vec3_mult(normal, -1);
            if (vec3_dot_prod(ray, reflect_dir) > 0.995 && vec3_dot_prod(ray, reflect_dir) > brilliance)
                brilliance = vec3_dot_prod(ray, reflect_dir);
            light = light + ((1 - light) * vec3_dot_prod(normal, light_dir) / magnitude);
        }
        i++;
    }
    return (calculate_light(cone->color, light, brilliance));
}

float dist_cone(t_vec3 pos, t_vec3 dir, t_cone *cone)
{
    float t[7]; //t1 t2 a b c det
    t_vec3 c_pos;

    //vec3_print("cone point", cone->point);
    //vec3_print("cone axis", cone->axis);
    //printf("angle %f\n", cone->angle);
    t[6] = cos(cone->angle) * cos(cone->angle);
    //printf("cos 2 theta %f\n", t[6]);
    c_pos = vec3_sub(cone->point, pos);
    //vec3_print("dir ", dir);
    //vec3_print("c_pos", c_pos);
    t[2] = vec3_dot_prod(dir, cone->axis);
    t[2] = (t[2] * t[2]) -  t[6];
    //printf("a %f \n", t[2]);
    //c_pos = vec3_sub(cone->point, pos);
    t[3] = 2 * ((vec3_dot_prod(dir, cone->axis) * vec3_dot_prod(c_pos, cone->axis)) - (vec3_dot_prod(dir, c_pos) * t[6]));
    //printf("b %f \n", t[3]);
    t[4] = vec3_dot_prod(c_pos, cone->axis);
    t[4] = (t[4] * t[4]) - (vec3_dot_prod(c_pos, vec3_mult(c_pos, t[6])));
    //printf("c %f \n", t[4]); 
    t[5] = (t[3] * t[3]) - (4 * t[2] * t[4]);
    //printf("delta %f \n", t[5]);
    //sleep(100);
    if (t[5] < 0 || t[2] == 0)
        return(-1.0);
    t[0] = (-t[3] + sqrt(t[5])) / (2 * t[2]);
    t[1] = (-t[3] - sqrt(t[5])) / (2 * t[2]);
    //printf("Cone distances %f %f \n", t[0], t[1]);
    t[0] = -t[0]; // ??
    t[1] = -t[1]; // why negative ?? 
    if (t[0] > 0 && t[1] > 0)
    {
        if (t[0] > t[1])
            return (t[1]);
    }
    return (-1);
}

int    new_cone(t_cone **cone)
{
    t_cone *new;

    if (!(new = (t_cone*)malloc(sizeof(t_cone))))
        return (2);
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
    return(0);
}