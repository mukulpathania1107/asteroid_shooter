#ifndef FILE_BGSPACE_SEEN
#define FILE_BGSPACE_SEEN 1

#include <allegro5/allegro5.h>
#include "asteroid.h"

#define STAR_COUNT SCREEN_WIDTH / 2

typedef struct{
     float x,y;
     float speed;
}STAR;

extern STAR stars[STAR_COUNT];

void init_star();
void star_update();
void star_create();



#define MAX_COMET_COUNT 10
extern ALLEGRO_BITMAP *PLANET, *COMET, *planet;

typedef struct{
    float x,y,scale,speed;
    bool gone;
}COMETS;

extern COMETS comets[MAX_COMET_COUNT];
extern int comet_count;


void init_planet();
void draw_planet();
void destroy_planet();
void update_comet();
static void create_comet(COMETS *comet);
static void draw_comet(COMETS *comet);
void draw_comets();
static void create_new_comet();
void trigger_comet();

#endif //bgspace.h
