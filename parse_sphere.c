/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:28 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 11:17:20 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static int parse_center(t_win *win, int fd, char *line)
{
    char **curr;

    if (get_next_line(fd, &line) > 0)
    {
        curr = ft_strsplit(line, ' ');
        if (curr[0])
            ((t_sphere*)(win->objects[win->nb_obj - 1]))->center.x = ft_atof(curr[0]);
        else
            return (1);
        if (curr[1])
            ((t_sphere*)(win->objects[win->nb_obj - 1]))->center.y = ft_atof(curr[1]);
        else
            return (1);
        if (curr[2])
            ((t_sphere*)(win->objects[win->nb_obj - 1]))->center.z = ft_atof(curr[2]);
        else
            return (1);
        free_split(&curr);
    }
    else
        return (1);
    free(line);
    return (0);
}

static int parse_direction(t_win *win, int fd, char *line)
{
    char **curr;

    if (get_next_line(fd, &line) > 0)
    {
        curr = ft_strsplit(line, ' ');
        if (curr[0])
            ((t_sphere*)(win->objects[win->nb_obj - 1]))->dir.x = ft_atof(curr[0]);
        else
            return (1);
        if (curr[1])
            ((t_sphere*)(win->objects[win->nb_obj - 1]))->dir.y = ft_atof(curr[1]);
        else
            return (1);
        if (curr[2])
            ((t_sphere*)(win->objects[win->nb_obj - 1]))->dir.z = ft_atof(curr[2]);
        else
            return (1);
        vec3_normalize(&(((t_sphere*)(win->objects[win->nb_obj - 1]))->dir));
        free_split(&curr);
    }
    else
        return (1);
    free(line);
    return (0);
}

static int parse_color(t_win *win, int fd, char *line)
{
char **curr;
unsigned int color;

color = 255;
if (get_next_line(fd, &line) > 0)
{
    curr = ft_strsplit(line, ' ');
    if (curr[0] && curr[1] && curr[2])
    {
        color = (ft_atoi(curr[0]) << 24) + (ft_atoi(curr[1]) << 16);
        color = color + (ft_atoi(curr[2]) << 8);
        ((t_sphere*)(win->objects[win->nb_obj - 1]))->color = color;
    }
    else
        return (1);
    free(curr);
}
else
    return (1);
free(line);
return (0);
}

static int parse_radius(t_win *win, int fd, char *line)
{
    if (get_next_line(fd, &line) > 0)
        ((t_sphere*)(win->objects[win->nb_obj - 1]))->r = ft_atof(line);
    else
        return (1);
    free(line);
    return (0);
}

int parse_sphere(t_win *win, int fd, char *line)
{
    if (!(win->objects[win->nb_obj] = (t_sphere*)malloc(sizeof(t_sphere))))
        return (1);
    ((t_sphere*)(win->objects[win->nb_obj]))->type = 1;
    win->nb_obj = win->nb_obj + 1;
    if (parse_center(win, fd, line) || parse_direction(win, fd, line)
        || parse_color(win, fd, line) || parse_radius(win, fd, line))
        return (1);
    return (0);
}
