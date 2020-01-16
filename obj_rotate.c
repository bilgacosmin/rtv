/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:15:40 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/16 15:42:30 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	object_rotate_x(t_win *win)
{
	if (((t_sphere*)(win->objects[win->selected_object]))->type == 1)
		return (0);
	if (((t_plane*)(win->objects[win->selected_object]))->type == 2)
		((t_plane*)(win->objects[win->selected_object]))->normal =
			vec3_rotation_x(((t_plane*)
			(win->objects[win->selected_object]))->normal, M_PI / 8);
	if (((t_cone*)(win->objects[win->selected_object]))->type == 3)
		((t_cone*)(win->objects[win->selected_object]))->axis =
			vec3_rotation_x(((t_cone*)
			(win->objects[win->selected_object]))->axis, M_PI / 8);
	if (((t_cylinder*)(win->objects[win->selected_object]))->type == 4)
		((t_cylinder*)(win->objects[win->selected_object]))->axis =
			vec3_rotation_x(((t_cylinder*)
			(win->objects[win->selected_object]))->axis, M_PI / 8);
	return (0);
}

int	object_rotate_y(t_win *win)
{
	if (((t_sphere*)(win->objects[win->selected_object]))->type == 1)
		return (0);
	if (((t_plane*)(win->objects[win->selected_object]))->type == 2)
		((t_plane*)(win->objects[win->selected_object]))->normal =
			vec3_rotation_y(((t_plane*)
				(win->objects[win->selected_object]))->normal, M_PI / 8);
	if (((t_cone*)(win->objects[win->selected_object]))->type == 3)
		((t_cone*)(win->objects[win->selected_object]))->axis =
			vec3_rotation_y(((t_cone*)
				(win->objects[win->selected_object]))->axis, M_PI / 8);
	if (((t_cylinder*)(win->objects[win->selected_object]))->type == 4)
		((t_cylinder*)(win->objects[win->selected_object]))->axis =
			vec3_rotation_y(((t_cylinder*)
				(win->objects[win->selected_object]))->axis, M_PI / 8);
	return (0);
}

int	object_rotate_z(t_win *win)
{
	if (((t_sphere*)(win->objects[win->selected_object]))->type == 1)
		return (0);
	if (((t_plane*)(win->objects[win->selected_object]))->type == 2)
		((t_plane*)(win->objects[win->selected_object]))->normal =
			vec3_rotation_z(((t_plane*)
				(win->objects[win->selected_object]))->normal, M_PI / 8);
	if (((t_cone*)(win->objects[win->selected_object]))->type == 3)
		((t_cone*)(win->objects[win->selected_object]))->axis =
			vec3_rotation_z(((t_cone*)
				(win->objects[win->selected_object]))->axis, M_PI / 8);
	if (((t_cylinder*)(win->objects[win->selected_object]))->type == 4)
		((t_cylinder*)(win->objects[win->selected_object]))->axis =
			vec3_rotation_z(((t_cylinder*)
				(win->objects[win->selected_object]))->axis, M_PI / 8);
	return (0);
}
