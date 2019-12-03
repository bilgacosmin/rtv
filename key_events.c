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

int key_pressed(t_win *win)
{
    printf("Pressed key: %d\n", win->event.key.keysym.scancode);
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
    draw(win);
    return (0);
}