#include "sdl_audio.h"
#include <SDL.h>
#include <stdio.h>

double sdl_audio::time = 0;
double sdl_audio::cos_index_a4 = 0;
double sdl_audio::cos_index_c5 = 0;
double sdl_audio::cos_index_e5 = 0;
double sdl_audio::cos_index_g5 = 0;
uint64_t sdl_audio::sample_index = 0;
double sdl_audio::offset_time = 0;
const double frequency_c5 = 523.2511;
const double frequency_e5 = 659.2551;
const double frequency_g5 = 783.9909;


const double pi = 3.14159;
const double one_div_44khz = 1.0 / 44100.0;

void sdl_audio::audio_callback(void *udata, Uint8 *stream, int len)
{
  size_t stream_index = 0;
  size_t elements = static_cast<size_t>(len) / sizeof(float);
  for (size_t i = 0; i < elements / 2; i++)
  {
    float value = 0;//sinf( time );
    float frequency_offset = sinf(offset_time);

    value = value + sinf(cos_index_c5 + frequency_offset * 5) * 0.33;
    value = value + sinf(cos_index_e5 + frequency_offset * 5) * 0.33;
    value = value + sinf(cos_index_g5 + frequency_offset * 5) * 0.33;

    reinterpret_cast<float*>(stream)[stream_index] = value;
    reinterpret_cast<float*>(stream)[stream_index + 1] = value;

//    time += 440.0 * pi * one_div_44khz;
    stream_index += 2;

    cos_index_c5 += frequency_c5 * pi * one_div_44khz;
    cos_index_e5 += frequency_e5 * pi * one_div_44khz;
    cos_index_g5 += frequency_g5 * pi * one_div_44khz;

    offset_time += 5 * pi *one_div_44khz;
  }
  printf("stream index : %d\n", stream_index / 2);
}

sdl_audio::sdl_audio()
{
  SDL_InitSubSystem(SDL_INIT_AUDIO);
  SDL_AudioSpec want, have;

  SDL_zero(want);
  want.freq = 44100;
  want.format = AUDIO_F32;
  want.channels = 2;
  want.samples = 4096;
  want.callback = audio_callback;

  printf("DEBUG: before Open Audio Device\n");

  sound_device = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
  if (sound_device == 0) {
      printf("ERROR: AUDIO: Failed to open audio: %hs\n", SDL_GetError());
      return;
  }

  // everything is OK
  printf("DEBUG: sound device OK\n");

  // check format
  if (have.format != want.format)
      printf("ERROR: AUDIO: We didn't get Float32 audio format.\n");

  // pause = off
  SDL_PauseAudioDevice(sound_device, 0);
}

sdl_audio::~sdl_audio()
{
  SDL_CloseAudioDevice(sound_device);
}


