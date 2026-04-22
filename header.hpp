#include <SDL3/SDL_rect.h>

#define HEIGHT 640
#define WIDTH 480

const float sizex = 10.f;
const float sizey = 30.f;
const float ep = 0.0001f;
const float vLIM = 10.f;
const int clr_boy[3] = {37, 42, 52};
const int clr_girl[3] = {234, 234, 234};
const int clr_bg[3] = {255, 46, 99};
const int clr_blk[3] = {8, 217, 214};
const float gravity = 0.000097;

void solve_collision(SDL_FRect &a, SDL_FRect &b);
void solve_wall(SDL_FRect &a, float &v, float &w);