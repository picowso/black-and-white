#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "header.hpp"

using namespace std;
/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
// const float sizex = 10.f;
// const float sizey = 30.f;

float vel_boy[2] = {0.f, 0.f};
float vel_girl[2] = {0.f, 0.f};

float slidef = 0.0001f;

long long ljb = 0;
long long ljg = 0; // last jump boy/girl.

const float jumpf = 0.001f;
SDL_FPoint boypos = {300.f, 300.f};
SDL_FPoint girlpos = {100.f, 200.f};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Black and white", "1.0", "com.blacknwhite.exec");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", HEIGHT, WIDTH, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, HEIGHT, WIDTH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if(event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

float min(float a, float b) {
    if(a > b) return b;
    return a;
}

void dec_abs(float &a) {
    if(a>0)a-=0.000001f;
    else a+=0.000001f;
}

void keyevents() {
    const bool *keys = SDL_GetKeyboardState(NULL);

    // boy (wasd)
    if(keys[SDL_SCANCODE_D]) {
        vel_boy[0] += slidef;
        boypos.x += 0.01f;
        if(vel_boy[0] > vLIM) vel_boy[0] -= slidef;
        if(vel_boy[0] < 0) vel_boy[0] /= 10.f;
    }

    if(keys[SDL_SCANCODE_A]) {
        vel_boy[0] -= slidef;
        if(-vel_boy[0] > vLIM) vel_boy[0] += slidef;
        if(vel_boy[0] > 0) vel_boy[0] /= 10.f;
    }

    if(keys[SDL_SCANCODE_W]) {
        vel_boy[1] -= jumpf;
    }

    // girl (arrows)
    if(keys[SDL_SCANCODE_RIGHT]) {
        vel_girl[0] += slidef;
        if(vel_girl[0] > vLIM) vel_girl[0] -= slidef;
        if(vel_girl[0] < 0) vel_girl[0] /= 10.f;
    }

    if(keys[SDL_SCANCODE_LEFT]) {
        vel_girl[0] -= slidef;
        girlpos.x += 0.01f;
        if(-vel_girl[0] > vLIM) vel_girl[0] += slidef;
        if(vel_girl[0] > 0) vel_girl[0] /= 10.f;
    }

    if(keys[SDL_SCANCODE_UP]) {
        vel_girl[1] -= jumpf;
    }
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
    // boyngirl vals
    keyevents();
    vel_boy[1] += gravity;
    vel_girl[1] += gravity;
    for(int i = 0 ; i < 2 ; i++) {
        vel_boy[i] *= 0.999;
        vel_girl[i] *= 0.999;
    }

    boypos.x += vel_boy[0];
    girlpos.x += vel_girl[0];
    boypos.y += vel_boy[1];
    girlpos.y += vel_girl[1];

    dec_abs(vel_boy[0]);
    dec_abs(vel_boy[1]);


    
    SDL_FRect boy = {boypos.x, boypos.y, sizex, sizey};
    SDL_FRect girl = {girlpos.x, girlpos.y, sizex, sizey};
    solve_wall(boy, vel_boy[0], vel_boy[1]);
    solve_wall(girl, vel_girl[0], vel_girl[1]);

    /* clear the window to the draw color. */
    SDL_SetRenderDrawColor(renderer, clr_bg[0], clr_bg[1], clr_bg[2], SDL_ALPHA_OPAQUE);  /* yellow, full alpha */
    SDL_RenderClear(renderer);

    /* draw boy and girl */
    SDL_SetRenderDrawColor(renderer, clr_boy[0], clr_boy[1], clr_boy[2], SDL_ALPHA_OPAQUE);  /* yellow, full alpha */
    SDL_RenderFillRect(renderer, &boy);

    SDL_SetRenderDrawColor(renderer, clr_girl[0], clr_girl[1], clr_girl[2], SDL_ALPHA_OPAQUE);  /* yellow, full alpha */
    SDL_RenderFillRect(renderer, &girl);

    // draw border
    SDL_SetRenderDrawColor(renderer, clr_blk[0], clr_blk[1], clr_blk[2], SDL_ALPHA_OPAQUE);  /* yellow, full alpha */
    SDL_FRect brdr = {0.f, 0.f, HEIGHT, WIDTH};
    SDL_RenderRect(renderer, &brdr);
    cout << vel_boy[0] << " " << vel_boy[1] << endl;
    cout << vel_girl[0] << " " << vel_girl[1] << endl;

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) { /* SDL will clean up the window/renderer for us. */ }

