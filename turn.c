#include "includes/rtv1.h"

int turn(t_win *win)
{
    int quit;

    quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&(win->event)))
        {
            if (win->event.type == SDL_KEYDOWN)
            {
                quit = key_pressed(win);
            }
            //SDL_RenderPresent(win->renderer);
        }
    }
    return (0);
}