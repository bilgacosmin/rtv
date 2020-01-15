/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:52:44 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/13 16:52:46 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

static void rotate_left(t_win *win)
{
    t_vec3 new;

    new = vec3_mult(win->camera.right, -1);
    new = vec3_add(win->camera.forward, new);
    new = vec3_add(win->camera.forward, new);
    vec3_normalize(&new);
    win->camera.forward = new;
}

static void rotate_right(t_win *win)
{
    t_vec3 new;

    new = win->camera.right;
    new = vec3_add(win->camera.forward, new);
    new = vec3_add(win->camera.forward, new);
    vec3_normalize(&new);
    win->camera.forward = new;
}

int key_object(t_win *win)
{
    if (win->selected_object < win->nb_obj && win->selected_object >= 0)
    {
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
        {
            if (win->selected_object + 1 < win->nb_obj)
                win->selected_object += 1;
        }
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
        {
            if (win->selected_object - 1 >= 0)
                win->selected_object -= 1;
        }
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_8)
            object_translate_up(win);
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_5)
            object_translate_down(win);
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_4)
            object_translate_left(win);
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_6)
            object_translate_right(win);
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_1)
            object_rotate_x(win);
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_2)
            object_rotate_y(win);
        if (win->event.key.keysym.scancode == SDL_SCANCODE_KP_3)
            object_rotate_z(win);
    }
    return (0);
}

int key_pressed(t_win *win)
{
    if (win->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        return(1);
    if (win->event.key.keysym.scancode == SDL_SCANCODE_W)
        win->camera.position.y += 1;
    if (win->event.key.keysym.scancode == SDL_SCANCODE_S)
        win->camera.position.y -= 1;
    if (win->event.key.keysym.scancode == SDL_SCANCODE_A)
        win->camera.position.x += 1;
    if (win->event.key.keysym.scancode == SDL_SCANCODE_D)
        win->camera.position.x -= 1;
    if (win->event.key.keysym.scancode == SDL_SCANCODE_E)
        win->camera.position.z += 1;
    if (win->event.key.keysym.scancode == SDL_SCANCODE_Q)
        win->camera.position.z -= 1;
    if (win->event.key.keysym.scancode == SDL_SCANCODE_Z)
        rotate_left(win);
    if (win->event.key.keysym.scancode == SDL_SCANCODE_X)
        rotate_right(win);
    key_object(win);
    draw(win);
    return (0);
}