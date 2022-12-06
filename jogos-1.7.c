#include <assert.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TIMEOUT 17

int AUX_WaitEventTimeoutCount(SDL_Event* event, Uint32* ms)
{
	static Uint32 antes, agora = 0;
	int happened = SDL_WaitEventTimeout(event, *ms);
	antes = agora;
	agora = SDL_GetTicks();
	if (happened) {
		// algum evento aconteceu, espera menos da próxima
		if (agora - antes > *ms) *ms = 0;
		else *ms -= agora - antes;
	} else {
		// reseta o temporizador
		*ms = TIMEOUT;
	}

	return happened;
}


struct AnimFrame
{
	SDL_Rect clip;
	Uint32 dt;
};

int main()
{
	/* INICIALIZACAO */
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *win = SDL_CreateWindow("Jogos-1.6",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 400, SDL_WINDOW_SHOWN);
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
	int running = 1;
	Uint32 timer = TIMEOUT;

	IMG_Init(IMG_INIT_PNG);
	// ler imagem
	SDL_Texture *tex = IMG_LoadTexture(ren, "reddit_spritesheet.png");
	assert(tex != NULL);
	// setup da animacao
	// imagem tem 18 frames (x2 porque vai repetir)
	struct AnimFrame frames[] = {
		
	};
	
	/* FINALIZACAO */
	SDL_DestroyTexture(tex);

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

	return 0;
}
