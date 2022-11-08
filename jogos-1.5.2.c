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

// PROGRAMA EXEMPLO PARA TESTAR A FUNCAO
int main() {
	SDL_Window* win = SDL_CreateWindow("Jogos 1.5.2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		500, 500, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	Uint32 timeout = TIMEOUT;
	SDL_Rect rect = {0, 0, 20, 20};

	while (1) {
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRect(ren, &rect);

		SDL_RenderPresent(ren);

		SDL_Event evt;
		int event = AUX_WaitEventTimeoutCount(&evt, &timeout);
		if (event) {
			if (evt.type == SDL_KEYDOWN) {
				switch (evt.key.keysym.sym) {
				case SDLK_UP:
					rect.y -= 5; break;
				case SDLK_DOWN:
					rect.y += 5; break;
				case SDLK_LEFT:
					rect.x -= 5; break;
				case SDLK_RIGHT:
					rect.x += 5; break;
				}
			} else if (evt.type == SDL_QUIT) break;
		} else {
			rect.x += 20;
			rect.y += 20;
		}		
	}

	return 0;
}
