#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

// desenho do simbolo do reddit
// cores:
// d75413 e ffffff

int main()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* win = SDL_CreateWindow("Reddit",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    512, 512, 0);
  SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

  SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(ren);
    
  // fundo redondo laranja
  filledEllipseColor(ren, 256, 256, 256, 256, 0xff0045ff);
  // ponta da antena
  filledEllipseColor(ren, 360, 125, 27, 27, 0xffffffff);
  // antena
  thickLineColor (ren, 276, 110, 360, 125, 12, 0xffffffff);
  thickLineColor (ren, 276, 105, 256, 200, 12, 0xffffffff);
  // orelhas
  filledEllipseColor(ren, 389, 256, 36, 36, 0xffffffff); // direita
  filledEllipseColor(ren, 123, 256, 36, 36, 0xffffffff); // esquerda
  // forma da cara
  filledEllipseColor(ren, 256, 296, 150, 100, 0xffffffff);
  // olhos
  filledEllipseColor(ren, 316, 281, 27, 27, 0xff0045ff); // direito
  filledEllipseColor(ren, 196, 281, 27, 27, 0xff0045ff); // esquerdo
  // boca
  Sint16 x[] = {196, 212, 256, 300, 316};
  Sint16 y[] = {335, 350, 360, 350, 335};
  for (int j = 0; j < 12; j++) {
    for (int i = 0; i < 5; i++)
      y[i] += 1;
    bezierColor(ren, x, y, 5, 2, 0xff0045ff);
  }

  SDL_RenderPresent(ren);

  SDL_Delay(5000);

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
