#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event8 evt, UInt32* ms) {
	
}

int main() {
	SDL_Window* win = SDL_CreateWindow("Jogos 1.5.2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		500, 500, 0);
	SDL_Renderer* ren = SDL_CreateRender(win, -1, 0);
	
	while (1) {
		
	}

	return 0;
}
