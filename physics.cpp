// physics.cpp: this will be a very short file since the "physics" won't be crazy
#include "header.hpp"

void solve_collision(SDL_FRect &a, SDL_FRect &b) {
	// assumption: a is the rigidbody always, its the one that moves
	if(a.x == b.x) {
		a.y = b.y + b.h;
	}

	else {
		a.x = b.x + b.w;
	}
}

// collision with wall
void solve_wall(SDL_FRect &a, float &v, float &w) {
	if(a.x <= 0) {
		a.x = 0 + ep;
		v = 0.01;
	}

	if(a.y <= 0) {
		a.y = 0 + ep;
		w = 0.01;
	}

	if(a.x >= HEIGHT - sizex) {
		a.x = HEIGHT - sizex - ep;
		v = -0.01;
	}

	if(a.y >= WIDTH - sizey) {
		a.y = WIDTH - sizey - ep;
		w = -0.01;
	}
}