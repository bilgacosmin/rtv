/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:15:45 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/16 13:26:03 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	object_translate_up(t_win *win)
{
	if (((t_sphere*)(win->objects[win->selected_object]))->type == 1)
		((t_sphere*)(win->objects[win->selected_object]))->center.y += 1;
	if (((t_plane*)(win->objects[win->selected_object]))->type == 2)
		((t_plane*)(win->objects[win->selected_object]))->point.y += 1;
	if (((t_cone*)(win->objects[win->selected_object]))->type == 3)
		((t_cone*)(win->objects[win->selected_object]))->point.y += 1;
	if (((t_cylinder*)(win->objects[win->selected_object]))->type == 4)
		((t_cylinder*)(win->objects[win->selected_object]))->point.y += 1;
	return (0);
}

int	object_translate_down(t_win *win)
{
	if (((t_sphere*)(win->objects[win->selected_object]))->type == 1)
		((t_sphere*)(win->objects[win->selected_object]))->center.y -= 1;
	if (((t_plane*)(win->objects[win->selected_object]))->type == 2)
		((t_plane*)(win->objects[win->selected_object]))->point.y -= 1;
	if (((t_cone*)(win->objects[win->selected_object]))->type == 3)
		((t_cone*)(win->objects[win->selected_object]))->point.y -= 1;
	if (((t_cylinder*)(win->objects[win->selected_object]))->type == 4)
		((t_cylinder*)(win->objects[win->selected_object]))->point.y -= 1;
	return (0);
}

int	object_translate_left(t_win *win)
{
	if (((t_sphere*)(win->objects[win->selected_object]))->type == 1)
		((t_sphere*)(win->objects[win->selected_object]))->center.x -= 1;
	if (((t_plane*)(win->objects[win->selected_object]))->type == 2)
		((t_plane*)(win->objects[win->selected_object]))->point.x -= 1;
	if (((t_cone*)(win->objects[win->selected_object]))->type == 3)
		((t_cone*)(win->objects[win->selected_object]))->point.x -= 1;
	if (((t_cylinder*)(win->objects[win->selected_object]))->type == 4)
		((t_cylinder*)(win->objects[win->selected_object]))->point.x -= 1;
	return (0);
}

int	object_translate_right(t_win *win)
{
	if (((t_sphere*)(win->objects[win->selected_object]))->type == 1)
		((t_sphere*)(win->objects[win->selected_object]))->center.x += 1;
	if (((t_plane*)(win->objects[win->selected_object]))->type == 2)
		((t_plane*)(win->objects[win->selected_object]))->point.x += 1;
	if (((t_cone*)(win->objects[win->selected_object]))->type == 3)
		((t_cone*)(win->objects[win->selected_object]))->point.x += 1;
	if (((t_cylinder*)(win->objects[win->selected_object]))->type == 4)
		((t_cylinder*)(win->objects[win->selected_object]))->point.x += 1;
	return (0);
}
