#pragma once

#include <SDL2/SDL_timer.h>

class FrameTime
{
public:
  FrameTime(int targetFramerate, int ticksPerSecond)
  : m_targetFPS { targetFramerate }
{
  m_frameLast = SDL_GetTicks64();
  TickRate = 1000.0 / ticksPerSecond;
}

  void getTime()
{
  m_frameStart = SDL_GetTicks64();
  m_frameDelta = m_frameStart - m_frameLast;
  m_frameLast = m_frameStart;
  FrameAccumulator += m_frameDelta;
}

public:
  int TickRate {};
  double FrameAccumulator {};

private:
  int m_targetFPS {};
  uint64_t m_frameStart {};
  uint64_t m_frameLast {};
  double m_frameDelta {};
};