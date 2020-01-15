#include "vector.h"
#include "../libraries/include/SDL2/SDL.h"
#include "libft.h"

#define SCREEN_X 800
#define SCREEN_Y 600
#define VPLANE_DISTANCE 1.0
#define VPLANE_WIDTH 0.35
#define VPLANE_HEIGHT 0.5


typedef struct  s_camera
{
    t_vec3 position;
    t_vec3 forward;
    t_vec3 right;
    t_vec3 up;
}               t_camera;

typedef struct s_win
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    SDL_Texture     *texture;
    t_camera        camera;
    void            **objects;
    int             nb_obj;
    int             selected_object;
    unsigned int    color;
    unsigned int    pixels[SCREEN_X * SCREEN_Y];
    t_vec3          *lights;
    int             nb_lights;
    int             max_depth;
    int             depth;
    float           ambient_light;
}               t_win;

typedef struct s_sphere
{
    int             type;   // 1 - sphere
    t_vec3          center;
    t_vec3          dir;
    float           r;
    unsigned int     color;
}               t_sphere;

typedef struct s_plane
{
    int type;       // 2 - plane
    t_vec3  point;
    t_vec3  normal;
    unsigned int    color;
}              t_plane;

typedef struct s_cone
{
    int type; // 3 - cone
    t_vec3  point;
    t_vec3  axis;
    float   angle;
    unsigned int color;
}               t_cone;

typedef struct s_cylinder
{
    int type; //4 - cylinder
    t_vec3  point;
    t_vec3  axis;
    float   r;
    unsigned int color;
}               t_cylinder;

typedef struct s_getcolor
{
    t_vec3 normal;
    t_vec3 light_dir;
    t_vec3 reflect_dir;
    float light;
    int i;
    float magnitude;
    float brilliance;
}               t_getcolor;

int             init_win(t_win *win);

int             turn(t_win *win);
int             key_pressed(t_win *win);
int             draw(t_win *win);
int             calculate_camera(t_win *win);
float           dist_sphere(t_vec3 pos, t_vec3 dir, t_sphere *sphere);
float           dist_plane(t_vec3 pos, t_vec3 dir, t_plane *plane);
float           dist_cone(t_vec3 pos, t_vec3 dir, t_cone *cone);
float           dist_cylinder(t_vec3 pos, t_vec3 dir, t_cylinder *cylinder);
int             new_sphere(t_sphere **sphere);
int             new_plane(t_plane **plane);
int             new_cone(t_cone **cone);
int             new_cylinder(t_cylinder **cylinder);
int             raytrace(t_win *win,t_vec3 pos, t_vec3 ray);
unsigned int    calculate_light(unsigned int color, float light_intensity, float brilliance);
int             get_color_sphere(t_win *win, t_vec3 inter, t_sphere *sphere, t_vec3 ray);
int             get_color_plane(t_win *win, t_vec3 inter, t_plane *plane, t_vec3 ray);
int             get_color_cone(t_win *win, t_vec3 inter, t_cone *cone, t_vec3 ray);
int             get_color_cylinder (t_win *win, t_vec3 inter, t_cylinder *cylinder, t_vec3 ray);
int             shadowtrace(t_win* win, int light, t_vec3 inter);
float           to_radian(float angle);
int             parse_objects_empty(t_win *win);
int             parse(t_win *win, char* filename);
int             parse_sphere(t_win *win, int fd, char *line);
int             parse_plane(t_win *win, int fd, char *line);
int             parse_cylinder(t_win *win, int fd, char *line);
int             parse_cone(t_win *win, int fd, char *line);
int             parse_camera(t_win *win, int fd, char *line);
int             parse_light(t_win *win, int fd, char *line);
int             object_translate_up(t_win *win);
int             object_translate_down(t_win *win);
int             object_translate_left(t_win *win);
int             object_translate_right(t_win *win);
int             object_rotate_x(t_win *win);
int             object_rotate_y(t_win *win);
int             object_rotate_z(t_win *win);

int             free_window(t_win *win);
void			free_split(char ***split);
