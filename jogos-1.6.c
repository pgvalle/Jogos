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
  SDL_Window* win = SDL_CreateWindow("Jogos-1.5.3",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 400, SDL_WINDOW_SHOWN);
  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
  int running = 1;
	Uint32 timer = TIMEOUT;

  int winner = 0;
  int race_over = 0;
  SDL_Rect const finish = {760, 0, 20, 400};
  SDL_Rect rects[3] = {{20,95, 20,20}, {20,195, 20,20}, {20,295, 20,20}};
  SDL_Color colors[3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};

  while (running) {
    SDL_Event event;
    if (AUX_WaitEventTimeoutCount(&event, &timer)) {
      switch (event.type) {
      case SDL_QUIT:
        running = 0;
        break;
      case SDL_KEYDOWN:
        if (race_over && event.key.keysym.sym == SDLK_r) {
          for (int i = 0; i < 3; i++)
            rects[i].x = 20;
          race_over = 0;
          winner = 0;
        }
        break;
      }
    } else if (!race_over) {
      int count = 0;
      for (int i = 0; i < 3; i++) {
        int rect_pace = (rand() % 3 + 1) * 5;
        rects[i].x += rect_pace;
        if (SDL_HasIntersection(&finish, &rects[i])) {
          if (!winner) {
            winner = i + 1;
            printf("O retangulo %d (de cima para baixo) venceu!\n", winner);
          }
          rects[i].x = finish.x - rects[i].w;
          count++;
        }
      }

      if (count == 3) {
        race_over = 1;
      }
    }

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 200, 200, 100, 255);
    SDL_RenderFillRect(ren, &finish);

    for (int i = 0; i < 3; i++) {
      SDL_SetRenderDrawColor(ren, colors[i].r, colors[i].g, colors[i].b, 255);
      SDL_RenderFillRect(ren, &rects[i]);
    }

    SDL_RenderPresent(ren);
  }

  if (!race_over) {
    printf("Ninguem ganhou dessa vez. Voce terminou a aplicacao!\n");
  }

  /* FINALIZACAO */
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}