#pragma once

#include <SDL.h>

class sdl_audio
{
  static double time;
  static double cos_index_a4;
  static double cos_index_c5;
  static double cos_index_e5;
  static double cos_index_g5;
  static uint64_t sample_index;
  static double offset_time;

  SDL_AudioDeviceID sound_device;
  static void audio_callback(void *udata, Uint8 *stream, int len);

public:

  sdl_audio();
  ~sdl_audio();

};
