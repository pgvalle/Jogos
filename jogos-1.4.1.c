#include <SDL2/SDL.h>
#include <stdlib.h>

#define RECT_MAX 10
#define RECT_SIZE 10

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
		rect->y = 0;
	else if (y - RECT_SIZE / 2 < 0)
		rect->y += RECT_SIZE / 2;

	color->r = rand() % 200;
	color->g = rand() % 200;
	color->b = rand() % 200;
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

	SDL_Rect rects[RECT_MAX];
	SDL_Color colors[RECT_MAX];
	int rect_count = 0;

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);

		for (int i = 0; i < rect_count && i < RECT_MAX; i++) {
			SDL_SetRenderDrawColor(ren, colors[i].r, colors[i].g, colors[i].b, 0xff);
			SDL_RenderFillRect(ren, &rects[i]);
		}

        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 5;
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    break;
            }
        } else if (evt.type == SDL_MOUSEBUTTONDOWN && rect_count < RECT_MAX) {
			generate_colored_rect(evt.button.x, evt.button.y,
				&rects[rect_count], &colors[rect_count]);
			rect_count++;
		} else if (evt.type == SDL_QUIT) break;
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
