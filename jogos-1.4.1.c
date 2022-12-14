#include <SDL2/SDL.h>
#include <stdlib.h>

#define RECT_MAX 10
#define RECT_SIZE 10

void keep_rect_in_screen(SDL_Rect* rect)
{
  if (rect->x + rect->w >= 200)
    rect->x = 200 - rect->w;
  else if (rect->x < 0)
    rect->x = 0;
  if (rect->y + rect->h >= 100)
    rect->y = 100 - rect->h;
  else if (rect->y < 0)
    rect->y = 0;
}

void generate_colored_rect(int x, int y, SDL_Rect* rect, SDL_Color* color)
{
	rect->x = x - RECT_SIZE / 2;
	rect->y = y - RECT_SIZE / 2;
	rect->w = RECT_SIZE;
	rect->h = RECT_SIZE;

	if (x + RECT_SIZE / 2 >= 200)
		rect->x = 200 - RECT_SIZE;
	else if (x - RECT_SIZE / 2 < 0)
		rect->x = 0;
	if (y + RECT_SIZE / 2 >= 100)
		rect->y = 100 - RECT_SIZE;
	else if (y - RECT_SIZE / 2 < 0)
		rect->y = 0;

	color->r = rand() % 200;
	color->g = rand() % 200;
	color->b = rand() % 200;
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    200, 100, SDL_WINDOW_SHOWN);
  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
  int running = 1;

	SDL_Rect rects[RECT_MAX];
	SDL_Color colors[RECT_MAX];
	int rect_count = 0;

  /* EXECUÇÃO */
  SDL_Rect r = { 40,20, 10,10 };
  SDL_Event evt;
  while (running) {
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);

    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(ren, &r);

    for (int i = 0; i < rect_count && i < RECT_MAX; i++) {
      SDL_SetRenderDrawColor(ren, colors[i].r, colors[i].g, colors[i].b, 0xff);
      SDL_RenderFillRect(ren, &rects[i]);
    }

    SDL_RenderPresent(ren);

    SDL_WaitEvent(&evt);
    switch(evt.type) {
    case SDL_QUIT:
      running = 0;
      break;
    case SDL_KEYDOWN:
      switch (evt.key.keysym.sym) {
      case SDLK_UP:
        r.y -= 5; break;
      case SDLK_DOWN:
        r.y += 5; break;
      case SDLK_LEFT:
        r.x -= 5; break;
      case SDLK_RIGHT:
        r.x += 5; break;
      }
      keep_rect_in_screen(&r);
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (rect_count >= RECT_MAX) break;
      generate_colored_rect(evt.button.x, evt.button.y,
      &rects[rect_count], &colors[rect_count]);
			rect_count++;
      break;
    }
  }

  /* FINALIZACAO */
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
