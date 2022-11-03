#include <SDL2/SDL.h>
#include <math.h>

// So do sdl 2.0.10 para cima que tem o SDL_FRect
typedef struct Float_Rect {
    float x, y, w, h;
} Float_Rect;

#define PI ((float)3.14159265358979323846)

void rotate_rect(Float_Rect* rect, float cx, float cy, int a)
{
    float b = a * PI / 180.f; // para radianos

    float x = rect->x + 0.5f*rect->w;
    float y = rect->y + 0.5f*rect->h;

    rect->x = (x-cx)*cos(b) - (y-cy)*sin(b) + cx - 0.5f*rect->w;
    rect->y = (x-cx)*sin(b) + (y-cy)*cos(b) + cy - 0.5f*rect->h;
}

int main()
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Jogos-1.3.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 200, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    int running = 1;

    float cx = 100;
	float cy = 100; // centro
    Float_Rect rect = {70, 70, 20, 20};

    const int frame_dt = 175;
	const int graus_rot = 5;
	const float radians_rot = graus_rot * PI / 180.f;
	// a distancia (raio) do centro da rotacao até o centro do quadrado e 20
	const float raio = abs((rect.x + 0.5f*rect.w) - cx);
	const float linear_vel = raio * radians_rot / (1e-3*frame_dt);

	printf("velocidade: %f\n", linear_vel);

	/* EXECUCAO */
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }
        
        // Limpa a tela
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        // rotacao        
        rotate_rect(&rect, cx, cy, graus_rot);
        // desenha
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	    SDL_Rect ri = {(int)round(rect.x), (int)round(rect.y), (int)rect.w, (int)rect.h};
        SDL_RenderDrawRect(ren, &ri);
        // SDL_RenderDrawRectF(ren, &r); // Somente do sdl 2.0.10 para cima
        SDL_RenderPresent(ren);

        SDL_Delay(frame_dt);
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

