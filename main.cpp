#include <stdio.h>
#include "setup.h"

SDL_Window *window = nullptr;
SDL_GLContext context;
sdl_audio* audio = nullptr;

int main(int argc, char* argv[])
{
  setup();
  run();
  return 0;
}
