
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int main() {
	// inicialização
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* win = SDL_CreateWindow("Jogos-1.2.1",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		400, 240, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

	// coisas pra desenhar
	SDL_Point hexagono[] = {
		{100, 60}, {140, 40}, {180, 60},
		{180, 100}, {140, 120}, {100, 100}, {100, 60}
	}; // um hexagono
	SDL_Point triangulo[] = {
		{300, 20}, {360, 70}, {240, 70}, {300, 20}
	}; // triangulo
	SDL_Rect r1 = {200, 180, 100, 40};
	SDL_Rect r2 = {300, 80, 80, 80};
	SDL_Rect r3 = {10, 10, 80, 100};
	SDL_Rect r4 = {10, 120, 80, 100};
	
	SDL_Point randlines[40] = {};
	for (int i = 0; i < 40; i++) {
		randlines[i] = (SDL_Point) {abs(rand() % 400), abs(rand() % 240)};
	}
	
	// execução
		
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
	SDL_RenderClear(ren);
	
	// meus desenhos
	SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
	
	SDL_RenderDrawLines(ren, hexagono, sizeof(hexagono) / sizeof(SDL_Point));
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
	
	SDL_RenderDrawLines(ren, triangulo,  sizeof(triangulo) / sizeof(SDL_Point));
	SDL_SetRenderDrawColor(ren, 0, 255, 0, 0);
	SDL_RenderFillRect(ren, &r1);
	
	SDL_SetRenderDrawColor(ren, 255, 255, 0, 0);
	SDL_RenderFillRect(ren, &r2);
	
	SDL_SetRenderDrawColor(ren, 255, 0, 255, 0);
	SDL_RenderFillRect(ren, &r3);
	
	SDL_SetRenderDrawColor(ren, 0, 255, 255, 0);
	SDL_RenderDrawRect(ren, &r4);
	
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderDrawLines(ren, randlines, 40);
	
	SDL_RenderPresent(ren);
	
	SDL_Delay(5000);
	
	// finalização
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}