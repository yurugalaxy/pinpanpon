#pragma once

#include <random>
#include <chrono>
#include <bitset>
#include <SDL2/SDL_timer.h>

//PRNG currently only for 8bit uints
namespace Random
{

  uint8_t get8bitSeed()
  {
    return static_cast<uint8_t>(std::chrono::steady_clock::now().time_since_epoch().count());
  }

  void rando8bit(uint8_t& seed)
  {
    seed = (seed ^ 61) ^ (seed >> 8);
    seed *= 9;
    seed = seed ^ (seed >> 4);
    seed = seed ^ (seed >> 15);
  }
}

//Takes care of the tickrate of the update loop
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