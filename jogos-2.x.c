#include <SDL2/SDL.h>
#include <stdbool.h>

#define TIMEOUT 17

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms)
{
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

int main()
{
  /* INICIALIZACAO */
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* win = SDL_CreateWindow("Jogos-1.5.3",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		500, 500, SDL_WINDOW_SHOWN);
  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
  bool running = true;
	Uint32 timer = TIMEOUT;

  SDL_Rect quad = {220,200, 60,60};
  SDL_Point quad_tmp_pos;
  bool on_press = false;
  bool moved = false;

  /* EXECUCAO */
  while (running) {
    SDL_Event event;
    int occurred = AUX_WaitEventTimeoutCount(&event, &timer);
    if (occurred) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          quad_tmp_pos.x = quad.x;
          quad_tmp_pos.y = quad.y;
          int x = event.button.x;
          int y = event.button.y;
          // nao tem SDL_PointInRect na versao do computador do laboratorio
          on_press = !(x < quad.x || x > quad.x + quad.w ||
            y < quad.y || y > quad.y + quad.h);
          moved = false;
        }
        break;
      case SDL_MOUSEBUTTONUP:
        // not pressed anymore
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (moved && on_press) {
            printf("Dropped!\n");        
          } else if (on_press) {
            printf("Clicked!\n");
          }
          on_press = moved = false;
        }
        break;
      case SDL_MOUSEMOTION:
        if (on_press) {
          quad.x += event.motion.xrel;
          quad.y += event.motion.yrel;
          
          if (!moved)
            printf("Dragging...\n");
        }
        moved = true;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE && moved && on_press) {
          quad.x = quad_tmp_pos.x;
          quad.y = quad_tmp_pos.y;
        }

        if (on_press)
          printf("Aborted!\n");

        on_press = moved = false;
        break;
      }
    }

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderFillRect(ren, &quad);

    SDL_RenderPresent(ren);
  }

  /* FINALIZACAO */
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
