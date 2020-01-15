/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:48:41 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 12:07:58 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

int	calculate_camera(t_win *win)
{
	t_camera	*camera;
	t_vec3		tmp;

	camera = &(win->camera);
	tmp.x = 0;
	tmp.y = 1;
	tmp.z = 0;
	camera->right = vec3_cross_prod(camera->forward, tmp);
	vec3_normalize(&(camera->right));
	camera->up = vec3_cross_prod(camera->forward, camera->right);
	vec3_normalize(&(camera->up));
	return (0);
}
