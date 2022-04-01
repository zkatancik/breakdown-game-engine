// replacement functions for debugging some parts of SDL use for resource
// manager lab

#ifndef SDL_DEBUG
#define SDL_DEBUG

#ifdef _DEBUG
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <set>

inline std::set<SDL_Texture*>& __DEBUG__textures() {
  static std::set<SDL_Texture*>* textures = new std::set<SDL_Texture*>();
  return *textures;
}

inline SDL_Texture* __DEBUG__SDL_CreateTextureFromSurface(
    SDL_Renderer* renderer, SDL_Surface* surface) {
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture) {
    __DEBUG__textures().insert(texture);
  }
  std::cout << "SDL_DEBUG: Creating texture; " << __DEBUG__textures().size()
            << " textures loaded." << std::endl;
  return texture;
}
#define SDL_CreateTextureFromSurface __DEBUG__SDL_CreateTextureFromSurface

inline void __DEBUG__SDL_DestroyTexture(SDL_Texture* texture) {
  SDL_DestroyTexture(texture);
  if (texture) {
    __DEBUG__textures().erase(texture);
  }
  std::cout << "SDL_DEBUG: Destroying texture; " << __DEBUG__textures().size()
            << " textures loaded." << std::endl;
}
#define SDL_DestroyTexture __DEBUG__SDL_DestroyTexture

inline std::set<SDL_Surface*>& __DEBUG__surfaces() {
  static std::set<SDL_Surface*>* surfaces = new std::set<SDL_Surface*>();
  return *surfaces;
}

inline SDL_Surface* __DEBUG__SDL_LoadBMP_RW(SDL_RWops* src, int freesrc) {
  SDL_Surface* surface = SDL_LoadBMP_RW(src, freesrc);
  if (surface) {
    __DEBUG__surfaces().insert(surface);
  }
  std::cout << "SDL_DEBUG: Loading surface; " << __DEBUG__surfaces().size()
            << " surfaces loaded." << std::endl;
  return surface;
}
#define SDL_LoadBMP_RW __DEBUG__SDL_LoadBMP_RW

inline void __DEBUG__SDL_DestroySurface(SDL_Surface* surface) {
  SDL_FreeSurface(surface);
  if (surface) {
    __DEBUG__surfaces().erase(surface);
  }
  std::cout << "SDL_DEBUG: Freeing surface; " << __DEBUG__surfaces().size()
            << " surfaces loaded." << std::endl;
}
#define SDL_FreeSurface __DEBUG__SDL_DestroySurface

inline void __DEBUG__SDL_Quit() {
  std::cout << "SDL_DEBUG: Quitting SDL; " << __DEBUG__textures().size()
            << " textures and " << __DEBUG__surfaces().size()
            << " surfaces loaded." << std::endl;
  SDL_Quit();
}
#define SDL_Quit __DEBUG__SDL_Quit

#endif  //_DEBUG
#endif  // SDL_DEBUG
