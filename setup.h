#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <sdl_audio.h>

extern SDL_Window *window;
extern SDL_GLContext context;
extern sdl_audio* audio;

void setup()
{
  // make sure we don't get spinning wheel
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER) < 0)
  {
    printf("Error initializing SDL\n");
    return;
  }

//  SDL_version compiled;
  SDL_version linked;

//  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);

  printf("SDL Version: %d.%d.%d\n", linked.major, linked.minor, linked.patch);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_DisableScreenSaver();

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // regular window, custom resolution, borderless optional
  window = SDL_CreateWindow(
      "SDL Audio Test",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      512,
      128,
      SDL_WINDOW_OPENGL
      | SDL_WINDOW_RESIZABLE
      | SDL_WINDOW_ALLOW_HIGHDPI
      | SDL_WINDOW_SHOWN
    );

  SDL_ShowCursor(SDL_DISABLE);
  context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent( window, context );
  SDL_GL_SetSwapInterval(1);

  audio = new sdl_audio();
}

void run()
{
  bool running = true;
  while( running )
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_WINDOWEVENT:
          switch (event.window.event)
          {
            case SDL_WINDOWEVENT_CLOSE:
              running = false;
            break;

            default:
            break;

          }
        break;
      }
    }
    SDL_GL_SwapWindow(window);
  }

  // Close OpenGL window and terminate
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  SDL_Quit();
}
