/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:08 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/16 15:32:06 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static int	parse_point(t_win *win, int fd, char *line)
{
	char **curr;

	if (get_next_line(fd, &line) > 0)
	{
		curr = ft_strsplit(line, ' ');
		if (curr[0] && curr[1] && curr[2])
		{
			((t_cylinder*)(win->objects[win->nb_obj - 1]))->point.x =
				ft_atof(curr[0]);
			((t_cylinder*)(win->objects[win->nb_obj - 1]))->point.y =
				ft_atof(curr[1]);
			((t_cylinder*)(win->objects[win->nb_obj - 1]))->point.z =
				ft_atof(curr[2]);
		}
		else
			return (1);
		free_split(&curr);
	}
	else
		return (1);
	free(line);
	return (0);
}

static int	parse_axis(t_win *win, int fd, char *line)
{
	char **curr;

	if (get_next_line(fd, &line) > 0)
	{
		curr = ft_strsplit(line, ' ');
		if (curr[0] && curr[1] && curr[2])
		{
			((t_cylinder*)(win->objects[win->nb_obj - 1]))->axis.x =
				ft_atof(curr[0]);
			((t_cylinder*)(win->objects[win->nb_obj - 1]))->axis.y =
				ft_atof(curr[1]);
			((t_cylinder*)(win->objects[win->nb_obj - 1]))->axis.z =
				ft_atof(curr[2]);
		}
		else
			return (1);
		vec3_normalize(&(((t_cylinder*)(win->objects[win->nb_obj - 1]))->axis));
		free_split(&curr);
	}
	else
		return (1);
	free(line);
	return (0);
}

static int	parse_color(t_win *win, int fd, char *line)
{
	char			**curr;
	unsigned int	color;

	color = 255;
	if (get_next_line(fd, &line) > 0)
	{
		curr = ft_strsplit(line, ' ');
		if (curr[0] && curr[1] && curr[2])
		{
			color = (ft_atoi(curr[0]) << 24) + (ft_atoi(curr[1]) << 16);
			color = color + (ft_atoi(curr[2]) << 8);
			((t_cylinder*)(win->objects[win->nb_obj - 1]))->color = color;
		}
		else
			return (1);
		free_split(&curr);
	}
	else
		return (1);
	free(line);
	return (0);
}

static int	parse_radius(t_win *win, int fd, char *line)
{
	if (get_next_line(fd, &line) > 0)
		((t_cylinder*)(win->objects[win->nb_obj - 1]))->r = ft_atof(line);
	else
		return (1);
	free(line);
	return (0);
}

int			parse_cylinder(t_win *win, int fd, char *line)
{
	if (!(win->objects[win->nb_obj] = (t_cylinder*)malloc(sizeof(t_cylinder))))
		return (1);
	((t_cylinder*)(win->objects[win->nb_obj]))->type = 4;
	win->nb_obj = win->nb_obj + 1;
	if (parse_point(win, fd, line) || parse_axis(win, fd, line)
		|| parse_color(win, fd, line) || parse_radius(win, fd, line))
		return (1);
	return (0);
}
