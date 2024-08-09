#pragma once

#include <random>
#include <chrono>
#include <bitset>


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