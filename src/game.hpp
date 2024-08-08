//
// Created by kae on 07/08/24.
//

#pragma once
#include <SDL2/SDL.h>

class Game
{
public:
  Game(const char* title, int width, int height);
  ~Game();

  void handleEvents();
  void update(double lag);
  void draw();

  void close();

public:
  SDL_Renderer *Renderer { nullptr };
  bool Running {};

private:
  SDL_Window *m_window { nullptr };
  SDL_Surface* m_surface { nullptr };
  SDL_Event m_windowEvent {};
  uint8_t count {};
};