#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

class Spritesheet
{
public:
  Spritesheet();
  SDL_Texture *importToTex(SDL_Renderer* renderer, char* path);
private:
  SDL_Rect rect;
  int originX;
  int originY;
};
