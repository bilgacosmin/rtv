#include "includes/rtv1.h"

int free_window(t_win *win)
{
    SDL_DestroyRenderer(win->renderer);
    SDL_DestroyWindow(win->window);
    return (0);
}                                            