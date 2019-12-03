#include "includes/rtv1.h"

int main(int argc, char *argv[])
{
    t_win win;

    init_win(&win);
    if (argc >= 2)
        parse(&win, argv[1]);
    else
        parse_objects_empty(&win);
    vec3_print("position", ((t_sphere*)win.objects[0])->center);
    printf("%d\n",win.nb_obj);
    turn(&win);
   /**
    surface = SDL_LoadBMP("texture.bmp");
    renderer = SDL_CreateRenderer(wn, -1, 0);
    SDL_RenderClear(renderer);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &hauteur, &largeur);
    dest.w = 100;
    dest.h = 50;
    dest.x = 0;
    dest.y = 0;
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_UpdateWindowSurface(wn);
    //SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    while (quit == 0)
    {
        while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    quit = 1;
                if (event.type == SDL_KEYDOWN)
                    quit = 1;
            }
    } **/
    free_window(&win);                                                                                                                                          
    return (0);
}