#include <SDL2/SDL.h>
#include <iostream>

#include "timings.hpp"

bool gRunning { true };

SDL_Window* gWindow = SDL_CreateWindow(""
                                      , SDL_WINDOWPOS_CENTERED
                                      , SDL_WINDOWPOS_CENTERED
                                      , 640
                                      , 480
                                      , 0);

SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
SDL_Event m_windowEvent;
FrameTime gTimer{60, 20};
uint8_t randomCounter {};

bool checkCollision( const SDL_Rect a, const SDL_Rect b)
{
  const int leftA { a.x };
  const int rightA { a.x + a.w };
  const int topA { a.y };
  const int bottomA { a.y + a.h };
  const int leftB { b.x };
  const int rightB { b.x + b.w };
  const int topB { b.y };
  const int bottomB { b.y + b.h };

  if (bottomA <= topB)
    return false;
  if (topA >= bottomB)
    return false;
  if (rightA <= leftB)
    return false;
  if (leftA >= rightB)
    return false;
  return true;
}

int main()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cout << "Failed to initialise SDL.\n";
    std::cout << "SDL error: " << SDL_GetError() << '\n';
    return -1;
  }

  SDL_Rect paddleLeft { 50, 150, 20, 150 };
  SDL_Rect paddleRight { 540, 150, 20, 150 };
  constexpr SDL_Rect outlineLeft { 25, 75, 10, 380 };
  constexpr SDL_Rect outlineRight { 615, 75, 10, 380 };
  constexpr SDL_Rect outlineTop { 25, 75, 590, 10 };
  constexpr SDL_Rect outlineBottom { 25, 455, 590, 10 };
  SDL_Rect ball { 310, 250, 20, 20 };
  double paddleLvelY { 0 };
  double paddleRvelY { 0 };
  int ballVelY { 2 };
  int ballVelX { 5 };

  while (gRunning)
  {
    while (SDL_PollEvent(&m_windowEvent) != 0)
    {
      switch (m_windowEvent.type)
      {
        case SDL_QUIT:
          gRunning = false;
          break;
        case SDL_KEYDOWN:
          switch (m_windowEvent.key.keysym.sym)
          {
            case SDLK_UP:
              paddleRvelY = -5;
              break;
            case SDLK_DOWN:
              paddleRvelY = 5;
              break;
            case SDLK_w:
              paddleLvelY = -5;
              break;
            case SDLK_s:
              paddleLvelY = 5;
              break;
          }
          break;
        case SDL_KEYUP:
          switch (m_windowEvent.key.keysym.sym)
          {
            case SDLK_UP:
              if (paddleRvelY < 0)
                paddleRvelY = 0;
              break;
            case SDLK_DOWN:
              if (paddleRvelY > 0)
                paddleRvelY = 0;
              break;
            case SDLK_w:
              if (paddleLvelY < 0)
                paddleLvelY = 0;
              break;
            case SDLK_s:
              if (paddleLvelY > 0)
                paddleLvelY = 0;
              break;
          }
      }
    }
    gTimer.getTime();

    while (gTimer.FrameAccumulator >= gTimer.TickRate)
    {
      ++randomCounter;
      if (paddleLeft.y < 100)
        paddleLeft.y = 100;
      if (paddleLeft.y > 280)
        paddleLeft.y = 280;
      paddleLeft.y += paddleLvelY * (gTimer.FrameAccumulator / gTimer.TickRate);

      if (paddleRight.y < 100)
        paddleRight.y = 100;
      if (paddleRight.y > 280)
        paddleRight.y = 280;
      paddleRight.y += paddleRvelY * (gTimer.FrameAccumulator / gTimer.TickRate);

      if (checkCollision(paddleLeft, ball) || checkCollision(paddleRight, ball))
        if (randomCounter < 150)
          ballVelX += 5;
        ballVelX = -ballVelX;
      ball.x += ballVelX;
      if (checkCollision( outlineBottom, ball) || checkCollision(outlineTop, ball))
      {
        if (randomCounter < 20)
          ballVelY += 5;
        else if (randomCounter < 100)
          ballVelY += 2;
        else if (randomCounter < 200)
          ballVelY -= 2;
        else
          ballVelY = 2;
        ballVelY = -ballVelY;
      }
      ball.y += ballVelY;

      gTimer.FrameAccumulator -= gTimer.TickRate;
    }
      SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
      SDL_RenderClear(gRenderer);
      SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
      SDL_RenderFillRect(gRenderer, &outlineLeft);
      SDL_RenderFillRect(gRenderer, &outlineRight);
      SDL_RenderFillRect(gRenderer, &outlineTop);
      SDL_RenderFillRect(gRenderer, &outlineBottom);
      SDL_RenderFillRect(gRenderer, &paddleLeft);
      SDL_RenderFillRect(gRenderer, &paddleRight);
      SDL_RenderFillRect(gRenderer, &ball);
      SDL_RenderPresent(gRenderer);
  }

  SDL_DestroyWindow(gWindow);
  SDL_Quit();
}