#include "fluid.h"
#define SDL_MAIN_HANDLED
#include <sdl2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define DELAY 3000

int main(void) {

  const int sizeX = 128;
  const int sizeY = 128;

  const double density = 0.1;
  const double timestep = 0.005;

  unsigned char *image = new unsigned char[sizeX * sizeY * 4];

  FluidSolver *solver = new FluidSolver(sizeX, sizeY, density);

  // Image raylibImage = Image(sizeX, sizeY, 1, 4);

  double time = 0.0;
  int iterations = 0;

  /* Initialises data */
  SDL_Window *window = NULL;

  /*
   * Initialises the SDL video subsystem (as well as the events subsystem).
   * Returns 0 on success or a negative error code on failure using
   * SDL_GetError().
   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  /* Creates a SDL window */
  window =
      SDL_CreateWindow("SDL Example",           /* Title of the SDL window */
                       SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
                       SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
                       sizeX, /* Width of the window in pixels */
                       sizeY, /* Height of the window in pixels */
                       0);    /* Additional flag(s) */

  /* Checks if window has been created; if not, exits program */
  if (window == NULL) {
    fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
    return 1;
  }

  while (1) {
    SDL_Event event;
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;

    for (int i = 0; i < 4; i++) {
      solver->addInflow(0.45, 0.2, 0.1, 0.01, 1.0, 0.0, 3.0);
      solver->update(timestep);
      time += timestep;
    }

    iterations++;

    solver->toImage(image);
    // draw pixel array
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_LockSurface(surface);
    // clear
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    // copy image to surface
    memcpy(surface->pixels, image, sizeX * sizeY * 4);

    SDL_UnlockSurface(surface);
    // SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    // SDL_UnlockSurface(surface);

    SDL_UpdateWindowSurface(window);
  }

  /* Frees memory */
  SDL_DestroyWindow(window);

  /* Shuts down all SDL subsystems */
  SDL_Quit();

  delete solver;
  delete[] image;

  return 0;
}