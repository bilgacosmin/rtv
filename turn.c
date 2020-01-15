/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <cbilga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:16:54 by cbilga            #+#    #+#             */
/*   Updated: 2020/01/15 11:43:34 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

int turn(t_win *win)
{
    int quit;

    quit = 0;
    key_pressed(win);
    while (quit == 0)
    {
        while (SDL_PollEvent(&(win->event)))
        {
            if (win->event.type == SDL_KEYDOWN)
                quit = key_pressed(win);
        }
    }
    return (0);
}
