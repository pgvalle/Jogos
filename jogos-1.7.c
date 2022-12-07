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
	SDL_Window *win = SDL_CreateWindow("Reddit gif",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		200, 200, SDL_WINDOW_SHOWN);
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
	int running = 1;
	Uint32 timer = TIMEOUT;

	IMG_Init(IMG_INIT_PNG);
	// ler imagem
	SDL_Texture *tex = IMG_LoadTexture(ren, "reddit_spritesheet.png");
	assert(tex != NULL);
	// setup da animacao
	// imagem tem 18 clips (35 frames no total contando as repeticoes de clips)
  struct AnimFrame frames[] = {
    {{0,0, 32,32}, 100},
    {{32,0, 32,32}, 100},
    {{64,0, 32,32}, 100},
    {{96,0 , 32,32}, 100},
    {{128,0 , 32,32}, 100},
    {{160,0 , 32,32}, 100},
    {{192,0 , 32,32}, 100},
    {{224,0 , 32,32}, 100},
    {{256,0 , 32,32}, 100},
    {{288,0 , 32,32}, 100},
    {{320,0 , 32,32}, 750},
    {{352,0 , 32,32}, 125},
    {{384,0 , 32,32}, 125},
    {{416,0 , 32,32}, 125},
    {{448,0 , 32,32}, 125},
    {{480,0 , 32,32}, 125},
    {{512,0 , 32,32}, 600},

    {{544,0 , 32,32}, 200},
    
    {{512,0 , 32,32}, 600},
    {{480,0 , 32,32}, 125},
    {{448,0 , 32,32}, 125},
    {{416,0 , 32,32}, 125},
    {{384,0 , 32,32}, 125},
    {{352,0 , 32,32}, 125},
    {{320,0 , 32,32}, 750},
    {{288,0 , 32,32}, 100},
    {{256,0 , 32,32}, 100},
    {{224,0 , 32,32}, 100},
    {{192,0 , 32,32}, 100},
    {{160,0 , 32,32}, 100},
    {{128,0 , 32,32}, 100},
    {{96,0 , 32,32}, 100},
    {{64,0, 32,32}, 100},
    {{32,0, 32,32}, 100},
    {{0,0, 32,32}, 100}
  };

  Uint32 before = 0, now = 0;
  Uint32 accum = 0;
  int i = 0;

  while (1)
  {
    // update dt
    before = now;
    now = SDL_GetTicks();

    SDL_Event event;
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;

    if (accum < frames[i].dt) {
      accum += now - before;
    } else {
      i = (i + 1) % 35;
      accum = 0;
    }

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, &frames[i].clip, NULL);
    SDL_RenderPresent(ren);
  }
	
	/* FINALIZACAO */
  SDL_DestroyTexture(tex);

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
