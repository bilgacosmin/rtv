/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:35 by cbilga            #+#    #+#             */
/*   Updated: 2020/02/04 10:47:48 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static int	parse_object(t_win *win, int fd, char *line)
{
	if (ft_strcmp("sphere", line) == 0)
		return (parse_sphere(win, fd, line));
	if (ft_strcmp("cone", line) == 0)
		return (parse_cone(win, fd, line));
	if (ft_strcmp("plane", line) == 0)
		return (parse_plane(win, fd, line));
	if (ft_strcmp("cylinder", line) == 0)
		return (parse_cylinder(win, fd, line));
	if (ft_strcmp("camera", line) == 0)
		return (parse_camera(win, fd, line));
	if (ft_strcmp("light", line) == 0)
		return (parse_light(win, fd, line));
	return (1);
}

static int	parse_while(t_win *win, int fd)
{
	int		parse;
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if ((parse = parse_object(win, fd, line)) == 1)
		{
			free(win->objects[win->nb_obj - 1]);
			win->nb_obj = win->nb_obj - 1;
			free(line);
			return (1);
		}
		else if (parse == 2)
		{
			win->nb_lights = win->nb_lights - 1;
			free(line);
			return (2);
		}
		free(line);
	}
	return (0);
}

int			parse(t_win *win, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_handling(win);
	win->nb_obj = 0;
	if (!(win->objects = (void**)malloc(sizeof(void*) * 100)))
		error_handling(win);
	return (parse_while(win, fd));
}
