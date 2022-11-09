#include <SDL2/SDL.h>
#include <math.h>

#define TIMEOUT 17

typedef struct FLT_Rect {
	float x, y, w, h;
} FLT_Rect;

#define PI ((float)3.14159265358979323846)

void RotateRect(FLT_Rect* rect, float cx, float cy, int a) {
    float b = a * PI / 180.f; // para radianos

    float x = rect->x + 0.5f*rect->w;
    float y = rect->y + 0.5f*rect->h;

    rect->x = (x-cx)*cos(b) - (y-cy)*sin(b) + cx - 0.5f*rect->w;
    rect->y = (x-cx)*sin(b) + (y-cy)*cos(b) + cy - 0.5f*rect->h;
}

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
	static Uint32 antes, agora = 0;
	int event = SDL_WaitEventTimeout(evt, *ms);
	antes = agora;
	agora = SDL_GetTicks();
	if (event) {
		// algum evento aconteceu, espera menos da próxima
		if (agora - antes > *ms) *ms = 0;
		else *ms -= agora - antes;
	} else {
		// reseta o temporizador
		*ms = TIMEOUT;
	}

	return event;
}

int main(int argc, char *argv[]) {
	SDL_Window* win = SDL_CreateWindow("Jogos 1.5.2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		500, 500, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	Uint32 timeout = TIMEOUT;
	FLT_Rect r_tempo = {100, 100, 20, 20};
	SDL_Rect r_teclado = {480, 480, 20, 20};
	SDL_Rect r_mouse = {0, 480, 20, 20};

	while (1) {
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		{
			SDL_Rect tmp = {round(r_tempo.x), round(r_tempo.y), 20, 20};
			SDL_RenderFillRect(ren, &tmp);
		}

		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		SDL_RenderFillRect(ren, &r_teclado);
		
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		SDL_RenderFillRect(ren, &r_mouse);

		SDL_RenderPresent(ren);

		SDL_Event evt;
		int event = AUX_WaitEventTimeoutCount(&evt, &timeout);
		if (event) {
			if (evt.type == SDL_KEYDOWN) {
				switch (evt.key.keysym.sym) {
				case SDLK_UP:
					r_teclado.y -= 5; break;
				case SDLK_DOWN:
					r_teclado.y += 5; break;
				case SDLK_LEFT:
					r_teclado.x -= 5; break;
				case SDLK_RIGHT:
					r_teclado.x += 5; break;
				}
			} else if (evt.type == SDL_MOUSEMOTION) {
				r_mouse.x = evt.motion.x - 10;
				r_mouse.y = evt.motion.y - 10;
			} else if (evt.type == SDL_QUIT) break;
		} else {
			RotateRect(&r_tempo, 250, 250, 5);
		} 
	}

	return 0;
}
