#include "game.hpp"

#include <iostream>
#include <SDL2/SDL.h>

Game::Game(const char* title, int width, int height)
{
  m_window = SDL_CreateWindow(title
    , SDL_WINDOWPOS_CENTERED
    , SDL_WINDOWPOS_CENTERED
    , width
    , height
    , false);

  m_surface = SDL_GetWindowSurface(m_window);

  Renderer = SDL_CreateRenderer(m_window, -1, false);

  Running = true;
}

Game::~Game()
{
  SDL_FreeSurface(m_surface);
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
  Running = false;
}

void Game::handleEvents()
{
  while ( SDL_PollEvent( &m_windowEvent ) != 0)
  {
    switch (m_windowEvent.type)
    {
      case SDL_QUIT:
        Running = false;
        break;
    }
  }
}

void Game::update(double lag)
{
  std::cout << static_cast<int>(count++) << '\n';
  std::cout << "Updating game at: x" << lag << " speed.\n";
}

void Game::draw()
{
  SDL_RenderClear(Renderer);

  SDL_UpdateWindowSurface(m_window);

  std::cout << "Drawing game.\n";
}
