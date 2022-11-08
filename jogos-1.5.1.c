#include <SDL2/SDL.h>

#define TIMEOUT 2000

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms) {
	static Uint32 antes, agora = 0;
	int event = SDL_WaitEventTimeout(evt, *ms);
	antes = agora;
	agora = SDL_GetTicks();
	if (event) {
		// algum evento aconteceu, espera menos da próxima
		if (agora - antes > *ms)
			*ms = 0;
		else
			*ms -= agora - antes;
	} else {
		// reseta o temporizador
		*ms = TIMEOUT;
	}

	return event;
}

int main() {
	SDL_Window* win = SDL_CreateWindow("Jogos 1.5.2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		500, 500, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	Uint32 timeout = TIMEOUT;
	int primeira = 1;
	SDL_Rect r_tempo = {0, 0, 20, 20};
	SDL_Rect r_teclado = {480, 480, 20, 20};
	SDL_Rect r_mouse = {0, 480, 20, 20};

	while (1) {
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRect(ren, &r_tempo);
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
				if (primeira) {
					r_mouse.x = evt.motion.x;
					r_mouse.y = evt.motion.y;
				} else {
					r_mouse.x += evt.motion.xrel;
					r_mouse.y += evt.motion.yrel;
				}
			} else if (evt.type == SDL_QUIT) break;
		} else {
			r_tempo.x += 20;
			r_tempo.y += 20;
		} 
	}

	return 0;
}
