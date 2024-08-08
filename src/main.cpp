#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>

#include "game.hpp"
#include "timings.hpp"

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "Failed to initialise SDL.\n";
    std::cout << "SDL error: " << SDL_GetError() << '\n';
    return -1;
  }

  Game game("wah", 640, 480);

  FrameTime timer {60, 20};

  while (game.Running)
  {
    timer.getTime();

    game.handleEvents();

    // Only update at fixed tickrate
    while (timer.FrameAccumulator >= timer.TickRate)
    {
      game.update(timer.FrameAccumulator / timer.TickRate);
      timer.FrameAccumulator -= timer.TickRate;
    }

    game.draw();
  }
}