#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

// desenho do simbolo do reddit
// cores:
// d75413 e ffffff

int main()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* win = SDL_CreateWindow("Jogos 1.2.2",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    512, 512, 0);
  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
  
  while (1) {
    SDL_Event event;
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) break;

    SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(ren);
    
    // fundo redondo laranja
    filledEllipseColor(ren, 256, 256, 256, 256, 0xff0045ff);
    // ponta da antena
    filledEllipseColor(ren, 360, 125, 28, 28, 0xffffffff);
    // antena
    thickLineColor (ren, 276, 110, 360, 125, 12, 0xffffffff);
    thickLineColor (ren, 276, 104, 256, 200, 12, 0xffffffff);

    // orelhas
    filledEllipseColor(ren, 389, 256, 35, 35, 0xffffffff); // direita
    filledEllipseColor(ren, 123, 256, 35, 35, 0xffffffff); // esquerda
    // forma da cara
    filledEllipseColor(ren, 256, 296, 150, 100, 0xffffffff);
    // olhos
    filledEllipseColor(ren, 316, 281, 28, 28, 0xff0045ff); // direito
    filledEllipseColor(ren, 196, 281, 28, 28, 0xff0045ff); // esquerdo

    SDL_RenderPresent(ren);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
