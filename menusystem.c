/*This file contains all the things that are required for drawing the
 *menu on the screen. */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "menusystem.h"
#include "bgspace.h"
#include "input.h"
#include "sounds.h"
#include "asteroid.h"
#include "main.h"

ALLEGRO_FONT *heading, *options, *highlighted_option, *medium_scale, *small_scale;
ALLEGRO_TRANSFORM menusystem_transform;
static void init_main_menu();
static void draw_menu();
static void draw_welcome();
static void draw_controls();
static void draw_credits();
int current_option = 0;
int draw_helper = 0;
bool done = false;//keep it here start_game_option_handler uses it.

void (*draw[3])();//array of function pointers used in the drawing of menu.


void init_menusystem(){
    must_init(al_init_font_addon(), "Font addon");
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_install_mouse(), "Mouse");

    heading = al_load_ttf_font("resources/SEASRN__.ttf", 72, 0);
    must_init(heading, "Heading Font");
    options = al_load_ttf_font("resources/SEASRN__.ttf", 32, 0);
    must_init(options, "Font for options");
    highlighted_option = al_load_ttf_font("resources/SEASRN__.ttf", 50, 0);
    must_init(highlighted_option, "Font for chosen option");
    medium_scale = al_load_ttf_font("resources/SEASRN__.ttf", 40, 0);
    must_init(medium_scale, "Medium sized font");
    small_scale = al_load_ttf_font("resources/SEASRN__.ttf", 25, 0);
    must_init(small_scale, "Small sized font");
    
    draw[0] = draw_welcome;
    draw[1] = draw_controls;
    draw[2] = draw_credits;

    init_main_menu();
}


static void start_game_option_handler(){
    done = true;
}
/*Couldn't think of a name.*/
static void controls_option_handler(){
    draw_helper = 1;
}
static void credits_option_handler(){
    draw_helper = 2;
}
static void exit_option_handler(){
    destroy_main();
    exit(0);
}
static void draw_credits(){
    al_build_transform(&menusystem_transform, 0, 0, 1, 1, 0);
    al_use_transform(&menusystem_transform);
    al_draw_filled_rectangle(390, 5, 700, 100, al_map_rgba(0, 128, 128, 0.2));
    
    al_draw_text(heading, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2, 0,
            ALLEGRO_ALIGN_CENTER, "CREDITS");
    
    al_draw_text(medium_scale, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 130,
            ALLEGRO_ALIGN_CENTER, "DEVELEOPED BY:");
    
    al_draw_text(small_scale, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 180,
            ALLEGRO_ALIGN_CENTER, "MUKUL PATHANIA");
    
    al_draw_text(medium_scale, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 250,
            ALLEGRO_ALIGN_CENTER, "CONTRIBUTORS:");
    
    al_draw_text(small_scale, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 300,
            ALLEGRO_ALIGN_CENTER, "SHUBHAM WAWALE AND ROHIT PATIL");
    
    al_draw_text(medium_scale, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 370,
            ALLEGRO_ALIGN_CENTER, "MUSIC TRACKS:");

    al_draw_text(small_scale, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 420,
            ALLEGRO_ALIGN_CENTER, "Nexus Save the Queen");

    al_draw_multiline_text(medium_scale, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, 500,
            SCREEN_WIDTH, 60, ALLEGRO_ALIGN_CENTER, "STAY AT HOME AND STAY SAFE DURING THESE"
            " TESTING TIMES OF CORONA.");
}
static void draw_controls(){
}


void destroy_menusystem(){
    al_destroy_font(heading);
    al_destroy_font(options);
    al_destroy_font(highlighted_option);
    al_destroy_font(medium_scale);
    al_destroy_font(small_scale);
}


MENU main_menu[5];
static void init_main_menu(){
    for(int i = 0, y = 250; i < 5; i++, y += 70){
        main_menu[i].x1 = 370;
        main_menu[i].x2 = 710;
        main_menu[i].y1 = y;
        main_menu[i].y2 = y + 70;
        main_menu[i].font = options;
    }
    main_menu[0].text = "START GAME";
    main_menu[0].handler = start_game_option_handler;
    main_menu[1].text = "CONTROLS";
    main_menu[1].handler = controls_option_handler;
    main_menu[2].text = "CREDITS";
    main_menu[2].handler = credits_option_handler;
    main_menu[3].text = "EXIT";
    main_menu[3].handler = exit_option_handler;
}




static void draw_menu(){
    for(int i = 0; i < 4; i++){
        if(i == current_option){
            al_draw_filled_rectangle(main_menu[i].x1, main_menu[i].y1, main_menu[i].x2, main_menu[i].y2, al_map_rgba(255, 255, 255, 0.2));
            al_draw_text(highlighted_option, al_map_rgb(0, 0, 0), SCREEN_WIDTH / 2,
                    main_menu[i].y1, ALLEGRO_ALIGN_CENTER, main_menu[i].text);
            continue;
        }
        al_draw_text(main_menu[i].font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                main_menu[i].y1, ALLEGRO_ALIGN_CENTER, main_menu[i].text);
    }
}

static void draw_welcome(){
    al_build_transform(&menusystem_transform, 0, 0, 1, 1, 0);
    al_use_transform(&menusystem_transform);
    al_draw_filled_rectangle(120, 5, 950, 180, al_map_rgba(0, 128, 128, 0.2));
    al_draw_multiline_text(heading, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
            0, SCREEN_WIDTH, 80, ALLEGRO_ALIGN_CENTER, "Welcome to Asteroid-Shooter");

    draw_menu();
}

static void handle_mouse_hover_and_click(ALLEGRO_EVENT *event){
    int x = 0, y = 0;
    bool clicked = false;
    switch(event->type){

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if(event->mouse.button & 1)
                clicked = true;
            //no break is added here to use fall through
        case ALLEGRO_EVENT_MOUSE_AXES:
            x = event->mouse.x;
            y = event->mouse.y;
            break;
    }

    if((x || y)  && draw_helper == 0)
        for(int i = 0 ; i < 4; i++)
            if(x > main_menu[i].x1 && x < main_menu[i].x2 && y > main_menu[i].y1 &&  y < main_menu[i].y2){
                current_option = i;
                if(clicked)
                    main_menu[current_option].handler();
            }

}


void welcome_screen(){
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer welcome screen");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue welcome screen");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool redraw = true;
    ALLEGRO_EVENT event;
    play_menu_music();

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                update_bgspace();
                trigger_bgspace();
                asteroid_trigger();
                update_asteroids();

                if(key[ALLEGRO_KEY_DOWN])
                    current_option++;

                if(key[ALLEGRO_KEY_UP])
                    current_option--;

                if(current_option > 3)
                    current_option = 0;

                if(current_option < 0)
                    current_option = 3;

                if(key[ALLEGRO_KEY_ESCAPE]){
                    if(draw_helper == 0){
                        destroy_main();
                        exit(0);
                    }
                    else
                        draw_helper = 0;
                }
                if(draw_helper == 0){
                    if(key[ALLEGRO_KEY_ENTER])
                        main_menu[current_option].handler();
                }
                break;


            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                destroy_main();
                exit(0);

        }
        handle_mouse_hover_and_click(&event);
        keyboard_update(&event);
        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_bgspace();
            draw_all_asteroids();
            draw[draw_helper]();
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    stop_menu_music();
}
