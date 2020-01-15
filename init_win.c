/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:52:34 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 09:47:17 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"
int init_camera(t_camera *camera)
{
    t_vec3 tmp;

    tmp.x = 0;
    tmp.y = 1;
    tmp.z = 0;
    camera->position.x = 0;
    camera->position.y = 0;
    camera->position.z = 0;
    camera->forward.x = 0;
    camera->forward.y = 0;
    camera->forward.z = 1;
    vec3_normalize(&(camera->forward));
    camera->right = vec3_cross_prod(camera->forward, tmp);
    vec3_normalize(&(camera->right));
    camera->up = vec3_cross_prod(camera->forward, camera->right);
    vec3_normalize(&(camera->up));
    return (0);
}

int parse_objects_empty(t_win *win)
{
    win->nb_obj = 5;
    win->objects = (void**)malloc(sizeof(void*) * win->nb_obj);
    new_cylinder((t_cylinder **)(&(win->objects[0])));
    new_sphere((t_sphere **)(&(win->objects[1])));
    ((t_sphere*)(win->objects[1]))->center.x = 0;
    ((t_sphere*)(win->objects[1]))->center.y = -3;
    ((t_sphere*)(win->objects[1]))->center.z = 20;
    ((t_sphere*)(win->objects[1]))->r = 1;
    ((t_sphere*)(win->objects[1]))->color = 0x0000FFFF;
    new_plane((t_plane**)(&(win->objects[2])));
    new_plane((t_plane**)(&(win->objects[3])));
    ((t_plane*)(win->objects[3]))->color = 0xBF00FFFF;
    ((t_plane*)(win->objects[3]))->normal.z = 0;
    ((t_plane*)(win->objects[3]))->normal.y = 1;
    ((t_plane*)(win->objects[3]))->point.y = -8;
    new_cone((t_cone **)(&(win->objects[4])));
    win->nb_lights = 2;
    win->lights = (t_vec3*)malloc(sizeof(t_vec3) * win->nb_lights);
    win->lights[0].x = -10;
    win->lights[0].y = 0;
    win->lights[0].z = 8;
    win->lights[1].x = 0;
    win->lights[1].y = -3;
    win->lights[1].z = 0;
    return(0);
}

int init_win(t_win *win)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return (2);
    win->window = SDL_CreateWindow("RTV1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, SDL_WINDOW_SHOWN);
    win->renderer = SDL_CreateRenderer(win->window, -1, 0);
    win->texture = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_X, SCREEN_Y);
    init_camera(&(win->camera));
    win->max_depth = 1;
    win->depth = 0;
    win->ambient_light = 0.3;
    win->nb_obj = 0;
    win->selected_object = 0;
    return(0);
}
