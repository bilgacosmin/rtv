/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:15:50 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/16 13:33:28 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static int	parse_position(t_win *win, int fd, char *line)
{
	char **curr;

	if (get_next_line(fd, &line) > 0)
	{
		curr = ft_strsplit(line, ' ');
		if (curr[0])
			win->camera.position.x = ft_atof(curr[0]);
		else
			return (1);
		if (curr[1])
			win->camera.position.y = ft_atof(curr[1]);
		else
			return (1);
		if (curr[2])
			win->camera.position.z = ft_atof(curr[2]);
		else
			return (1);
		free_split(&curr);
	}
	else
		return (1);
	free(line);
	return (0);
}

static int	parse_direction(t_win *win, int fd, char *line)
{
	char **curr;

	if (get_next_line(fd, &line) > 0)
	{
		curr = ft_strsplit(line, ' ');
		if (curr[0])
			win->camera.forward.x = ft_atof(curr[0]);
		else
			return (1);
		if (curr[1])
			win->camera.forward.y = ft_atof(curr[1]);
		else
			return (1);
		if (curr[2])
			win->camera.forward.z = ft_atof(curr[2]);
		else
			return (1);
		vec3_normalize(&(win->camera.forward));
		free_split(&curr);
	}
	else
		return (1);
	free(line);
	return (0);
}

static int	parse_ambient(t_win *win, int fd, char *line)
{
	if (get_next_line(fd, &line) > 0)
		win->ambient_light = ft_atof(line);
	else
		return (1);
	free(line);
	if (win->ambient_light > 1 || win->ambient_light < 0)
		win->ambient_light = 0.1;
	return (0);
}

int			parse_camera(t_win *win, int fd, char *line)
{
	if (parse_position(win, fd, line) || parse_direction(win, fd, line)
		|| parse_ambient(win, fd, line))
		return (2);
	return (0);
}
