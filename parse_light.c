/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:20 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 11:14:44 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static int parse_pos(t_win *win, int fd, char *line)
{
    char **curr;

    if (get_next_line(fd, &line) > 0)
    {
        curr = ft_strsplit(line, ' ');
        if (curr[0])
            win->lights[win->nb_lights - 1].x = ft_atof(curr[0]);
        else
            return (1);
        if (curr[1])
            win->lights[win->nb_lights - 1].y = ft_atof(curr[1]);
        else
            return (1);
        if (curr[2])
            win->lights[win->nb_lights - 1].z = ft_atof(curr[2]);
        else
            return (1);
        free_split(&curr);
    }
    else
        return (1);
    free(line);
    return (0);
}

int parse_light(t_win *win, int fd, char *line)
{
    int i;
    t_vec3 *tmp;

    i = 0;
    win->nb_lights = win->nb_lights + 1;
    if (win->lights == NULL)
    {
        if (!(win->lights = (t_vec3*)malloc(sizeof(t_vec3))))
            return (1);
    }
    else
    {
        if (!(tmp = (t_vec3*)malloc(sizeof(t_vec3) * win->nb_lights)))
            return (1);
        while(i < win->nb_lights - 1)
        {
            tmp[i] = win->lights[i];
            i++;
        }
        free(win->lights);
        win->lights = tmp;
    }
    if (parse_pos(win, fd, line))
        return (2);
    return (0);
}
