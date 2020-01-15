/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:52:19 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 14:51:37 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void		calculate_view_point_start(t_vec3 *viewplanepoint, t_win *win)
{
	t_vec3 tmp;

	*viewplanepoint = vec3_mult(win->camera.forward, VPLANE_DISTANCE);
	tmp = vec3_mult(win->camera.up, VPLANE_HEIGHT / 2.0);
	*viewplanepoint = vec3_add(*viewplanepoint, tmp);
	tmp = vec3_mult(win->camera.right, VPLANE_WIDTH / 2.0);
	*viewplanepoint = vec3_sub(*viewplanepoint, tmp);
	*viewplanepoint = vec3_add(win->camera.position, *viewplanepoint);
}

t_vec3		calculate_view_point(t_vec3 *viewplanepointstart,
	t_win *win, int x, int y)
{
	float	x_ident;
	float	y_ident;
	t_vec3	viewplanepoint;
	t_vec3	tmp;

	x_ident = (VPLANE_WIDTH / (float)SCREEN_X) * x;
	y_ident = (VPLANE_HEIGHT / (float)SCREEN_Y) * y;
	tmp = vec3_mult(win->camera.right, x_ident);
	viewplanepoint = vec3_add(*viewplanepointstart, tmp);
	tmp = vec3_mult(win->camera.up, y_ident);
	viewplanepoint = vec3_sub(viewplanepoint, tmp);
	return (viewplanepoint);
}

static void	render_routine(t_win *win)
{
	SDL_UpdateTexture(win->texture, NULL, (void*)(win->pixels), SCREEN_X * 4);
	SDL_RenderCopy(win->renderer, win->texture, NULL, NULL);
	SDL_RenderPresent(win->renderer);
}

int			draw(t_win *win)
{
	int		x;
	int		y;
	t_vec3	viewplanepointstart;
	t_vec3	viewplanepoint;

	calculate_camera(win);
	calculate_view_point_start(&viewplanepointstart, win);
	y = 0;
	while (y < SCREEN_Y)
	{
		x = 0;
		while (x < SCREEN_X)
		{
			viewplanepoint =
				calculate_view_point(&viewplanepointstart, win, x, y);
			viewplanepoint = vec3_sub(viewplanepoint, win->camera.position);
			vec3_normalize(&viewplanepoint);
			win->color = raytrace(win, win->camera.position, viewplanepoint);
			win->pixels[y * SCREEN_X + x] = win->color;
			x++;
		}
		y++;
	}
	render_routine(win);
	return (0);
}
