#include "includes/rtv1.h"

void calculate_view_point_start(t_vec3 *viewPlanePoint, t_win *win)
{
    t_vec3 tmp;

    *viewPlanePoint = vec3_mult(win->camera.forward, VPLANE_DISTANCE);
    tmp = vec3_mult(win->camera.up, VPLANE_HEIGHT / 2.0);
    *viewPlanePoint = vec3_add(*viewPlanePoint, tmp);
    tmp = vec3_mult(win->camera.right, VPLANE_WIDTH / 2.0);
    *viewPlanePoint = vec3_sub(*viewPlanePoint, tmp);
    *viewPlanePoint = vec3_add(win->camera.position, *viewPlanePoint);
}

t_vec3 calculate_view_point(t_vec3 *viewPlanePointStart, t_win *win,int x, int y)
{
    float x_ident;
    float y_ident;
    t_vec3 viewPlanePoint;
    t_vec3 tmp;

    x_ident = (VPLANE_WIDTH / (float)SCREEN_X) * x;
    y_ident = (VPLANE_HEIGHT / (float)SCREEN_Y) * y;

    tmp = vec3_mult(win->camera.right, x_ident);
    viewPlanePoint = vec3_add(*viewPlanePointStart, tmp);
    tmp = vec3_mult(win->camera.up, y_ident);
    viewPlanePoint = vec3_sub(viewPlanePoint, tmp);
    return (viewPlanePoint);
}

int draw(t_win *win)
{
    int x;
    int y;
    t_vec3 viewPlanePointStart;
    t_vec3 viewPlanePoint;

    SDL_RenderClear(win->renderer);
    calculate_camera(win);
    calculate_view_point_start(&viewPlanePointStart, win);
    y = 0;
    while (y < SCREEN_Y)
    {
        x = 0;
        while (x < SCREEN_X)
        {
            viewPlanePoint = calculate_view_point(&viewPlanePointStart, win, x, y);
            viewPlanePoint = vec3_sub(viewPlanePoint, win->camera.position);
            vec3_normalize(&viewPlanePoint);
            win->color = raytrace(win, win->camera.position, viewPlanePoint);
            win->pixels[y * SCREEN_X + x] = win->color;
            x++;
        }
        y++;
    }
    SDL_UpdateTexture(win->texture, NULL, (void*)(win->pixels), SCREEN_X * 4);
    SDL_RenderCopy(win->renderer, win->texture, NULL, NULL);
    SDL_RenderPresent(win->renderer);
    return (0);
}