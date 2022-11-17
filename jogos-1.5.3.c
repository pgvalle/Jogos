#include <SDL2/SDL.h>
#include <math.h>

// So do sdl 2.0.10 para cima que tem o SDL_FRect
typedef struct Float_Rect {
  float x, y, w, h;
} Float_Rect;

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

#define PI ((float)3.14159265358979323846)

void rotate_rect(Float_Rect* rect, float cx, float cy, int a)
{
	if (a == 0) return;

	float b = a * PI / 180.f; // para radianos

	float x = rect->x + 0.5f*rect->w;
	float y = rect->y + 0.5f*rect->h;

	rect->x = (x-cx)*cos(b) - (y-cy)*sin(b) + cx - 0.5f*rect->w;
	rect->y = (x-cx)*sin(b) + (y-cy)*cos(b) + cy - 0.5f*rect->h;
}

// MODIFICAÇOES:
// pausar/continuar         - espaço
// acelerar/desacelerar     - Up/Down
// reverter                 - r
// aumentar/diminuir o raio - a/s

int main()
{
    /* INICIALIZACAO */
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* win = SDL_CreateWindow("Jogos-1.5.3",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    200, 200, SDL_WINDOW_SHOWN);
  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
	Uint32 timer = TIMEOUT;

	// centro
  float const cx = 100;
	float const cy = 100;
	int rot_step = 5;
	int rot_step_tmp = rot_step;
  Float_Rect rect = {70, 70, 20, 20}; // retangulo para rodar


	/* EXECUCAO */
  while (1) {
    SDL_Event event;
		if (AUX_WaitEventTimeoutCount(&event, &timer)) {
			if (event.type == SDL_QUIT) break;
			else if (event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
				case SDLK_SPACE:
					rot_step = rot_step != 0 ? 0 : rot_step_tmp; break;
				case SDLK_UP:
					if (rot_step > 0) rot_step++;
					else if (rot_step < 0) rot_step--;
					if (rot_step != 0) rot_step_tmp = rot_step;
					break;
				case SDLK_DOWN:
					if (rot_step > 1) rot_step--;
					else if (rot_step < -1) rot_step++;
					if (rot_step != 0) rot_step_tmp = rot_step;
					break;
				case SDLK_r:
					if (rot_step != 0) rot_step_tmp = rot_step = -rot_step;
					break;
				case SDLK_a:
					if (rect.x + rect.w / 2 < cx) rect.x--;
					else if (rect.x + rect.w / 2 > cx) rect.x++;
					if (rect.y + rect.h / 2 < cy) rect.x--;
					else if (rect.y + rect.h / 2 > cy) rect.y++;
					break;
				case SDLK_s:
					if (rect.x + rect.w / 2 < cx) rect.x++;
					else if (rect.x + rect.w / 2 > cx) rect.x--;
					if (rect.y + rect.h / 2 < cy) rect.x++;
					else if (rect.y + rect.h / 2 > cy) rect.y--;
					break;
				}
			}
		} else rotate_rect(&rect, cx, cy, rot_step);
        
    // Limpa a tela
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    
    // desenha
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    {
			SDL_Rect ri = {round(rect.x), round(rect.y), rect.w, rect.h};
    	SDL_RenderDrawRect(ren, &ri);
		}
    SDL_RenderPresent(ren);
  }

  /* FINALIZACAO */
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}

