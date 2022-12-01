/*
Altere o exercício 5.1 da seguinte forma:
  - Faça os objetos se moverem somente no eixo X
  - Desenhe uma linha de chegada
  - Pare os objetos que atingirem a linha de chegada
  - Aguarde todos atingirem a linha de chegada
  - Anuncie o objeto que chegou primeiro
  - Reinicie a aplicação
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

#define TIMEOUT 100

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

int main(int argc, char** argv)
{
  /* INICIALIZACAO */
  srand(time(NULL));
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* win = SDL_CreateWindow("Jogos-1.6",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 400, SDL_WINDOW_SHOWN);
  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
  int running = 1;
  Uint32 timer = TIMEOUT;

  TTF_Init();
  TTF_Font* fnt = TTF_OpenFont("tiny.ttf", 40);
  assert(fnt != NULL);
  SDL_Color clr = {0x00,0x00,0x00,0xFF};
  SDL_Texture* txt = NULL;

  int winner = 0;
  int race_over = 0;
  SDL_Rect const finish = {760,0, 20,400};
  SDL_Rect r_tempo = {20,95, 20,20};
  SDL_Rect r_teclado = {20,195, 20,20};
  SDL_Rect r_mouse = {20,295, 20,20};

  while (running) {
    int tempo_chegou = SDL_HasIntersection(&finish, &r_tempo);
    int mouse_chegou = SDL_HasIntersection(&finish, &r_mouse);
    int teclado_chegou = SDL_HasIntersection(&finish, &r_teclado);
    if (!winner && tempo_chegou) {
      clr.r = 255;
    }
    if (!winner && mouse_chegou) {
      clr.b = 255;
    }
    if (!winner && teclado_chegou) {
      clr.g = 255;
    }

    if (!winner && teclado_chegou || mouse_chegou || tempo_chegou) {
      winner = 1;
      SDL_Surface* sfc = TTF_RenderText_Blended(fnt, "ganhou", clr);
      txt = SDL_CreateTextureFromSurface(ren, sfc);
      SDL_FreeSurface(sfc);
    }

    race_over = tempo_chegou && mouse_chegou && teclado_chegou;

    SDL_Event event;
    if (AUX_WaitEventTimeoutCount(&event, &timer)) {
      switch (event.type) {
      case SDL_QUIT:
        running = 0;
        break;
      case SDL_KEYDOWN:
        if (race_over && event.key.keysym.sym == SDLK_r) {
          // reiniciar
          r_tempo.x = r_teclado.x = r_mouse.x = 20;
          race_over = 0;
          winner = 0;
          clr.r = clr.g = clr.b = 0;
        } else if (!teclado_chegou && event.key.keysym.sym == SDLK_RIGHT) {
          r_teclado.x += 5;
        }
        break;
      case SDL_MOUSEMOTION:
        if (!mouse_chegou) {
          r_mouse.x = event.motion.x;
        }
        break;
      }
    } else if (!tempo_chegou) {
      r_tempo.x += (rand() % 3 + 1) * 5;
    }

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    if (winner) {
      int w, h;
      SDL_QueryTexture(txt, NULL, NULL, &w, &h);
      SDL_Rect r = { 20,20, w,h };
      SDL_RenderCopy(ren, txt, NULL, &r);
    }

    SDL_SetRenderDrawColor(ren, 200, 200, 100, 255);
    SDL_RenderFillRect(ren, &finish);

    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRect(ren, &r_tempo);

		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		SDL_RenderFillRect(ren, &r_teclado);
		
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		SDL_RenderFillRect(ren, &r_mouse);

		SDL_RenderPresent(ren);

    SDL_RenderPresent(ren);
  }

  /* FINALIZACAO */
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
